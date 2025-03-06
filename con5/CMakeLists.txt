cmake_minimum_required(VERSION 3.29)
project(con5)

set(CMAKE_CXX_STANDARD 20)

add_executable(con5 main.cpp)

find_package(fmt)

target_link_libraries(con5 ${CONAN_LIBS})