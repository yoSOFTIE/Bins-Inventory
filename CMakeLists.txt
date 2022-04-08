cmake_minimum_required(VERSION 3.21)
project(Bins_Inventory)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Bins_Inventory
        bins.cpp
        bins.h
        main.cpp)
