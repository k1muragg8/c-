cmake_minimum_required(VERSION 3.29)
project(con1)

set(CMAKE_CXX_STANDARD 23)

find_package(7zip)

target_link_libraries(7zip 7zip::7zip)

add_executable(con1 main.cpp)
