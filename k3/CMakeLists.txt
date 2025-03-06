cmake_minimum_required(VERSION 3.29)
project(k3)

set(CMAKE_CXX_STANDARD 20)

add_executable(k3 main.cpp test.cpp)

find_package(Boost)

target_link_libraries(k3 boost::boost)