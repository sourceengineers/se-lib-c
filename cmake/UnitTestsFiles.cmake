
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
set(OOP_EXAMPLES_SOURCES
	${SRC_ROOT}/driver/AdcDriver.c
	${SRC_ROOT}/measurement/TemperatureCalculator.c
	${SRC_ROOT}/measurement/MeasurementFactory.c
	${SRC_ROOT}/util/runnable/Runnable.c
	${SRC_ROOT}/util/runnable/RunnableList.c
	${SRC_ROOT}/monitoring/MaxCheck.c
    ${TEST_ROOT}/util/runnable/MockRunnable.c
	${TEST_ROOT}/driver/MockAdcDriver.c
)

# Add tests
set(OOP_EXAMPLES_UNIT_TESTS
	${TEST_ROOT}/util/runnable/TestRunnable.cpp
	${TEST_ROOT}/util/runnable/TestRunnableList.cpp
	${TEST_ROOT}/monitoring/TestMaxCheck.cpp
	${TEST_ROOT}/measurement/TestTemperatureCalculator.cpp
	${TEST_ROOT}/measurement/TestMeasurement.cpp
)

