cmake_minimum_required(VERSION 3.5)
project(magic_squares_perf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(magic_squares_perf ${SOURCE_FILES})