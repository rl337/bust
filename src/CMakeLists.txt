cmake_minimum_required(VERSION 2.8)

project (jarvis)

set (jarvis_VERSION_MAJOR 0)
set (jarvis_VERSION_MINOR 1)
set (CMAKE_MACOSX_RPATH 1)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

include_directories("${PROJECT_SOURCE_DIR}/testing")
include_directories("${PROJECT_SOURCE_DIR}/math")

add_library(jarvistesting SHARED testing/suite.cpp testing/test.cpp testing/report.cpp)
add_library(jarvismath SHARED math/bitsets.cpp )
add_executable(jarvistests tests/main.cpp tests/testing/test_testing.cpp tests/math/test_bitsets.cpp)
target_link_libraries(jarvistests jarvismath jarvistesting)

