#include <iostream>
#include <cstdlib>
#include <set>
#include <stdexcept>
#include <string>
#include <format>
#include "lex_analyzer.hpp"

enum Token {
    NUMBER,
    PLUS = '+',
    MINUS = '-',
    MUL = '*',
    DIV = '/',
};

struct OutputValues {
    int ansInt;
    double ansDouble;
    std::set<std::string> usedFuncs;
};

struct Expression
{
    double value = 0;
    Token token = Token::NUMBER;
    std::shared_ptr<Expression> pLeft = nullptr;
    std::shared_ptr<Expression> pRight = nullptr;
};

using ExpressionPtr = std::shared_ptr<Expression>;

ExpressionPtr ParseNum(std::string& expr) {
    std::shared_ptr<Expression> exprNode = std::make_shared<Expression>();
    if (!expr.empty() && std::isdigit(expr[0])) {
        exprNode->value = std::stod(expr);
        exprNode->token = Token::NUMBER;
        expr.erase(0, 1);
    }
    return exprNode;
}

ExpressionPtr ParseMulDiv(std::string& expr) {
    ExpressionPtr left = ParseNum(expr);
    while (true) {
        if (expr.empty()) break;

        Token token = Token::NUMBER;
        if (expr[0] == '*') {
            token = Token::MUL;
        }
        else if (expr[0] == '/') {
            token = Token::DIV;
        }
        else {
            return left;
        }

        expr.erase(0, 1);
        ExpressionPtr right = ParseNum(expr);
        ExpressionPtr newExpr = std::make_shared<Expression>();
        newExpr->pLeft = left;
        newExpr->pRight = right;
        newExpr->token = token;
        left = newExpr;
    }
    return left;
}

ExpressionPtr ParseAddSub(std::string& expr) {
    ExpressionPtr left = ParseMulDiv(expr);
    while (true) {
        if (expr.empty()) break;

        Token token = Token::NUMBER;
        if (expr[0] == '+') {
            token = Token::PLUS;
        }
        else if (expr[0] == '-') {
            token = Token::MINUS;
        }
        else {
            return left;
        }

        expr.erase(0, 1);
        ExpressionPtr right = ParseMulDiv(expr);
        ExpressionPtr newExpr = std::make_shared<Expression>();
        newExpr->pLeft = left;
        newExpr->pRight = right;
        newExpr->token = token;
        left = newExpr;
    }
    return left;
}


bool isValidExpr(const std::string& mathExpr) {
    std::set<char> mathSymbs{ '+', '-', '*', '/' };

    for (char chr : mathExpr) {
        if (mathSymbs.count(chr)) {
            continue;
        }
        if (!std::isdigit(chr) && chr != '.') {
            return false;
        }
    }
    return true;
}

double calculateExpression(std::shared_ptr<Expression> pExpr) {
    if (pExpr->token != Token::NUMBER) {
        if (!pExpr->pLeft) {
            throw std::runtime_error("pLeft is null");
        }

        if (!pExpr->pRight) {
            throw std::runtime_error("pRight is null");
        }

        calculateExpression(pExpr->pLeft);
        calculateExpression(pExpr->pRight);

        switch (pExpr->token) {
        case Token::PLUS:
            pExpr->value = pExpr->pLeft->value + pExpr->pRight->value;
            break;
        case Token::MINUS:
            pExpr->value = pExpr->pLeft->value - pExpr->pRight->value;
            break;
        case Token::DIV:
            pExpr->value = pExpr->pLeft->value / pExpr->pRight->value;
            break;
        case Token::MUL:
            pExpr->value = pExpr->pLeft->value * pExpr->pRight->value;
            break;
        case Token::NUMBER:
            throw std::runtime_error("number is symbs");
        }
    }
    return pExpr->value;
}




void analyzeString(const std::string& inputExpression) {
    if (!isValidExpr(inputExpression)) {
        // throw std::runtime_error(std::format("Error: {} consists of unsupported symbols!", inputExpression));
        throw std::runtime_error("err");
    }
    std::string expr = inputExpression;
    ExpressionPtr parsedExpression = ParseAddSub(expr);
    double result = calculateExpression(parsedExpression);
    std::cout << "Result: " << result << std::endl;
}