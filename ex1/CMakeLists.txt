cmake_minimum_required(VERSION 3.15)
project(ex1)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex1 main.cpp Matrix.h Matrix.cpp Activation.cpp Dense.h Dense.cpp MlpNetwork.cpp)