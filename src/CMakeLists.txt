cmake_minimum_required(VERSION 2.8)

project (jarvis)

set (jarvis_VERSION_MAJOR 0)
set (jarvis_VERSION_MINOR 1)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

include_directories("${PROJECT_SOURCE_DIR}/testing")

add_library(jarvisjesting SHARED testing/suite.cpp testing/test.cpp testing/report.cpp)
add_executable(jarvisjests tests/main.cpp tests/testing/test_testing.cpp)

