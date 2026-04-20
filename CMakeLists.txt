cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Sokoban)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(Sokoban WIN32
    src/main.cpp
    src/game.cpp
    src/level.cpp
    src/history.cpp
    src/renderer.cpp
    src/input.cpp
)

# Include directories
include_directories(src)
