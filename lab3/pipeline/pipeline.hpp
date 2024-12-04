#include <vector>
#include <list>

#include "../lib/NumberManipulator.hpp"


NumberManipulator createRandomObject();

template <typename T>
std::vector<T> buildInitialVector(int vecSize);

template <typename T>
std::vector<T> buildSliceVector(const std::vector<T>& initialVector, int startOffset, int endOffset);

template <typename T>
std::list<T> buildLargestList(const std::vector<T>& sliceVector);

template <typename T>
std::list<T> buildSmallestList(const std::vector<T>& sliceVector);

template <typename T>
void removeMovedElements(std::vector<T>& vec);

template <typename T>
void sortAverageElement(std::list<T>& inputList);

template <typename T>
void removeAllOddElements(std::list<T>& inputList);

template <typename T>
std::vector<T> vecFromUnionSet(const std::vector<T>& inputVecA, const std::vector<T>& inputVecB);

template <typename T>
std::list<std::pair<T, T>> equalizeLists(const std::list<T>& inputListA, const std::list<T>& inputListB);

template <typename T>
std::vector<T> equalizeVectors(const std::vector<T>& inputVectorA, const std::vector<T>& inputVectorB);

template <typename T>
void runPipeline(int vecSize);