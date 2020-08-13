# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("x_library")

include_directories("xcommon/include")
include_directories("xsocket/include")
include_directories("xredis/include")
link_directories("lib")

set(EXECUTABLE_OUTPUT_PATH  "bin")
set(LIBRARY_OUTPUT_PATH "lib")

add_subdirectory ("xsocket")
add_subdirectory ("xredis")
add_subdirectory("test")
