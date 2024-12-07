#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "../lib/NumberManipulator.hpp"

std::vector<NumberManipulator> buildInitialVector(int vecSize) {
    std::vector<NumberManipulator> resultVector;
    resultVector.reserve(vecSize);
    for (int i = 0; i < vecSize; i++) {
        resultVector.emplace_back(std::rand(), "new");
    }
    return resultVector;
}

bool compareByBiggestNumber(const NumberManipulator& a, const NumberManipulator& b) {
    return a.number > b.number;
}

bool compareBySmallestNumber(const NumberManipulator& a, const NumberManipulator& b) {
    return a.number < b.number;
}

std::vector<NumberManipulator> sliceInitialVector(std::vector<NumberManipulator> inputVector) {
    int vecEnd = inputVector.size();
    std::vector<NumberManipulator> slicedVector;

    if (vecEnd < 200) {
        auto start = inputVector.begin();
        auto end = inputVector.begin() + vecEnd;
        slicedVector = std::vector<NumberManipulator>(start, end);
    } else {
        auto start = inputVector.begin() + 200;
        auto end = inputVector.begin() + vecEnd;
        slicedVector = std::vector<NumberManipulator>(start, end);
    }

    return slicedVector;
}

std::list<NumberManipulator> buildLargestList(std::vector<NumberManipulator> inputVector) {
    std::vector<NumberManipulator> slicedVector;
    std::sort(inputVector.begin(), inputVector.end(), compareByBiggestNumber);
    int vecEnd = inputVector.size();

    if (vecEnd < 20 || vecEnd < 50) {
        auto start = inputVector.begin();
        auto end = inputVector.begin() + vecEnd;
        slicedVector = std::vector<NumberManipulator>(start, end);
    } else {
        auto start = inputVector.begin() + 20;
        auto end = inputVector.begin() + 50;
        slicedVector = std::vector<NumberManipulator>(start, end);
    }

    return std::list<NumberManipulator>(slicedVector.begin(), slicedVector.end());
}

void removeMovedElements(std::vector<NumberManipulator>& inputVector) {
    inputVector.erase(std::remove_if(inputVector.begin(), inputVector.end(),
                               [](const NumberManipulator& nm) { return nm.isMoved(); }),
                inputVector.end());
}

std::list<NumberManipulator> buildSmallestList(std::vector<NumberManipulator> inputVector) {
    std::vector<NumberManipulator> slicedVector;
    std::sort(inputVector.begin(), inputVector.end(), compareBySmallestNumber);
    int vecEnd = inputVector.size();

    if (vecEnd < 20 || vecEnd < 50) {
        auto start = inputVector.begin();
        auto end = inputVector.begin() + vecEnd;
        slicedVector = std::vector<NumberManipulator>(start, end);
    } else {
        auto start = inputVector.begin() + 20;
        auto end = inputVector.begin() + 50;
        slicedVector = std::vector<NumberManipulator>(start, end);
    }

    return std::list<NumberManipulator>(slicedVector.begin(), slicedVector.end());
}

std::list<NumberManipulator>::iterator sortByAVGList(std::list<NumberManipulator>& inputList) {
    inputList.sort(compareByBiggestNumber);
    auto it = inputList.begin();
    std::advance(it, inputList.size() / 2);
    return it;
}

void removeAllOddNumbers(std::list<NumberManipulator>& inputList) {
    inputList.remove_if([](const NumberManipulator& nm) {
        return nm.number % 2 != 0;
    });
}

std::vector<NumberManipulator> buildCommonElements(
    std::vector<NumberManipulator> inputVectorA,
    std::vector<NumberManipulator> inputVectorB) {

    auto compareByNumber = [](const NumberManipulator& a, const NumberManipulator& b) {
        return a.number < b.number;
    };

    std::sort(inputVectorA.begin(), inputVectorA.end(), compareByNumber);
    std::sort(inputVectorB.begin(), inputVectorB.end(), compareByNumber);

    std::vector<NumberManipulator> result;

    std::set_intersection(
        inputVectorA.begin(), inputVectorA.end(),
        inputVectorB.begin(), inputVectorB.end(),
        std::back_inserter(result),
        compareByNumber
    );

    return result;
}

std::list<std::pair<NumberManipulator, NumberManipulator>> equalizeLists(
    std::list<NumberManipulator> inputListA,
    std::list<NumberManipulator> inputListB) {

    if (inputListA.size() > inputListB.size()) {
        auto it = inputListA.begin();
        std::advance(it, inputListA.size() - inputListB.size());
        inputListA.erase(inputListA.begin(), it);
    } else if (inputListB.size() > inputListA.size()) {
        auto it = inputListB.begin();
        std::advance(it, inputListB.size() - inputListA.size());
        inputListB.erase(inputListB.begin(), it);
    }

    std::list<std::pair<NumberManipulator, NumberManipulator>> mergedPairs;
    std::transform(
        inputListA.begin(), inputListA.end(), 
        inputListB.begin(),
        std::back_inserter(mergedPairs),
        [](const NumberManipulator& a, const NumberManipulator& b) {
            return std::make_pair(a, b);
        }
    );
    return mergedPairs;
}

std::vector<std::pair<NumberManipulator, NumberManipulator>> equalizeVectors(const std::vector<NumberManipulator>& inputVectorA, const std::vector<NumberManipulator>& inputVectorB) {
    auto longest = (inputVectorA.size() > inputVectorB.size()) ? inputVectorA : inputVectorB;
    auto smallest = (inputVectorA.size() < inputVectorB.size()) ? inputVectorA : inputVectorB;

    std::vector<std::pair<NumberManipulator, NumberManipulator>> mergedPairs;
    auto itA = inputVectorA.begin();
    auto itB = inputVectorB.begin();

    auto minSize = std::min(inputVectorA.size(), inputVectorB.size());
    std::transform(itA, itA + minSize, itB, std::back_inserter(mergedPairs),
        [](const NumberManipulator& a, const NumberManipulator& b) {
            return std::make_pair(a, b);
        });

    return mergedPairs;
}


template <typename T>
void print(const T& container) {
    for (const auto& obj : container) {
        std::cout << obj.number << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void printPairs(const T& container) {
    for (const auto& obj : container) {
            std::cout << obj.first.number << " " << obj.second.number << "  ";
        }
    std::cout << std::endl;
}

void runPipeline(int vecSize) {
    auto initialVector = buildInitialVector(vecSize);
    // print(initialVector);

    auto slicedVector = sliceInitialVector(initialVector);
    // print(slicedVector);

    auto largestList = buildLargestList(initialVector);
    // print(largestList);
 
    auto smallestList = buildSmallestList(slicedVector);
    // print(smallestList);

    // removeMovedElements(initialVector);
    // print(initialVector);

    // removeMovedElements(slicedVector);
    // print(slicedVector);

    auto avgIT = sortByAVGList(largestList);
    int avg = avgIT->number;
    // print(largestList);
    // std::cout << avg << std::endl;

    removeAllOddNumbers(smallestList);
    // print(smallestList);

    auto mergedVector = buildCommonElements(initialVector, slicedVector);
    // print(mergedVector);

    auto equalizedLists = equalizeLists(largestList, smallestList);
    // printPairs(equalizedLists);

    auto equalizedVectors = equalizeVectors(initialVector, slicedVector);
    // printPairs(equalizedVectors);
}

