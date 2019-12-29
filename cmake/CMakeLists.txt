cmake_minimum_required (VERSION 3.5)
project (OopExamplesUnitTests)

# predefined symbols
add_definitions(-DUNIT_TEST)

# Download and unpack googletest at configure time
add_subdirectory(gtest)

#include directories
include_directories(cmake-build-debug/gtest/googletest-src/googletest/include)
include_directories(../include)

#include other file
include(UnitTestsFiles.cmake)

#C++ compiler settings
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "-g -O0 -Wall")

#C compiler settings
set(CMAKE_C_STANDARD 99)
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W")

# compile sources into object libary
add_library(SeLibCSourceLib OBJECT ${OOP_EXAMPLES_SOURCES})

# compile tests into object libary
add_library(SeLibCTestLib OBJECT ${OOP_EXAMPLES_UNIT_TESTS})

# compile object library and unit-test into application
add_executable(SeLibCUnitTests
	../src/UnitTests.cpp
	$<TARGET_OBJECTS:SeLibCSourceLib>
	$<TARGET_OBJECTS:SeLibCTestLib>
	)

# add google test at link-time (needs to be pre-installed)
target_link_libraries(SeLibCUnitTests gtest gtest_main pthread)



