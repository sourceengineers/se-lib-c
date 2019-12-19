#include <gtest/gtest.h>

extern "C" {
    #include "measurement/TemperatureCalculator.h"
    #include "measurement/MeasuredValues.h"
    #include "../driver/MockAdcDriver.h"
}

class TemperatureCalculatorTest : public ::testing::Test
{
protected:
    TemperatureCalculatorTest()
        : Test()
    {
    }

    void SetUp() override
    {
        _measuredValues.ambientTemperature = 0.0f;
        MockAdcDriver_init(&_mockAdc);
        _temperatureCalculator = TemperatureCalculator_create(MockAdcDriver_getIAdcDriverInterface(&_mockAdc),&_measuredValues.ambientTemperature,5);
    }

    void TearDown() override
    {
    	TemperatureCalculator_destroy(_temperatureCalculator);
    }

    virtual ~TemperatureCalculatorTest()
    {
    }

    TemperatureCalculator_Handle _temperatureCalculator;
    MockAdcDriverPrivateData _mockAdc;
    MeasuredValues _measuredValues;
};

TEST_F(TemperatureCalculatorTest, TemperatureCalculatorCreated)
{
	// test that the template was created
    EXPECT_NE(nullptr, _temperatureCalculator);
}

TEST_F(TemperatureCalculatorTest, TemperatureCalculatorOperation)
{
    // test that the template was created
    EXPECT_NE(nullptr, _temperatureCalculator);

    _mockAdc.analogValue[5] = 500u;
    IRunnable* runnable = TemperatureCalculator_getIRunnableInterface(_temperatureCalculator);
    EXPECT_NE(nullptr, runnable);

    runnable->run(runnable->handle);
    EXPECT_EQ(500*5-3,_measuredValues.ambientTemperature);
}
