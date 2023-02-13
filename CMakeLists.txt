cmake_minimum_required(VERSION 3.16)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

project(gccrs-unicode VERSION 0.1)

add_executable(gccrs-unicode src/main.cc)

target_include_directories(gccrs-unicode PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(gccrs-unicode PUBLIC ${PROJECT_SOURCE_DIR}/src)
