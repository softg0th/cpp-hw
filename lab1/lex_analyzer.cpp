#include <iostream>
#include <cstdlib>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>

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
    std::set<std::string> usedFuncs;
};

double addSub(TokenData& tokenData);
double mulDiv(TokenData& tokenData);
double parseBrackets(TokenData& tokenData);
double parseNumber(TokenData& tokenData);

double addSub(TokenData& tokenData) {
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
            tokenData.usedFuncs.insert("+");
        }
        else {
            first -= second;
            tokenData.usedFuncs.insert("-");
        }
    }
    return first;
}

double mulDiv(TokenData& tokenData) {
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
            tokenData.usedFuncs.insert("*");
        }
        else {
            if (second != 0) {
                first /= second;
                tokenData.usedFuncs.insert("/");
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

void analyzeString(const std::string& inputExpression) {
    if (inputExpression.empty() || !isValidExpr(inputExpression)) {
        throw std::runtime_error("Error: Invalid expression.");
    }
    TokenData td;
    td.currentPosition = 0;
    td.finalExpression = inputExpression;

    double result = addSub(td);
    std::cout << "Result: " << result << std::endl;
}