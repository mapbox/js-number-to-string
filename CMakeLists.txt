cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(js-number-to-string)


option(BUILD_EXAMPLES "Build examples" ON)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(src)
