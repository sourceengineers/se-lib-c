
set(SE_LIB_C_TESTS_NAME ${SE_LIB_C_PROJECT_NAME}_TEST)

project(${SE_LIB_C_TESTS_NAME})

include(cmake/UnitTestFiles.cmake)

if(NOT TARGET gtest)
    add_subdirectory(cmake/gtest)
endif()

add_test(${SE_LIB_C_TESTS_NAME} ${SE_LIB_C_TESTS_NAME})

add_executable(${SE_LIB_C_TESTS_NAME}
        ${SE_LIB_C_UNIT_TESTS}
        ${SE_LIB_C_MOCKS}
        )

target_include_directories(${SE_LIB_C_TESTS_NAME} PRIVATE cmake-build-debug/gtest/googletest-src/googletest/include)
target_include_directories(${SE_LIB_C_TESTS_NAME} PRIVATE cmake-build-debug/gtest/googletest-src/googlemock/include)
target_include_directories(${SE_LIB_C_TESTS_NAME} PRIVATE ../include)
target_include_directories(${SE_LIB_C_TESTS_NAME} PRIVATE .)

target_link_libraries(
        ${SE_LIB_C_TESTS_NAME}
        PRIVATE
        $<BUILD_INTERFACE:se-lib-c>
        $<BUILD_INTERFACE:gtest_main>)