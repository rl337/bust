cmake_minimum_required(VERSION 2.8)

project (bust)

set (bust_VERSION_MAJOR 0)
set (bust_VERSION_MINOR 1)
set (CMAKE_MACOSX_RPATH 1)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wc++1z-extensions")

include_directories("${PROJECT_SOURCE_DIR}/testing")
include_directories("${PROJECT_SOURCE_DIR}/math")
include_directories("${PROJECT_SOURCE_DIR}/svg")
include_directories("${PROJECT_SOURCE_DIR}/png")
include_directories("${PROJECT_SOURCE_DIR}/util")

add_library(bust_testing SHARED
    testing/runner.cpp
    testing/suite.cpp
    testing/test.cpp
    testing/report.cpp
)

add_library(bust_util SHARED
    util/checksums.cpp
    util/zlib.cpp
    util/color.cpp
)

add_library(bust_math SHARED
    math/bitsets.cpp
    math/vector.cpp
)

add_library(bust_png SHARED
    png/png.cpp
)
target_link_libraries( bust_png bust_util )

add_library(bust_svg SHARED
    svg/svg.cpp
    svg/style.cpp
)

add_library(test_testing SHARED
    tests/testing/test_testing.cpp
    tests/testing/testing_suite.cpp
)
target_link_libraries( test_testing bust_testing )

add_library(test_util SHARED
    tests/util/test_checksums.cpp
    tests/util/test_zlib.cpp
    tests/util/test_color.cpp
    tests/util/util_suite.cpp
)
target_link_libraries( test_util bust_util bust_testing )

add_library(test_math SHARED
    tests/math/test_bitsets.cpp
    tests/math/test_vector.cpp
    tests/math/math_suite.cpp
)
target_link_libraries( test_math
    bust_testing
    bust_math
)

add_library(test_png SHARED
    tests/png/png_suite.cpp
    tests/png/test_png.cpp
)
target_link_libraries( test_png
    bust_testing
    bust_png
)

add_library(test_svg SHARED
    tests/svg/test_svg.cpp
    tests/svg/svg_suite.cpp
)
target_link_libraries( test_svg
    bust_testing
    bust_svg
    bust_png
)

add_executable(bust_tests
    tests/main.cpp
)

target_link_libraries( bust_tests
    test_testing
    test_math
    test_svg
    test_util
    test_png
)

add_executable(bust_colorbars
    cmds/colorbars/main.cpp
)

target_link_libraries( bust_colorbars
    bust_math
    bust_png
)
