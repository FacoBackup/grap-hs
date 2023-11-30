cmake_minimum_required(VERSION 3.26)
project(grafos2)

set(CMAKE_CXX_STANDARD 17)

add_executable(dfs dfs/main.c)
add_executable(bfs bfs/main.c common.h)
