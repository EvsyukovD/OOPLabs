cmake_minimum_required(VERSION 3.22)

project(DialogLib)

set(DIALOG_LIB_FILES dialog.cpp)
add_library(DialogLib_1 STATIC ${DIALOG_LIB_FILES})