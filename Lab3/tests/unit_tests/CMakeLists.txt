cmake_minimum_required(VERSION 3.22)
project(unit_tests)
add_subdirectory(PolygonWithOperatorsTests)
add_subdirectory(SimplePolygonTests)
add_subdirectory(DynamicPolygonTests)
include_directories(../../lib/SimplePolygon ../../lib/PolygonWithOperators ../../lib/DynamicPolygon)