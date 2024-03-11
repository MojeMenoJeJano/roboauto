cmake_minimum_required(VERSION 3.27)
project(roboauto)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(roboauto
        assignment3.cpp
        main.cpp)
