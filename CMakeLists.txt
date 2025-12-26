cmake_minimum_required(VERSION 3.20)
project(algolib VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TESTS "Build tests" ON)
option(ENABLE_BENCHMARKS "Build benchmarks" ON)

add_library(algolib INTERFACE)
target_include_directories(algolib INTERFACE include)

# Dependencies only used by tests / benchmarks
include(cmake/FetchDependencies.cmake)

if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if (ENABLE_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()
