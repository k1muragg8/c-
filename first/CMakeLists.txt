cmake_minimum_required(VERSION 3.15)
project(MyProject)

set(CMAKE_CXX_STANDARD 14)

# 设置 vcpkg 工具链文件
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
else()
    message(FATAL_ERROR "Please define VCPKG_ROOT environment variable")
endif()

find_package(Boost REQUIRED)

add_executable(MyProject main.cpp)
target_link_libraries(MyProject Boost::Boost)