cmake_minimum_required(VERSION 3.15)
project(MyBoostProject)

set(CMAKE_CXX_STANDARD 14)

# 设置 vcpkg 工具链文件
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
else()
    message(FATAL_ERROR "Please define VCPKG_ROOT environment variable")
endif()

# 查找 Boost 库
find_package(Boost REQUIRED COMPONENTS regex)

# 添加可执行文件并链接 Boost 库
add_executable(MyBoostProject main.cpp my_class.cpp)
target_link_libraries(MyBoostProject Boost::regex)