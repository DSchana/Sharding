cmake_minimum_required(VERSION 3.16)
project(Deconstruct)
project(Reconstruct)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall")

add_executable(Deconstruct src/deconstruct.cpp)
add_executable(Reconstruct src/reconstruct.cpp)
