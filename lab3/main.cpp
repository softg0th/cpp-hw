#include <iostream>

#include "pipeline/pipeline.hpp"

int main() {
    std::cout << "Input size" << std::endl;

    int vecSize;
    std::cin >> vecSize;

    std::cout << "Running pipeline..." << std::endl;

    runPipeline(vecSize);
}
