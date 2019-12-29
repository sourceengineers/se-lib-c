#include <gtest/gtest.h>

extern "C" {
    #include <se-lib-c/util/runnable/Runnable.h>
}

class RunnableTest : public ::testing::Test
{
protected:
    RunnableTest()
        : Test()
    {
    }

    void SetUp() override
    {
        _runnable = Runnable_create();
    }

    void TearDown() override
    {
    	Runnable_destroy(_runnable);
    }

    virtual ~RunnableTest()
    {
    }

    Runnable_Handle _runnable;
};

TEST_F(RunnableTest, TestRunRunnable)
{
	// test that the template was created
    EXPECT_NE(nullptr, _runnable);

    // get interface from concrete class
    IRunnable* iRunnable = Runnable_getIRunnableInterface(_runnable);
    EXPECT_NE(nullptr, _runnable);

    // run interface
    iRunnable->run(iRunnable->handle);
    EXPECT_EQ(1, Runnable_getCallCountOfRun(_runnable));

    iRunnable->run(iRunnable->handle);
    EXPECT_EQ(2, Runnable_getCallCountOfRun(_runnable));

    iRunnable->run(iRunnable->handle);
    EXPECT_EQ(3, Runnable_getCallCountOfRun(_runnable));
}
