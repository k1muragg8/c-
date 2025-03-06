cmake_minimum_required(VERSION 3.29)
project(mysql)

set(CMAKE_CXX_STANDARD 23)
find_package(autoconf)

add_executable(mysql main.cpp)

target_link_libraries(mysql autoconf::autoconf)