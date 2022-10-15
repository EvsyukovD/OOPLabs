cmake_minimum_required(VERSION 3.22)
project(DynamicPolygonTests)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(DYN_POLYGON_TESTS_FILES DynamicPolygonTest.cpp)
add_executable(DynPolygonUnitTesting ${DYN_POLYGON_TESTS_FILES})

target_link_libraries(DynPolygonUnitTesting gtest gtest_main)
target_link_libraries(DynPolygonUnitTesting DynamicPolygon)