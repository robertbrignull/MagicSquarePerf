cmake_minimum_required(VERSION 3.5)
project(magic_squares_perf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/impls/theirs/direct/direct.cpp src/impls/theirs/direct/direct.h src/impls/BaseImpl.h)
add_executable(magic_squares_perf ${SOURCE_FILES})