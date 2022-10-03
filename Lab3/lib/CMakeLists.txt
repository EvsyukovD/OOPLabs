cmake_minimum_required(VERSION 3.22)

project(lib)
#set(LIB_FILES SimplePolygon/SimplePolygon.cpp PolygonWithOperators.cpp DynamicPolygon.cpp)
include_directories(SimplePolygon PolygonWithOperators)
add_subdirectory(SimplePolygon)
add_subdirectory(PolygonWithOperators)
#add_subdirectory(DynamicPolygon)
#add_library(lib STATIC ${LIB_FILES})