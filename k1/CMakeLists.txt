cmake_minimum_required(VERSION 3.29)
project(k1)

set(CMAKE_CXX_STANDARD 20)

add_executable(k1 main.cpp)

find_package(Boost)

target_link_libraries(k1 boost::boost)