cmake_minimum_required(VERSION 3.22)

project(lib)
include_directories(SimplePolygon PolygonWithOperators DynamicPolygon)
add_subdirectory(SimplePolygon)
add_subdirectory(PolygonWithOperators)
add_subdirectory(DynamicPolygon)

