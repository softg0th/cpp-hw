#include <iostream>
#include <cstdlib>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include "file_creater.hpp"

enum Token {
    NUMBER,
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',
    LBRACKET = '(',
    RBRACKET = ')'
};

bool isValidExpr(const std::string& mathExpr) {
    std::set<char> mathSymbs{ '+', '-', '*', '/', '(', ')' };

    for (char chr : mathExpr) {
        if (mathSymbs.count(chr) || std::isspace(chr)) {
            continue;
        }
        if (!std::isdigit(chr) && chr != '.') {
            return false;
        }
    }
    return true;
}

struct TokenData {
    int currentPosition;
    std::string finalExpression;
    std::vector<std::pair<std::string, std::pair<std::string, std::string>>> usedFuncs;
};

double addSub(TokenData& tokenData);
double mulDiv(TokenData& tokenData);
double parseBrackets(TokenData& tokenData);
double parseNumber(TokenData& tokenData);
int addSubInt(TokenData& tokenData);
int intMulDiv(TokenData& tokenData);
int parseBracketsInt(TokenData& tokenData);
int parseNumberInt(TokenData& tokenData);

double addSub(TokenData& tokenData) {
    double first = mulDiv(tokenData);
    double second;

    while (tokenData.currentPosition < tokenData.finalExpression.size()) {
        char symb = tokenData.finalExpression[tokenData.currentPosition];

        if (symb != Token::SUB && symb != Token::ADD) {
            break;
        }
        tokenData.currentPosition++;

        second = mulDiv(tokenData);
        tokenData.usedFuncs.push_back({ "doubleAddSub", {std::to_string(first), std::to_string(second)} });
        if (symb == Token::ADD) {
            first += second;
        }
        else {
            first -= second;
        }
    }
    return first;
}

double mulDiv(TokenData& tokenData) {
    double first = parseBrackets(tokenData);
    double second;

    while (tokenData.currentPosition < tokenData.finalExpression.size()) {
        char symb = tokenData.finalExpression[tokenData.currentPosition];

        if (symb != Token::DIV && symb != Token::MUL) {
            break;
        }
        tokenData.currentPosition++;

        second = parseBrackets(tokenData);
        tokenData.usedFuncs.push_back({ "doubleMulDiv", {std::to_string(first), std::to_string(second)} });
        if (symb == Token::MUL) {
            first *= second;
        }
        else {
            if (second != 0) {
                first /= second;
            }
            else {
                throw std::runtime_error("Error: Division by zero.");
            }
        }
    }
    
    return first;
}

double parseBrackets(TokenData& tokenData) {
    char curr = tokenData.finalExpression[tokenData.currentPosition];

    if (curr == Token::LBRACKET) {
        tokenData.currentPosition++;
        double result = addSub(tokenData);
        if (tokenData.currentPosition >= tokenData.finalExpression.size() ||
            tokenData.finalExpression[tokenData.currentPosition] != Token::RBRACKET) {
            throw std::runtime_error("Error: Mismatched parentheses.");
        }
        tokenData.currentPosition++;
        return result;
    }
    else if (std::isdigit(curr) || curr == '.') {
        return parseNumber(tokenData);
    }

    throw std::runtime_error("Error: Unexpected character.");
}
double parseNumber(TokenData& tokenData) {
    std::string numberStr;

    while (tokenData.currentPosition < tokenData.finalExpression.size() &&
        (std::isdigit(tokenData.finalExpression[tokenData.currentPosition]) ||
            tokenData.finalExpression[tokenData.currentPosition] == '.')) {
        numberStr += tokenData.finalExpression[tokenData.currentPosition++];
    }

    return std::stod(numberStr);
}

int addSubInt(TokenData& tokenData) {
    int first = intMulDiv(tokenData);
    int second;

    while (tokenData.currentPosition < tokenData.finalExpression.size()) {
        char symb = tokenData.finalExpression[tokenData.currentPosition];

        if (symb != Token::SUB && symb != Token::ADD) {
            break;
        }
        tokenData.currentPosition++;

        second = intMulDiv(tokenData);
        tokenData.usedFuncs.push_back({ "intAddSub", {std::to_string(first), std::to_string(second)} });
        if (symb == Token::ADD) {
            first += second;
        }
        else {
            first -= second;
        }
    }
    return first;
}

int intMulDiv(TokenData& tokenData) {
    int first = parseBracketsInt(tokenData);
    int second;

    while (tokenData.currentPosition < tokenData.finalExpression.size()) {
        char symb = tokenData.finalExpression[tokenData.currentPosition];

        if (symb != Token::DIV && symb != Token::MUL) {
            break;
        }
        tokenData.currentPosition++;

        second = parseBrackets(tokenData);
        tokenData.usedFuncs.push_back({ "intMulDiv", {std::to_string(first), std::to_string(second)} });
        if (symb == Token::MUL) {
            first *= second;
        } else {
            if (second != 0) {
                first /= second;
            } else {
                throw std::runtime_error("err");
            }
        }
    }
    return first;
}

int parseBracketsInt(TokenData& tokenData) {
    char curr = tokenData.finalExpression[tokenData.currentPosition];

    if (curr == Token::LBRACKET) {
        tokenData.currentPosition++;
        int result = addSub(tokenData);
        if (tokenData.currentPosition >= tokenData.finalExpression.size() ||
            tokenData.finalExpression[tokenData.currentPosition] != Token::RBRACKET) {
            throw std::runtime_error("err");
        }
        tokenData.currentPosition++;
        return result;
    }
    else if (std::isdigit(curr)) {
        return parseNumber(tokenData);
    }

    throw std::runtime_error("err");
}

int parseNumberInt(TokenData& tokenData) {
    std::string numberStr;

    while (tokenData.currentPosition < tokenData.finalExpression.size() &&
        (std::isdigit(tokenData.finalExpression[tokenData.currentPosition]))) {
        numberStr += tokenData.finalExpression[tokenData.currentPosition++];
    }

    return std::stoi(numberStr);
}

void analyzeString(const std::string& inputExpression, char typeInput) {
    if (inputExpression.empty() || !isValidExpr(inputExpression)) {
        throw std::runtime_error("Error: Invalid expression.");
    }
    TokenData td;
    td.currentPosition = 0;
    td.finalExpression = inputExpression;

    if (typeInput == '1') {
        double result = addSub(td);
        std::cout << "Result: " << result << std::endl;
        create_file(std::to_string(result), td.usedFuncs);
    }
    else {
        int result = addSubInt(td);
        std::cout << "Result: " << result << std::endl;
        create_file(std::to_string(result), td.usedFuncs);
    }
}