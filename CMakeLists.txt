cmake_minimum_required(VERSION 3.5)
project(magic_squares_perf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/impls/theirs/direct/direct.cpp src/impls/theirs/direct/direct.h src/impls/BaseImpl.h src/impls/NullReferenceImpl.cpp src/impls/NullReferenceImpl.h src/impls/theirs/oddity_heuristic/oddity_heuristic.cpp src/impls/theirs/oddity_heuristic/oddity_heuristic.h src/impls/theirs/central_5/central_5.cpp src/impls/theirs/central_5/central_5.h src/impls/theirs/no_shifts/no_shifts.cpp src/impls/theirs/no_shifts/no_shifts.h)
add_executable(magic_squares_perf ${SOURCE_FILES})