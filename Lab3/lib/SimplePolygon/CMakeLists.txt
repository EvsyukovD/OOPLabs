cmake_minimum_required(VERSION 3.22)
project(SimplePolygon)

set(SIMPLE_POLYGON_FILES SimplePolygon.cpp)
include_directories(DialogLib)
add_subdirectory(DialogLib)
include_directories(MathLib)
add_subdirectory(MathLib)
add_library(SimplePolygon STATIC ${SIMPLE_POLYGON_FILES})
target_link_libraries(SimplePolygon DialogLib MathLib)