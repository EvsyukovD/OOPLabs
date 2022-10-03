cmake_minimum_required(VERSION 3.22)
project(MathLib)
set(MATH_LIB_FILES math.cpp)
add_library(MathLib STATIC ${MATH_LIB_FILES})