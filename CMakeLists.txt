cmake_minimum_required(VERSION 3.5.2)
project(RISC5)

set(CMAKE_CXX_STANDARD 14)

add_executable(code code.cpp Instruction.hpp Memory.hpp Useful_Functions.hpp)
