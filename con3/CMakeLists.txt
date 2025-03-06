cmake_minimum_required(VERSION 3.29)
project(con3)

set(CMAKE_CXX_STANDARD 14)

find_package(aaf)

add_executable(con3 main.cpp)

target_link_libraries(con3 ${CONAN_LIBS})