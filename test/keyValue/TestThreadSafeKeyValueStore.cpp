#include <gtest/gtest.h>

extern "C" {
    #include "se-lib-c/keyValue/ThreadSafeKeyValueStore.h"
    #include "se-lib-c/osal/MockMutex.h"
}

class ThreadSafeKeyValueStoreTest : public ::testing::Test
{
protected:
    ThreadSafeKeyValueStoreTest()
        : Test()
    {
    }

    void SetUp() override
    {
        _threadSafeKeyValueStore = ThreadSafeKeyValueStore_create();
    }

    void TearDown() override
    {
    	ThreadSafeKeyValueStore_destroy(_threadSafeKeyValueStore);
    }

    virtual ~ThreadSafeKeyValueStoreTest()
    {
    }

    ThreadSafeKeyValueStore_Handle _threadSafeKeyValueStore;
};

TEST_F(ThreadSafeKeyValueStoreTest, ThreadSafeKeyValueStoreCreated)
{
	// test that the template was created
    EXPECT_NE(nullptr, _threadSafeKeyValueStore);
}
