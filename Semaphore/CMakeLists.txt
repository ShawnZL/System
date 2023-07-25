cmake_minimum_required(VERSION 3.21)
project(Semaphore)

set(CMAKE_CXX_STANDARD 23)

add_executable(Semaphore main.cpp comm.h comm.cpp)
