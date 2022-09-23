cmake_minimum_required (VERSION 3.8)

project ("OOPLab1")

add_executable (OOPLab1 "OOPLab1.cpp" "OOPLab1.h" "functions.cpp"   "list.h" "list.cpp")


install(TARGETS OOPLab1 DESTINATION "ooplab1/bin")
