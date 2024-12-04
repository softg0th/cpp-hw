#include <iostream>

#include "pipeline/pipeline.hpp"

template <typename T>
void runPipeline(int vecSize);

int main() {
    std::cout << "Input size" << std::endl;
    
    int vecSize;
    std::cin >> vecSize;

    std::cout<< "Running pipeline..." << std::endl;
    runPipeline<NumberManipulator>(vecSize);
}