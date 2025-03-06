cmake_minimum_required(VERSION 3.29)
project(con4)

set(CMAKE_CXX_STANDARD 20)

add_executable(con4 main.cpp)

find_package(7zip)
target_link_libraries(con4 ${CONAN_LIBS})