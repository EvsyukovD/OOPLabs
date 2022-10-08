cmake_minimum_required(VERSION 3.22)
project(PolygonWithOperatorsTests)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(POLYGON_OPER_TESTS_FILES PolygonWithOperatorsTest.cpp)
add_executable(PolygonOperUnitTesting ${POLYGON_OPER_TESTS_FILES})

target_link_libraries(PolygonOperUnitTesting gtest gtest_main)
target_link_libraries(PolygonOperUnitTesting PolygonWithOperators)