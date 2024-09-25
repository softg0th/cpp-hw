#include <chrono>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <set>
#include <fstream>
#include <iostream>

void create_file(std::string result, std::set<std::string> usedFuncs) {
	auto now = std::chrono::system_clock::now();
	auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(
		now.time_since_epoch()).count();
    std::string fileName = "file_" + std::to_string(timestamp) + ".txt";
    std::filesystem::path currentPath = std::filesystem::current_path();
	
    std::unordered_map<std::string, std::string> funcs = {
    {"doubleAddSub", R"(double addSub(TokenData& tokenData) {
        double first = mulDiv(tokenData);

        while (tokenData.currentPosition < tokenData.finalExpression.size()) {
            char symb = tokenData.finalExpression[tokenData.currentPosition];

            if (symb != Token::SUB && symb != Token::ADD) {
                break;
            }
            tokenData.currentPosition++;

            double second = mulDiv(tokenData);
            if (symb == Token::ADD) {
                first += second;
            } else {
                first -= second;
            }
        }
        tokenData.usedFuncs.insert("doubleAddSub");
        return first;
    })"},
    {"doubleMulDiv", R"(double mulDiv(TokenData& tokenData) {
        double first = parseBrackets(tokenData);

        while (tokenData.currentPosition < tokenData.finalExpression.size()) {
            char symb = tokenData.finalExpression[tokenData.currentPosition];

            if (symb != Token::DIV && symb != Token::MUL) {
                break;
            }
            tokenData.currentPosition++;

            double second = parseBrackets(tokenData);
            if (symb == Token::MUL) {
                first *= second;
            } else {
                if (second != 0) {
                    first /= second;
                } else {
                    throw std::runtime_error("Error: Division by zero.");
                }
            }
        }
        tokenData.usedFuncs.insert("doubleMulDiv");
        return first;
    })"},
    {"intAddSub", R"(int addSubInt(TokenData& tokenData) {
        int first = intMulDiv(tokenData);

        while (tokenData.currentPosition < tokenData.finalExpression.size()) {
            char symb = tokenData.finalExpression[tokenData.currentPosition];

            if (symb != Token::SUB && symb != Token::ADD) {
                break;
            }
            tokenData.currentPosition++;

            int second = intMulDiv(tokenData);
            if (symb == Token::ADD) {
                first += second;
            } else {
                first -= second;
            }
        }
        tokenData.usedFuncs.insert("intAddSub");
        return first;
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
                first *= second;
            } else {
                if (second != 0) {
                    first /= second;
                } else {
                    throw std::runtime_error("Error: Division by zero.");
                }
            }
        }
        tokenData.usedFuncs.insert("intMulDiv");
        return first;
    })"}
    };

    std::ofstream fileOutput;
    fileOutput.open(fileName);
    std::cout << fileName << std::endl;
    if (fileOutput.is_open()) {
        fileOutput << result;
        fileOutput << '\n';

        for (const std::string& element : usedFuncs) {
            fileOutput << funcs[element];
            fileOutput << '\n';
        }
        fileOutput.close();
    }
}