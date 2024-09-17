# Minimum CMake version
cmake_minimum_required(VERSION 3.0.0)

# Project name and version
project(Blackjack VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(dependencies)
add_subdirectory(src)

# Specify include directories
target_include_directories(Blackjack PUBLIC "${PROJECT_SOURCE_DIR}/src")

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
