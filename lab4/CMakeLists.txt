cmake_minimum_required(VERSION 3.29)
project(lab)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab main.cpp
    sparse/SparseVector.hpp
)