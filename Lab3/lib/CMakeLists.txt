cmake_minimum_required(VERSION 3.22)

project(lib)
set(LIB_FILES SimplePolygon/SimplePolygon.cpp PolygonWithOperators.cpp DynamicPolygon.cpp)

add_library(lib STATIC ${LIB_FILES})