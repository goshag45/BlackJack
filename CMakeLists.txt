# Minimum CMake version
cmake_minimum_required(VERSION 3.0.0)

# Project name and version
project(Blackjack VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
set(SOURCES
    src/main.cpp
    src/card.h
    src/cash.h
    src/dealer.h
    src/deck.h
    src/game.h
    src/hand.h
    src/player.h
    src/ui.h
)

# Add executable
add_executable(Blackjack ${SOURCES})

# Specify include directories
target_include_directories(Blackjack PUBLIC "${PROJECT_SOURCE_DIR}/src")

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)