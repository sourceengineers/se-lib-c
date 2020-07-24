
set(SE_LIB_C_MOCKS
        ${SE_LIB_C_TEST_DIR}/util/runnable/MockRunnable.c
        )

set(SE_LIB_C_UNIT_TESTS
        ${SE_LIB_C_TEST_DIR}/container/FloatRingBuffer-test.cpp
        #${SE_LIB_C_TEST_DIR}/logger/LoggerFactory-test.cpp
        ${SE_LIB_C_TEST_DIR}/monitoring/TestMaxCheck.cpp
        ${SE_LIB_C_TEST_DIR}/monitoring/TestMinCheck.cpp
        ${SE_LIB_C_TEST_DIR}/stream/Bytestream-test.cpp
        ${SE_LIB_C_TEST_DIR}/UnitTests.cpp
        ${SE_LIB_C_TEST_DIR}/util/runnable/TestRunnableList.cpp
        )