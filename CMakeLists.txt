cmake_minimum_required(VERSION 3.28)
project(aoc2024)

set(CMAKE_CXX_STANDARD 23)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)
add_compile_options(-fno-omit-frame-pointer)

if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_definitions(-D_GLIBCXX_ASSERTIONS)
    add_definitions(-D_LIBCPP_DEBUG)
    add_compile_options(
            -fsanitize=address
            -fsanitize-address-use-after-scope
            -fsanitize-recover=address
            -fsanitize=undefined)
    add_link_options(-fsanitize=address -fsanitize=undefined)
endif ()


find_package(range-v3 REQUIRED)
find_package(fmt REQUIRED)
find_package(ctre REQUIRED)

add_subdirectory(util)
add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
add_subdirectory(day5)
add_subdirectory(day6)
add_subdirectory(day7)
add_subdirectory(day8)
add_subdirectory(day9)
add_subdirectory(day10)
add_subdirectory(day11)
add_subdirectory(day12)
add_subdirectory(day13)
add_subdirectory(day14)
add_subdirectory(day15)
add_subdirectory(day16)
add_subdirectory(day17)
add_subdirectory(day18)
