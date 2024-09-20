cmake_minimum_required(VERSION 3.29)
project(ADT_Queue)

set(CMAKE_CXX_STANDARD 20)

add_executable(ADT_Queue main.cpp
        Stack.cpp
        Queue.cpp)
