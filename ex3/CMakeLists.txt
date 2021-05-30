cmake_minimum_required(VERSION 3.15)
project(ex3)

set(CMAKE_CXX_STANDARD 14)


set(Boost_path "C:/Users/user/Downloads")
set(Boost_INCLUDE_DIR "${Boost_path}/boost_1_70_0")
find_package(Boost 1.70.0)

if (Boost_FOUND)
    message(STATUS "It works!")
    include_directories(${Boost_INCLUDE_DIR})
endif ()

add_executable(ex3 HashMap.hpp SpamDetector.cpp)

set_target_properties(ex3 PROPERTIES LINKER_LANGUAGE CXX)

