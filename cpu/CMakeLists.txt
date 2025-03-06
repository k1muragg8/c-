cmake_minimum_required(VERSION 3.29)
project(cpu)

set(CMAKE_CXX_STANDARD 20)

# 设置交叉编译工具链
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

add_executable(cpu main.cpp)
