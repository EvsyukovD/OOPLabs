cmake_minimum_required(VERSION 3.22)

project(Lab3)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_CPP_FILES main.cpp)

include_directories(lib/PolygonWithOperators lib/SimplePolygon lib/DynamicPolygon)

add_executable(Lab3 ${SOURCE_CPP_FILES})
add_subdirectory(lib)
add_subdirectory(tests)
target_link_libraries(Lab3 PolygonWithOperators SimplePolygon DynamicPolygon)
