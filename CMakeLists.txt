cmake_minimum_required(VERSION 3.29)
project(Project3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project3 main.cpp
        Graph.h
        Graph.cpp)
set(FLTK_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/fltk-1.4.2-source/fltk/fltk-1.4.2")

# Add FLTK as a subdirectory
target_link_libraries(Project3 PRIVATE fltk)
add_subdirectory(${FLTK_SOURCE_DIR})
