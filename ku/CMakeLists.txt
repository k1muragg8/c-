cmake_minimum_required(VERSION 3.29)
project(ku)

set(CMAKE_CXX_STANDARD 20)

add_library(ku STATIC library.cpp)

find_package(fmt)

target_link_libraries(ku fmt::fmt)