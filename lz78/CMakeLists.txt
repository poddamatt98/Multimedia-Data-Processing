cmake_minimum_required(VERSION 3.19)
project(lz78)

set(CMAKE_CXX_STANDARD 14)

add_executable(lz78 main.cpp lz78encode.cpp lz78encode.h)