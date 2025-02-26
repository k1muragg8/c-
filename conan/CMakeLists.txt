cmake_minimum_required(VERSION 3.29)
project(conan)

set(CMAKE_CXX_STANDARD 23)

add_executable(conan main.cpp)

find_package(Boost)
target_link_libraries(conan boost::boost)