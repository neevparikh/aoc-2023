cmake_minimum_required(VERSION 3.28)
project(
  AoC
  VERSION 0.1
  DESCRIPTION "Advent of Code 2023"
  LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(aoc src/main.cc)

target_compile_features(aoc PUBLIC cxx_std_23)
set_target_properties(aoc PROPERTIES CXX_EXTENSIONS OFF)
