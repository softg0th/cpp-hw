#include <iostream>

void logOperations(unsigned int op) {
    switch (op) {
        case 1:
            std::cout << "Default constructor call" << std::endl;
            break;
        case 2:
            std::cout << "Constructor call" << std::endl;
            break;
        case 3:
            std::cout << "Copy constructor call" << std::endl;
            break;
        case 4:
            std::cout << "Move constructor call" << std::endl;
            break;
        case 5:
            std::cout << "Destructor call" << std::endl;
            break;
        case 6:
            std::cout << "Assignment copy call" << std::endl;
            break;
        case 7:
            std::cout << "Assignment move call" << std::endl;
            break;
        default:
            throw std::runtime_error("Unknown operation");
            break;
    }
}