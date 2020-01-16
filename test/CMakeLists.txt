
set(SE_LIB_C_TEST ${SE_LIB_C}-test)

project(${SE_LIB_C_TEST})

include(cmake/UnitTestFiles.cmake)

if(NOT TARGET gtest)
    add_subdirectory(cmake/gtest)
endif()

add_test(${SE_LIB_C_TEST} ${SE_LIB_C_TEST})

add_executable(${SE_LIB_C_TEST}
        ${SE_LIB_C_UNIT_TESTS}
        ${SE_LIB_C_MOCKS}
        )

message(${CMAKE_CURRENT_BINARY_DIR}/test/cmake/gtest/googletest-src/googletest/include)
target_include_directories(${SE_LIB_C_TEST} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/cmake/gtest/googletest-src/googletest/include)
target_include_directories(${SE_LIB_C_TEST} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/cmake/gtest/googletest-src/googlemock/include)
target_include_directories(${SE_LIB_C_TEST} PRIVATE ../include)
target_include_directories(${SE_LIB_C_TEST} PRIVATE .)

target_link_libraries(
        ${SE_LIB_C_TEST}
        PRIVATE
        se-scope
        gtest_main
        pthread)