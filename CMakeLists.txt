cmake_minimum_required(VERSION 3.26)

cmake_policy(VERSION 3.26)

project(
  AOC
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

set(COMMON_SRCS 
        src/common/display.cpp 
        src/common/runner.cpp
)

set(SOLUTION_SRCS 
        src/solutions/main.cpp
        src/solutions/day01.cpp
        src/solutions/day02.cpp
        src/solutions/day03.cpp
        src/solutions/day04.cpp
        src/solutions/day05.cpp
        src/solutions/day06.cpp
        src/solutions/day07.cpp
        src/solutions/day08.cpp
        src/solutions/day09.cpp
        src/solutions/day10.cpp
        src/solutions/day11.cpp
        src/solutions/day12.cpp
        src/solutions/day13.cpp
        src/solutions/day14.cpp
        src/solutions/day15.cpp
        src/solutions/day16.cpp
        src/solutions/day17.cpp
        src/solutions/day18.cpp
        src/solutions/day19.cpp
        src/solutions/day20.cpp
        src/solutions/day21.cpp
        src/solutions/day22.cpp
        src/solutions/day23.cpp
        src/solutions/day24.cpp
        src/solutions/day25.cpp
)

add_executable(AOC ${SOLUTION_SRCS} ${COMMON_SRCS})
target_include_directories(AOC PRIVATE include/)