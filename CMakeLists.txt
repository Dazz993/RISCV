cmake_minimum_required(VERSION 3.13)
project(RISC5)

set(CMAKE_CXX_STANDARD 14)

add_executable(RISC5 main.cpp Instruction.hpp Memory.hpp Useful_Functions.hpp)