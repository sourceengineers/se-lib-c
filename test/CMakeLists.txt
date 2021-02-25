set(SE_LIB_C_TEST ${SE_LIB_C}-test)
set(SE_LIB_C_MOCKS ${SE_LIB_C}-mocks)

project(${SE_LIB_C_TEST})

include(cmake/UnitTestFiles.cmake)

if(NOT TARGET gtest)
    add_subdirectory(cmake/gtest)
endif()

add_test(${SE_LIB_C_TEST} ${SE_LIB_C_TEST})

#######################################################################################################################
# Build the mock library as its own lib
#######################################################################################################################
add_library(${SE_LIB_C_MOCKS} STATIC ${SE_LIB_C_MOCKS_SOURCES})

add_library(se-lib::c::mock ALIAS ${SE_LIB_C_MOCKS})
target_link_libraries(${SE_LIB_C_MOCKS} INTERFACE se-lib::c::mock)
target_include_directories(${SE_LIB_C_MOCKS} PUBLIC .)

target_link_libraries(
        ${SE_LIB_C_MOCKS}
        PRIVATE
        se-lib::c)

#######################################################################################################################
# Add tests
#######################################################################################################################
add_executable(${SE_LIB_C_TEST}
        ${SE_LIB_C_UNIT_TESTS})

target_compile_options(${SE_LIB_C} PUBLIC -DUNIT_TEST --coverage)
target_include_directories(${SE_LIB_C_TEST} PRIVATE .)


target_link_libraries(
        ${SE_LIB_C_TEST}
        PRIVATE
        se-lib::c
        test::gtest
        se-lib::c::mock)
target_link_options(${SE_LIB_C} PUBLIC --coverage)
