cmake_minimum_required(VERSION 3.22)

project(lib)
set(LIB_FILES Lab3.cpp)

add_library(lib STATIC ${LIB_FILES})