cmake_minimum_required(VERSION 4.0)
project(advent_of_code_library DESCRIPTION "guess")

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_BUILD_TYPE Debug)

#set(sources )
add_library(AoC INTERFACE)

target_include_directories(AoC INTERFACE include)
target_include_directories(AoC INTERFACE external)
