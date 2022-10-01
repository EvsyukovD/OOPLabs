cmake_minimum_required(VERSION 3.22)

project(DialogLib)

set(DIALOG_LIB_FILES dialog.cpp)
add_library(DialogLib STATIC ${DIALOG_LIB_FILES})