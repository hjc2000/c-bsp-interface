cmake_minimum_required(VERSION 3.20)
include(${cpp_lib_build_scripts_path}/cmake-module/setup.cmake)

set(ProjectName c-bsp-interface)
project(${ProjectName})
enable_language(ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

add_library(${ProjectName} STATIC)
target_import_src(${ProjectName})

set(CMAKE_INSTALL_PREFIX ${cpp_lib_build_scripts_path}/${platform}/.libs/${ProjectName}/)