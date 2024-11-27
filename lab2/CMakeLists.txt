cmake_minimum_required(VERSION 3.29)
project(lab)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab main.cpp 
            lib/NumberManipulator.hpp 
            lib/NumberManipulator.cpp
            lib/logger.cpp
            lib/logger.hpp
            lib/common.cpp
            lib/common.hpp
            3rdparty/json.hpp)
