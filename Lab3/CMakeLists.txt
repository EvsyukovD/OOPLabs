cmake_minimum_required(VERSION 3.22)

project(Lab3)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_CPP_FILES main.cpp)

add_subdirectory(lib)
include_directories(lib)
add_subdirectory(tests)

add_executable(Lab3 ${SOURCE_CPP_FILES})
target_link_libraries(Lab3 lib)
