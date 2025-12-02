cmake_minimum_required(VERSION 4.0)
project(advent_of_code DESCRIPTION "guess")

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_BUILD_TYPE Debug)

# Structure related
set(year 2025)
set(day 02)
set(dir ${CMAKE_SOURCE_DIR}/src/${year}/${day})
add_executable(main ${dir}/main.cpp)


# Optional libraries
set(openssl ssl crypto)

find_library(libAoC NAMES AoC PATHS ${CMAKE_SOURCE_DIR}/lib/build REQUIRED NO_DEFAULT_PATH)


target_link_libraries(main PRIVATE ${libAoC} ${openssl})
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/lib/external)


