cmake_minimum_required(VERSION 4.0)
project(advent_of_code_library DESCRIPTION "guess")

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_BUILD_TYPE Debug)

set(sources src/io.cpp)
add_library(AoC SHARED ${sources})

target_include_directories(AoC PUBLIC include)

