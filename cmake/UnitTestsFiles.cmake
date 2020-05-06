
# manage include directories
set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set(TEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../test)
set(TESTCONFIG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../config/test)

include_directories(
	${SRC_ROOT}
	${TEST_ROOT}
	${TESTCONFIG_ROOT}
)

# Add sourcecode
set(SE_LIB_C_SOURCES
		${SRC_ROOT}/container/ByteRingBuffer.c
		${SRC_ROOT}/container/FloatRingBuffer.c
		${SRC_ROOT}/container/IntRingBuffer.c
		${SRC_ROOT}/logger/Logger.c
		${SRC_ROOT}/logger/LoggerBuilder.c
		${SRC_ROOT}/monitoring/MaxCheck.c
		${SRC_ROOT}/monitoring/MinCheck.c
		${SRC_ROOT}/stream/BufferedByteStream.c
		${SRC_ROOT}/stream/BufferedFloatStream.c
		${SRC_ROOT}/stream/BufferedIntStream.c
		${SRC_ROOT}/util/runnable/RunnableList.c
)

# Add mocks
set(SE_LIB_C_MOCKS
	${TEST_ROOT}/util/runnable/MockRunnable.c
	${TEST_ROOT}/driver/MockAdcDriver.c
)

# Add tests
set(SE_LIB_C_UNIT_TESTS
		${TEST_ROOT}/container/FloatRingBuffer-test.cpp
		${TEST_ROOT}/logger/LoggerTest.cpp
		#${TEST_ROOT}/logger/LoggerFactory-test.cpp
		${TEST_ROOT}/monitoring/TestMaxCheck.cpp
		${TEST_ROOT}/monitoring/TestMinCheck.cpp
		${TEST_ROOT}/stream/Bytestream-test.cpp
		${TEST_ROOT}/util/runnable/TestRunnableList.cpp
)

