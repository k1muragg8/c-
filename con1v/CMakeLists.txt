cmake_minimum_required(VERSION 3.29)
project(con1v)

set(CMAKE_CXX_STANDARD 20)

add_executable(con1v main.cpp
        MySQLDatabase.cpp)

find_package(libmysqlclient REQUIRED)

target_link_libraries(con1v libmysqlclient::libmysqlclient)