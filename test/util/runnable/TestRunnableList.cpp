#include <gtest/gtest.h>

extern "C" {
    #include "util/runnable/RunnableList.h"
    #include "util/runnable//Runnable.h"
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
    Runnable_Handle runnable1 = Runnable_create();
    EXPECT_NE(nullptr, runnable1);
    RunnableList_add(_runnableList,Runnable_getIRunnableInterface(runnable1));

    // add second runnable
    Runnable_Handle runnable2 = Runnable_create();
    EXPECT_NE(nullptr, runnable2);
    RunnableList_add(_runnableList,Runnable_getIRunnableInterface(runnable2));

    IRunnable*  iRunnable = RunnableList_getIRunnableInterface(_runnableList);

    // run and check both runnable are run
    iRunnable->run(iRunnable->handle);
    EXPECT_EQ(1,Runnable_getCallCountOfRun(runnable1));
    EXPECT_EQ(1,Runnable_getCallCountOfRun(runnable2));

    iRunnable->run(iRunnable->handle);
    EXPECT_EQ(2,Runnable_getCallCountOfRun(runnable1));
    EXPECT_EQ(2,Runnable_getCallCountOfRun(runnable2));

    //clean up
    Runnable_destroy(runnable1);
    Runnable_destroy(runnable2);

}
