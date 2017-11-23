cmake_minimum_required(VERSION 3.8)
project(tri_fusion)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.c tri_fusion.c tri_fusion.h)

add_executable(tri_fusion ${SOURCE_FILES})