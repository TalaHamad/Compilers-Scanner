cmake_minimum_required(VERSION 3.23)
project(complier)

set(CMAKE_CXX_STANDARD 14)

add_executable(complier main.cpp FileDescriptor.h FileDescriptor.cpp Scanner.h Scanner.cpp)
