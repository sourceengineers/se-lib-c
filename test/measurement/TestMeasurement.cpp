#include <gtest/gtest.h>

extern "C" {
    #include <measurement/MeasurementFactory.h>
    #include "../driver/MockAdcDriver.h"
}

class MeasurementTest : public ::testing::Test
{
protected:
    MeasurementTest()
        : Test()
    {
    }

    void SetUp() override
    {
        MockAdcDriver_init(&_mockAdc);

        MeasurementFactory_initialize(&_mockAdc.parent);
        _runnables = MeasurementFactory_getRunnable();
        _measuredValues = MeasurementFactory_getMeasuredValuesSharedObject();
    }

    void TearDown() override
    {
    	MeasurementFactory_destroy();
    }

    virtual ~MeasurementTest()
    {
    }

    MockAdcDriverPrivateData _mockAdc;
    const MeasuredValues* _measuredValues;
    IRunnable* _runnables;
};

TEST_F(MeasurementTest, MeasuredValuesCreated)
{
    // test that the MeasurementComponent was created
    EXPECT_NE(nullptr, _measuredValues);
    EXPECT_NE(nullptr, _runnables);
}

TEST_F(MeasurementTest, MeasuredValuesOperation)
{
    // test that the MeasurementComponent was created
    EXPECT_NE(nullptr, _measuredValues);
    EXPECT_NE(nullptr, _runnables);

    // initialize adc to know value
    _mockAdc.analogValue[1] = 123u;
    _mockAdc.analogValue[2] = 500u;
    _mockAdc.analogValue[3] = 500u;
    _mockAdc.analogValue[4] = 500u;
    _mockAdc.analogValue[5] = 500u;

    // run all runnables created by measurement
    _runnables->run(_runnables->handle);

    // check that all temperatures were calculated
    EXPECT_EQ(500*5-3,_measuredValues->ambientTemperature);
    EXPECT_EQ(500*5-3,_measuredValues->igbtTemperature1);
    EXPECT_EQ(500*5-3,_measuredValues->igbtTemperature2);
    EXPECT_EQ(500*5-3,_measuredValues->cpuTemperature);
}
