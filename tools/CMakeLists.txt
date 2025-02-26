cmake_minimum_required(VERSION 3.29)
project(tools)

set(CMAKE_CXX_STANDARD 23)

find_package(CURL REQUIRED)

add_executable(tools http_request.cpp)
target_link_libraries(tools CURL::libcurl)