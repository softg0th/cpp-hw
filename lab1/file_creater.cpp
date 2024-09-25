#include <chrono>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <set>
#include <fstream>
#include <iostream>
#include <regex>

std::string replacePlaceholders(const std::string& str, const std::unordered_map<std::string, std::string>& replacements) {
    std::string result = str;
    for (const auto& [key, value] : replacements) {
        result = std::regex_replace(result, std::regex("\\{" + key + "\\}"), value);
    }
    return result;
}

void create_file(std::string result, std::vector<std::pair<std::string, std::pair<std::string, std::string>>> usedFuncs) {
    
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(
        now.time_since_epoch()).count();
    std::string fileName = "file_" + std::to_string(timestamp) + ".txt";
    std::filesystem::path currentPath = std::filesystem::current_path();

    std::unordered_map<std::string, std::string> funcs = {
    {"doubleAddSub", R"(double addSub(TokenData& tokenData) {
        double {first} = mulDiv(tokenData);
        
        while (tokenData.currentPosition < tokenData.finalExpression.size()) {
            char symb = tokenData.finalExpression[tokenData.currentPosition];

            if (symb != Token::SUB && symb != Token::ADD) {
                break;
            }
            tokenData.currentPosition++;

            double second = mulDiv(tokenData);
            if (symb == Token::ADD) {
                {first} += {second};
            } else {
                {first} -= {second};
            }
        }
        return {first};
    })"},
    {"doubleMulDiv", R"(double mulDiv(TokenData& tokenData) {
        double {first} = parseBrackets(tokenData);

        while (tokenData.currentPosition < tokenData.finalExpression.size()) {
            char symb = tokenData.finalExpression[tokenData.currentPosition];

            if (symb != Token::DIV && symb != Token::MUL) {
                break;
            }
            tokenData.currentPosition++;

            double {second} = parseBrackets(tokenData);
            if (symb == Token::MUL) {
                {first} *= {second};
            } else {
                if (second != 0) {
                    {first} /= {second};
                } else {
                    throw std::runtime_error("Error: Division by zero.");
                }
            }
        }
        return {first};
    })"},
    {"intAddSub", R"(int addSubInt(TokenData& tokenData) {
        int {first} = intMulDiv(tokenData);

        while (tokenData.currentPosition < tokenData.finalExpression.size()) {
            char symb = tokenData.finalExpression[tokenData.currentPosition];

            if (symb != Token::SUB && symb != Token::ADD) {
                break;
            }
            tokenData.currentPosition++;

            int second = intMulDiv(tokenData);
            if (symb == Token::ADD) {
                {first} += {second};
            } else {
                {first} -= {second};
            }
        }
        return {first};
    })"},
    {"intMulDiv", R"(int intMulDiv(TokenData& tokenData) {
        int first = parseBracketsInt(tokenData);

        while (tokenData.currentPosition < tokenData.finalExpression.size()) {
            char symb = tokenData.finalExpression[tokenData.currentPosition];

            if (symb != Token::DIV && symb != Token::MUL) {
                break;
            }
            tokenData.currentPosition++;

            int second = parseBracketsInt(tokenData); // исправлено на int
            if (symb == Token::MUL) {
                {first} *= {second};
            } else {
                if (second != 0) {
                    {first} /= {second};
                } else {
                    throw std::runtime_error("Error: Division by zero.");
                }
            }
        }
        return {first};
    })"}
    };

    std::ofstream fileOutput;
    fileOutput.open(fileName);
    if (fileOutput.is_open()) {
        fileOutput << result;
        fileOutput << '\n';

        for (const auto& usedFunc : usedFuncs) {
            std::string gotFunc = funcs[usedFunc.first];
            std::unordered_map<std::string, std::string> firstMap = { {"first", usedFunc.second.first} };
            std::unordered_map<std::string, std::string> secondMap = { {"second", usedFunc.second.second} };

            std::string temp = replacePlaceholders(gotFunc, firstMap);
            std::string finalFunc = replacePlaceholders(temp, secondMap);
            fileOutput << finalFunc;
            fileOutput << '\n';
        }
     fileOutput.close();
    }
}