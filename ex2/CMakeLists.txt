cmake_minimum_required(VERSION 3.14)
project(ex2)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex2 FractalDrawer.cpp Fractal.cpp Fractal.h)

set(Boost_path "C:/Users/user/Downloads")
set(Boost_INCLUDE_DIR "${Boost_path}/boost_1_70_0")
find_package(Boost 1.70.0)

if (Boost_FOUND)
    message(STATUS "It works!")
    include_directories(${Boost_INCLUDE_DIR})
endif ()