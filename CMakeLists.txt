cmake_minimum_required(VERSION 2.8.4)
project(GoldSequence)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES task.cpp)
add_executable(GoldSequence ${SOURCE_FILES})