project(basic_tests)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(SOURCE_CPP_TEST_FILES VerzieraTest.cpp)
add_executable(runUnitTesting ${SOURCE_CPP_TEST_FILES})

target_link_libraries(runUnitTesting gtest gtest_main)
target_link_libraries(runUnitTesting Lab2Lib)
