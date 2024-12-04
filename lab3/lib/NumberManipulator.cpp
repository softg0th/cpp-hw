#include <iostream>

#include "NumberManipulator.hpp"
#include "logger.hpp"

NumberManipulator::NumberManipulator() : number(0), numToString("") {
    updateMapHistory(number, numToString, "SetDefault");
    logOperations(1);
}

NumberManipulator::NumberManipulator(int number, const std::string& numToString) : number(0), numToString("") {
    updateMapHistory(number, numToString, "Set");
    logOperations(2);
}

NumberManipulator::NumberManipulator(const NumberManipulator& newCopy) : number(newCopy.number), numToString(newCopy.numToString) {
    logOperations(3);
}

NumberManipulator::NumberManipulator(NumberManipulator &&movedData) : number(movedData.number), numToString(movedData.numToString) {
    logOperations(4);
}

NumberManipulator::~NumberManipulator() {
    logOperations(5);
}

NumberManipulator& NumberManipulator::operator=(const NumberManipulator& other) {
    if (this != &other) {
        number = other.number;
        numToString = other.numToString;
        logOperations(6);
        updateMapHistory(number, numToString, "Copy");
    }
    return *this;
}

NumberManipulator& NumberManipulator::operator=(NumberManipulator&& other){
    if (this != &other) {
        number = other.number;
        numToString = std::move(other.numToString);
        logOperations(7);
        updateMapHistory(number, numToString, "Move");
    }
    return *this;
}

void NumberManipulator::getHistory() const {
    for (const auto& historyLine : history) {
        for (const auto& entry : historyLine) {
            std::cout << entry.first << ": " << entry.second << "\n";
        }
        std::cout << "------------------------\n";
    }
}

std::vector<std::map<std::string, std::string>> NumberManipulator::getValueHistory() {
    return history;
}