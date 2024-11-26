#include "NumberManipulator.hpp"
#include "logger.hpp"

NumberManipulator::NumberManipulator() : number(0), numToString("") {
    logOperations(1);
}

NumberManipulator::NumberManipulator(int number, std::string& numToString) : number(0), numToString("") {
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