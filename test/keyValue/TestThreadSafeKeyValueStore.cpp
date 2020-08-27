#include <gtest/gtest.h>

extern "C" {
    #include "../../src/keyValue/ThreadSafeKeyValueStore.h"

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
