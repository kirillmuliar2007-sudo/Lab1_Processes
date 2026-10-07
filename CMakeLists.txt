cmake_minimum_required(VERSION 3.10)
project(Lab1_Processes)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Creator Creator/Creator.cpp)
add_executable(Reporter Reporter/Reporter.cpp)
add_executable(Main Main/Main.cpp)

set_target_properties(Creator PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(Reporter PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(Main PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
              
add_dependencies(Main Creator Reporter)