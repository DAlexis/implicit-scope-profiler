cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project("implicit-scope-profiler" CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 14)

set(RAPIDJSON_BUILD_EXAMPLES OFF)
set(RAPIDJSON_BUILD_TESTS OFF)
set(RAPIDJSON_BUILD_DOC OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wimplicit-fallthrough=0")
add_subdirectory(3rdparty/rapidjson-1.1.0)

add_subdirectory(isp)
add_subdirectory(example)


include(detect-gtest.cmake)
if(GTEST_FOUND)
    # To enable ctest usage
    enable_testing()
    add_subdirectory(tests)
endif()

