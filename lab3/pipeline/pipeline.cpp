#include <iostream>

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
#include <list>
#include <iterator>
#include <cstdlib>

#include "../lib/NumberManipulator.hpp"

NumberManipulator createRandomObject() {
    auto obj =  NumberManipulator{std::rand(), "new"};
    return obj;
}

template <typename T>
std::vector<T> buildInitialVector(int vecSize) {
    std::vector<T> resultVector;
    for (int i = 0; i < vecSize; i++) {
        resultVector.push_back(T(std::rand(), "new"));
    }
    return resultVector;
}

template <typename T>
std::vector<T> buildSliceVector(const std::vector<T>& initialVector, int startOffset, int endOffset) {
    auto start = initialVector.begin() + startOffset;
    auto end = (endOffset < static_cast<int>(initialVector.size())) ? initialVector.begin() + endOffset : initialVector.end();
    return std::vector<T>(start, end);
}

template <typename T>
std::list<T> buildLargestList(const std::vector<T>& sliceVector) {
    auto sortedSlice = sliceVector;
    std::stable_sort(sortedSlice.begin(), sortedSlice.end(), std::greater<T>());

    auto start = sortedSlice.begin() + 20;
    auto end = (sortedSlice.size() > 50) ? (sortedSlice.begin() + 50) : sortedSlice.end();
    return std::list<T>(start, end);
}

template <typename T>
std::list<T> buildSmallestList(const std::vector<T>& sliceVector) {
    auto sortedSlice = sliceVector;
    std::stable_sort(sortedSlice.begin(), sortedSlice.end());

    auto start = (sortedSlice.size() > 20) ? (sortedSlice.end() - 20) : sortedSlice.begin();
    auto end = (sortedSlice.size() > 50) ? (sortedSlice.end() - 50) : sortedSlice.end();
    return std::list<T>(start, end);
}

template <typename T>
void removeMovedElements(std::vector<T>& vec) {
    vec.erase(std::remove_if(vec.begin(), vec.end(),
                             [](const T& elem) { return elem.name == "new"; }),
              vec.end());
}

template <typename T>
void sortAverageElement(std::list<T>& inputList) {
    auto sum = std::accumulate(inputList.begin(), inputList.end(), 0);
    auto average = sum / inputList.size();
    inputList.sort([average](const T& a, const T& b) {
        return std::abs(a.value - average) < std::abs(b.value - average);
    });
}

template <typename T>
void removeAllOddElements(std::list<T>& inputList) {
    int index = 0;
    inputList.remove_if([&index](int) {
        return index++ % 2 != 0;
    });
}

template <typename T>
std::vector<T> vecFromUnionSet(const std::vector<T>& inputVecA, const std::vector<T>& inputVecB) {
    std::vector<T> sortedA(inputVecA.begin(), inputVecA.end());
    std::vector<T> sortedB(inputVecB.begin(), inputVecB.end());

    std::sort(sortedA.begin(), sortedA.end());
    std::sort(sortedB.begin(), sortedB.end());

    std::vector<T> result;
    result.resize(sortedA.size() + sortedB.size());

    auto it = std::set_union(
        sortedA.begin(), sortedA.end(), 
        sortedB.begin(), sortedB.end(), 
        result.begin()
    );
    result.resize(std::distance(result.begin(), it));
    return result;
}

template <typename T>
std::list<std::pair<T, T>> equalizeLists(const std::list<T>& inputListA, const std::list<T>& inputListB) {
    std::list<T> longest = (inputListA.size() > inputListB.size()) ? inputListA : inputListB;
    std::list<T> smallest = (inputListA.size() < inputListB.size()) ? inputListA : inputListB;

    longest.insert(longest.end(), std::next(smallest.begin(), longest.size()), smallest.end());
    std::list<std::pair<T, T>> mergedPairs;
    auto itA = longest.begin();
    auto itB = smallest.begin();

    std::transform(itA, longest.end(), itB, std::back_inserter(mergedPairs),
        [](const T& a, const T& b) {
            return std::make_pair(a, b);
        });

    return mergedPairs;
}

template <typename T>
std::vector<T> equalizeVectors(const std::vector<T>& inputVectorA, const std::vector<T>& inputVectorB) {
    auto longest = (inputVectorA.size() > inputVectorB.size()) ? inputVectorA : inputVectorB;
    auto smallest = (inputVectorA.size() < inputVectorB.size()) ? inputVectorA : inputVectorB;

    std::vector<std::pair<T, T>> mergedPairs;
    auto itA = inputVectorA.begin();
    auto itB = inputVectorB.begin();

    auto minSize = std::min(inputVectorA.size(), inputVectorB.size());
    std::transform(itA, itA + minSize, itB, std::back_inserter(mergedPairs),
        [](const T& a, const T& b) {
            return std::make_pair(a, b);
        });

    return mergedPairs;
}

template <typename T>
void runPipeline(int vecSize) {
    auto initialVector = buildInitialVector(vecSize);
    std::cout << "Initial vector:" << std::endl;
    std::cout << initialVector << std::endl;

    auto sliceVector = buildSliceVector(initialVector, 10, 10);
    std::cout << "Slice vector:" << std::endl;
    std::cout << sliceVector << std::endl;

    auto listOfSlices = buildLargestList(sliceVector);
    std::cout << "List of slices:" << std::endl;
    std::cout << listOfSlices << std::endl;

    auto listOfSmallestSlices = buildSmallesList(sliceVector);
    std::cout << "List of smallest slices:" << std::endl;
    std::cout << listOfSmallestSlices << std::endl;

    removeMovedElements(initialVector);
    std::cout << "Initial vector:" << std::endl;
    std::cout << initialVector << std::endl;

    removeMovedElements(sliceVector);
    std::cout << "Slice vector:" << std::endl;
    std::cout << sliceVector << std::endl;

    sortAverageElement(listOfSlices);
    std::cout << "List of slices:" << std::endl;
    std::cout << listOfSlices << std::endl;

    removeAllOddElements(listOfSmallestSlices);
    std::cout << "List of smallest slices:" << std::endl;
    std::cout << listOfSmallestSlices << std::endl;

    auto setVector = vecFromUnionSet(initialVector, sliceVector);
    std::cout << "setVector:" << std::endl;
    std::cout << setVector << std::endl;

    auto mergedEqualizedList = equalizeLists(listOfSlices, listOfSmallestSlices);
    std::cout << "mergedEqualizeList:" << std::endl;
    std::cout << mergedEqualizedList << std::endl;

    auto mergedEqualizedVector = equalizeVectors(initialVector, sliceVector);
    std::cout << "mergedEqualizedVector:" << std::endl;
    std::cout << mergedEqualizedVector << std::endl;
}