cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project("implicit-scope-profiler" CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(isp)
add_subdirectory(example)

include(detect-gtest.cmake)
if(GTEST_FOUND)
    # To enable ctest usage
    enable_testing()
    add_subdirectory(tests)
endif()

