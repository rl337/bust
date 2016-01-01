cmake_minimum_required(VERSION 2.8)

project (jarvis)

set (jarvis_VERSION_MAJOR 0)
set (jarvis_VERSION_MINOR 1)
set (CMAKE_MACOSX_RPATH 1)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

include_directories("${PROJECT_SOURCE_DIR}/testing")
include_directories("${PROJECT_SOURCE_DIR}/math")
include_directories("${PROJECT_SOURCE_DIR}/svg")

add_library(jv_testing SHARED
    testing/runner.cpp
    testing/suite.cpp
    testing/test.cpp
    testing/report.cpp
)

add_library(jv_math SHARED
    math/bitsets.cpp math/vector.cpp
)

add_library(jv_svg SHARED
    svg/svg.cpp
    svg/color.cpp
    svg/style.cpp
)

add_library(test_testing SHARED
    tests/testing/test_testing.cpp
)
target_link_libraries( test_testing jv_testing )

add_library(test_math SHARED
    tests/math/test_bitsets.cpp
    tests/math/test_vector.cpp
)
target_link_libraries( test_math
    jv_testing
    jv_math
)

add_library(test_svg SHARED
    tests/svg/test_svg.cpp
    tests/svg/test_color.cpp
)
target_link_libraries( test_svg
    jv_testing
)

add_executable(jv_tests
    tests/main.cpp
)

target_link_libraries( jv_tests
    jv_testing
    jv_svg
    test_testing
    test_math
    test_svg
)

