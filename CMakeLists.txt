cmake_minimum_required(VERSION 3.20)
project(DataStructurs_hw2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DataStructurs_hw2
        UnionFind.cpp
        UnionFind.h main1.cpp HashTables.h HashTables.cpp)
