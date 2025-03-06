cmake_minimum_required(VERSION 3.29)
project(con2)

set(CMAKE_CXX_STANDARD 23)
find_package(fmt)
target_link_libraries(fmt fmt::fmt)
add_executable(con2 main.cpp)
