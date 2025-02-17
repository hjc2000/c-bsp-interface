cmake_minimum_required(VERSION 3.8)
set(ProjectName c-bsp-interface)
project(${ProjectName})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

include($ENV{cpp_lib_build_scripts_path}/cmake-module/setup.cmake)


# 编译目标
add_library(${ProjectName})
target_import_src(${ProjectName})
