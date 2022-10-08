cmake_minimum_required(VERSION 3.22)
project(SimplePolygonTests)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(TESTS_FILES SimplePolygonTest.cpp)
add_executable(runUnitTesting ${TESTS_FILES})

target_link_libraries(runUnitTesting gtest gtest_main)
target_link_libraries(runUnitTesting SimplePolygon)