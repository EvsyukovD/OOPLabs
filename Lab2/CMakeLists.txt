cmake_minimum_required(VERSION 3.22)
project(OOPLab2)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_CPP_FILES main.cpp)
include_directories(Lab2Lib)

add_executable(OOPLab2 ${SOURCE_CPP_FILES})

add_subdirectory(Lab2Lib)
add_subdirectory(LabTests)
target_link_libraries(OOPLab2 Lab2Lib)
