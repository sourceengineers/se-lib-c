#include <gtest/gtest.h>

extern "C" {
    #include <se-lib-c/monitoring/MaxCheck.h>
}

class MaxCheckTest : public ::testing::Test
{
protected:
    MaxCheckTest()
        : Test()
    {
    }

    void SetUp() override
    {
        _valueToCheck = 0.0f;

        float tripLimit = 100.0f;
        uint16_t  tripTimeMs = 100;
        uint16_t  callInvervallMs = 10;
        _maxCheck = MaxCheck_create(&_valueToCheck,tripLimit,tripTimeMs,callInvervallMs);
        _checkable = MaxCheck_getICheckableInterface(_maxCheck);
        _runnable = MaxCheck_getIRunnableInterface(_maxCheck);

    }

    void TearDown() override
    {
    	MaxCheck_destroy(_maxCheck);
    }

    virtual ~MaxCheckTest()
    {
    }

    MaxCheck_Handle _maxCheck;
    float _valueToCheck;
    ICheckable* _checkable;
    IRunnable* _runnable;
};

TEST_F(MaxCheckTest, MaxCheckCreated)
{
	// test that the MaxCheck was created
    EXPECT_NE(nullptr, _maxCheck);
    EXPECT_NE(nullptr, _runnable);
    EXPECT_NE(nullptr, _checkable);
}

TEST_F(MaxCheckTest, ActivatedMaxCheckOperation)
{
    EXPECT_NE(nullptr, _maxCheck);
    EXPECT_NE(nullptr, _runnable);
    EXPECT_NE(nullptr, _checkable);

    // set value above maximum
    _valueToCheck = 100.1f;

    // activate check
    _checkable->setActive(_checkable->handle,true);

    // run 9 times, check must not trip
    for(int i = 0; i < 9; i++)
    {
        _runnable->run(_runnable->handle);
        EXPECT_EQ(true,_checkable->isCheckOk(_checkable->handle));
    }

    // the 10th time, the check must trip
    _runnable->run(_runnable->handle);
    EXPECT_EQ(false,_checkable->isCheckOk(_checkable->handle));

    // if value drops to trip-limit the check must be ok again
    _valueToCheck = 100.0f;
    _runnable->run(_runnable->handle);
    EXPECT_EQ(true,_checkable->isCheckOk(_checkable->handle));

}

TEST_F(MaxCheckTest, InactiveMaxCheckOperation)
{
    EXPECT_NE(nullptr, _maxCheck);
    EXPECT_NE(nullptr, _runnable);
    EXPECT_NE(nullptr, _checkable);

    // set value above maximum
    _valueToCheck = 100.1f;

    // activate check
    _checkable->setActive(_checkable->handle,false);

    // run 9 times, check must not trip
    for(int i = 0; i < 10; i++)
    {
        _runnable->run(_runnable->handle);
        EXPECT_EQ(true,_checkable->isCheckOk(_checkable->handle));
    }
}
