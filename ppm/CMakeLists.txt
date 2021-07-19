cmake_minimum_required(VERSION 3.19)
project(ppm_load)

set(CMAKE_CXX_STANDARD 14)

add_executable(ppm_load main.cpp json.cpp)