#include <gtest/gtest.h>

extern "C" {
    #include <se-lib-c/monitoring/MinCheck.h>
}

class MinCheckTest : public ::testing::Test
{
protected:
    MinCheckTest()
        : Test()
    {
    }

    void SetUp() override
    {
        _valueToCheck = 0.0f;

        float tripLimit = 100.0f;
        uint16_t  tripTimeMs = 100;
        uint16_t  callInvervallMs = 10;
        _minCheck = MinCheck_create(&_valueToCheck,tripLimit,tripTimeMs,callInvervallMs);
        _checkable = MinCheck_getICheckableInterface(_minCheck);
        _runnable = MinCheck_getIRunnableInterface(_minCheck);

    }

    void TearDown() override
    {
    	MinCheck_destroy(_minCheck);
    }

    virtual ~MinCheckTest()
    {
    }

    MinCheck_Handle _minCheck;
    float _valueToCheck;
    ICheckable* _checkable;
    IRunnable* _runnable;
};

TEST_F(MinCheckTest, MinCheckCreated)
{
	// test that the MaxCheck was created
    EXPECT_NE(nullptr, _minCheck);
    EXPECT_NE(nullptr, _runnable);
    EXPECT_NE(nullptr, _checkable);
}

TEST_F(MinCheckTest, ActivatedMinCheckOperation)
{
    EXPECT_NE(nullptr, _minCheck);
    EXPECT_NE(nullptr, _runnable);
    EXPECT_NE(nullptr, _checkable);

    // set value above maximum
    _valueToCheck = 99.9f;

    // activate check
    _checkable->setActive(_checkable,true);

    // run 9 times, check must not trip
    for(int i = 0; i < 9; i++)
    {
        _runnable->run(_runnable);
        EXPECT_EQ(true,_checkable->isCheckOk(_checkable));
    }

    // the 10th time, the check must trip
    _runnable->run(_runnable);
    EXPECT_EQ(false,_checkable->isCheckOk(_checkable));

    // if value rises to trip-limit the check must be ok again
    _valueToCheck = 100.0f;
    _runnable->run(_runnable);
    EXPECT_EQ(true,_checkable->isCheckOk(_checkable));

}

TEST_F(MinCheckTest, InactiveMinCheckOperation)
{
    EXPECT_NE(nullptr, _minCheck);
    EXPECT_NE(nullptr, _runnable);
    EXPECT_NE(nullptr, _checkable);

    // set value above maximum
    _valueToCheck = 99.9f;

    // activate check
    _checkable->setActive(_checkable,false);

    // run 9 times, check must not trip
    for(int i = 0; i < 10; i++)
    {
        _runnable->run(_runnable);
        EXPECT_EQ(true,_checkable->isCheckOk(_checkable));
    }
}
