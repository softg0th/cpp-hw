/*
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <chrono>
#include "sparse/SparseVecMatrix.hpp"

// Alias for convenience
using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;

void testSparseVector() {
    auto start = Clock::now();

    SparseVector<std::vector<int>> sv;
    std::vector<int> data = {0, 3, 0, 0, 5};
    sv.buildContainer(data);
    sv.print();

    auto result = sv.add({0, 1, 0, 2, -5});
    for (size_t i = 0; i < result.size(); ++i) {
        if (result[i] != 0) {
            std::cout << "(" << i << ", " << result[i] << ") ";
        }
    }
    std::cout << std::endl;

    int dotProduct = sv.multiply({0, 1, 0, 2, 5});
    std::cout << "Scalar multiply: " << dotProduct << std::endl;

    auto scalarResult = sv.scalarMultiply(2);
    for (size_t i = 0; i < scalarResult.size(); ++i) {
        if (scalarResult[i] != 0) {
            std::cout << "(" << i << ", " << scalarResult[i] << ") ";
        }
    }
    std::cout << std::endl;

    auto end = Clock::now();
    Duration duration = end - start;
    std::cout << "Execution time for testSparseVector: " << duration.count() << " seconds\n";
}

void testSparseMatrix() {
    auto start = Clock::now();

    SparseMatrix<std::vector<std::vector<int>>> sm;
    std::vector<std::vector<int>> data = {
        {0, 0, 3},
        {4, 0, 0},
        {0, 5, 0}
    };
    sm.buildMatrix(data);
    sm.print();

    auto scalarResult = sm.scalarMultiply(2);
    scalarResult.print();

    auto end = Clock::now();
    Duration duration = end - start;
    std::cout << "Execution time for testSparseMatrix: " << duration.count() << " seconds\n";
}

void testSparseMatrixExtensions() {
    auto start = Clock::now();

    SparseMatrix<std::vector<std::vector<int>>> sm;
    std::vector<std::vector<int>> data = {
        {0, 2, 0},
        {3, 0, 4},
        {0, 0, 5}
    };
    sm.buildMatrix(data);

    std::cout << "Source matrix:" << std::endl;
    sm.print();

    auto transposed = sm.transpose();
    std::cout << "Transposed:" << std::endl;
    transposed.print();

    auto powered = sm.power(2);
    std::cout << "Powered matrix:" << std::endl;
    powered.print();

    auto end = Clock::now();
    Duration duration = end - start;
    std::cout << "Execution time for testSparseMatrixExtensions: " << duration.count() << " seconds\n";
}

int main() {
    std::cout << "Testing Sparse Vector:" << std::endl;
    testSparseVector();

    std::cout << "\nTesting Sparse Matrix:" << std::endl;
    testSparseMatrix();

    std::cout << "\nTesting Sparse Matrix Extensions:" << std::endl;
    testSparseMatrixExtensions();

    return 0;
}
*/



#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <chrono>
#include "sparse/SparseVector.hpp"

// Alias for convenience
using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;

void testSparseVector() {
    auto start = Clock::now();

    SparseVector<std::vector<int>> sv;
    std::vector<int> data = {0, 3, 0, 0, 5};
    sv.buildContainer(data);
    sv.print();

    auto result = sv.add({0, 1, 0, 2, -5});
    for (size_t i = 0; i < result.size(); ++i) {
        if (result.find(i) != result.end() && result[i] != 0) {
            std::cout << "(" << i << ", " << result[i] << ") ";
        }
    }
    std::cout << std::endl;

    int dotProduct = sv.multiply({0, 1, 0, 2, 5});
    std::cout << "Scalar multiply: " << dotProduct << std::endl;

    auto scalarResult = sv.scalarMultiply(2);
    for (const auto& [index, value] : scalarResult) {
        if (value != 0) {
            std::cout << "(" << index << ", " << value << ") ";
        }
    }
    std::cout << std::endl;

    auto end = Clock::now();
    Duration duration = end - start;
    std::cout << "Execution time for testSparseVector: " << duration.count() << " seconds\n";
}

void testSparseMatrix() {
    auto start = Clock::now();

    SparseMatrix<std::vector<std::vector<int>>> sm;
    std::vector<std::vector<int>> data = {
        {0, 0, 3},
        {4, 0, 0},
        {0, 5, 0}
    };
    sm.buildMatrix(data);
    sm.print();

    auto scalarResult = sm.scalarMultiply(2);
    scalarResult.print();

    auto end = Clock::now();
    Duration duration = end - start;
    std::cout << "Execution time for testSparseMatrix: " << duration.count() << " seconds\n";
}

void testSparseMatrixExtensions() {
    auto start = Clock::now();

    SparseMatrix<std::vector<std::vector<int>>> sm;
    std::vector<std::vector<int>> data = {
        {0, 2, 0},
        {3, 0, 4},
        {0, 0, 5}
    };
    sm.buildMatrix(data);

    std::cout << "Source matrix:" << std::endl;
    sm.print();

    auto transposed = sm.transpose();
    std::cout << "Transposed:" << std::endl;
    transposed.print();

    auto powered = sm.power(2);
    std::cout << "Powered matrix:" << std::endl;
    powered.print();

    auto end = Clock::now();
    Duration duration = end - start;
    std::cout << "Execution time for testSparseMatrixExtensions: " << duration.count() << " seconds\n";
}

int main() {
    std::cout << "Testing Sparse Vector:" << std::endl;
    testSparseVector();

    std::cout << "\nTesting Sparse Matrix:" << std::endl;
    testSparseMatrix();

    std::cout << "\nTesting Sparse Matrix Extensions:" << std::endl;
    testSparseMatrixExtensions();

    return 0;
}
