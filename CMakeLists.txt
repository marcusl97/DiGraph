cmake_minimum_required(VERSION 3.27)
project(graph)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(Google_tests)

add_executable(graph main.cpp
        graph.h
        graph.cpp)
