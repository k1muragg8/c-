cmake_minimum_required(VERSION 3.29)
project(k2)

set(CMAKE_CXX_STANDARD 20)

add_executable(k2 main.cpp)

find_package(Boost)
find_package(nlohmann_json)

target_link_libraries(k2 boost::boost, nlohmann_json::nlohmann_json)