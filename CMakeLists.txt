cmake_minimum_required(VERSION 3.17.5)
project(DataStructurs_hw2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DataStructurs_hw2
        UnionFind.cpp
        UnionFind.h main1.cpp HashTables.h HashTables.cpp Player.cpp Player.h
        GameSystem.cpp GameSystem.h Group.cpp Group.h avl.h)
