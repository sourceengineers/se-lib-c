
set(SE_LIB_C_MOCKS
        ${SE_LIB_C_TEST_DIR}/util/runnable/MockRunnable.c
        ${SE_LIB_C_TEST_DIR}/stream/MockByteStream.c
        ${SE_LIB_C_TEST_DIR}/driver/MockAdcDriver.c
        ${SE_LIB_C_TEST_DIR}/osal/MockMutex.c
        )

set(SE_LIB_C_UNIT_TESTS
        ${SE_LIB_C_TEST_DIR}/container/FloatRingBuffer-test.cpp
        ${SE_LIB_C_TEST_DIR}/logger/LoggerTest.cpp
        ${SE_LIB_C_TEST_DIR}/keyValue/TestRamKeyValueStore.cpp
        ${SE_LIB_C_TEST_DIR}/keyValue/TestThreadSafeKeyValueStore.cpp
        ${SE_LIB_C_TEST_DIR}/keyValue/TestThreadSafeKeyValueBuilder.cpp
        #${SE_LIB_C_TEST_DIR}/logger/LoggerFactory-test.cpp
        ${SE_LIB_C_TEST_DIR}/monitoring/TestMaxCheck.cpp
        ${SE_LIB_C_TEST_DIR}/monitoring/TestMinCheck.cpp
        ${SE_LIB_C_TEST_DIR}/stream/Bytestream-test.cpp
        ${SE_LIB_C_TEST_DIR}/stream/Bytestream-test.cpp
        ${SE_LIB_C_TEST_DIR}/UnitTests.cpp
        ${SE_LIB_C_TEST_DIR}/util/runnable/TestRunnableList.cpp
        )