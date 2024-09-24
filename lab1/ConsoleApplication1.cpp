#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <format>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include "lex_analyzer.hpp"
#pragma warning(disable:4996)


std::vector<std::string> getStringFromFile(const std::string& fileName) {
	std::vector<std::string> mathExpressions;
	std::string line;
	std::fstream expressionFile(fileName);

	if (!expressionFile.is_open()) {
		// throw std::runtime_error(std::format("Error: {} doesn't exist!", fileName));
		throw std::runtime_error("err");
	}

	while (getline(expressionFile, line)) {
		line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
		mathExpressions.push_back(line);
	}
	return mathExpressions;
}

int main(void)
{
	std::string pathToFile, mathExpression;

	std::cout << "Input path:" << std::endl; 
	std::cin >> pathToFile;
	std::vector<std::string> mathExpressions = getStringFromFile(pathToFile);

	for (int element = 0; element < mathExpressions.size(); element++) {
		try {
			std::cout << element << std::endl;
			std::string singleExpression = mathExpressions[element];
			analyzeString(singleExpression);
		}
		catch (const std::runtime_error& e) {
			std::cerr << e.what() << std::endl;
		}
	}
}
