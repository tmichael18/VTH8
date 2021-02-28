cmake_minimum_required(VERSION 3.9...3.19)
project(VTH8 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# build test driver
add_executable(unit_tests
  unit_tests.cpp
  test_functions.cpp
  functions.hpp
  functions.cpp)

# enable testing
include(CTest)
enable_testing()

# register Catch tests with cmake
include(Catch)
catch_discover_tests(unit_tests)
