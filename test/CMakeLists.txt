
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

target_include_directories(${SE_LIB_C_TEST} PRIVATE ${gmock_SOURCE_DIR}/include)
target_include_directories(${SE_LIB_C_TEST} PRIVATE ${gmock_SOURCE_DIR})
target_include_directories(${SE_LIB_C_TEST} PRIVATE ${gtest_SOURCE_DIR}/include)
target_include_directories(${SE_LIB_C_TEST} PRIVATE ${gtest_SOURCE_DIR})
target_include_directories(${SE_LIB_C_TEST} PRIVATE ../include)
target_include_directories(${SE_LIB_C_TEST} PRIVATE .)

target_link_libraries(
        ${SE_LIB_C_TEST}
        PRIVATE
        ${SE_LIB_C}
        gtest
        gtest_main
        pthread)