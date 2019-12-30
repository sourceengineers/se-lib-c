#include <gtest/gtest.h>

extern "C" {
    #include <se-lib-c/util/runnable/RunnableList.h>
    #include <util/runnable/MockRunnable.h>
}

class RunnableListTest : public ::testing::Test
{
protected:
    RunnableListTest()
        : Test()
    {
    }

    void SetUp() override
    {
        _runnableList = RunnableList_create();
    }

    void TearDown() override
    {
    	RunnableList_destroy(_runnableList);
    }

    virtual ~RunnableListTest()
    {
    }

    RunnableList_Handle _runnableList;
};

TEST_F(RunnableListTest, RunnableListAddAndRunElements)
{
	// test that the runnable-list was created
    EXPECT_NE(nullptr, _runnableList);

    // add first runnable
    MockRunnable runnable1;
    MockRunnable_init(&runnable1);
    RunnableList_add(_runnableList,MockRunnable_getIRunnableInterface(&runnable1));

    // add second runnable
    MockRunnable runnable2;
    MockRunnable_init(&runnable2);
    RunnableList_add(_runnableList,MockRunnable_getIRunnableInterface(&runnable2));

    IRunnable*  iRunnable = RunnableList_getIRunnableInterface(_runnableList);

    // run and check both runnable are run
    iRunnable->run(iRunnable);
    EXPECT_EQ(1,runnable1.callCountOfRun);
    EXPECT_EQ(1,runnable2.callCountOfRun);

    iRunnable->run(iRunnable);
    EXPECT_EQ(2,runnable1.callCountOfRun);
    EXPECT_EQ(2,runnable2.callCountOfRun);

}
