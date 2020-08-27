#include <gtest/gtest.h>

#define NUMBER_OF_ENTRIES 5u

extern "C" {
#include "se-lib-c/keyValue/ThreadSafeKeyValueStore.h"
#include "se-lib-c/keyValue/RamKeyValueStore.h"
#include "../osal/MockMutex.h"
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
        MockMutex_init(&_mockMutexPrivateData);
        _mutex = MockMutex_getIMutexInterface(&_mockMutexPrivateData);
        _ramKeyValueStore = RamKeyValueStore_create(NUMBER_OF_ENTRIES);
        _iKeyValueStore = Runnable_getIKeyValueStoreInterface(_ramKeyValueStore);
        _threadSafeKeyValueStore = ThreadSafeKeyValueStore_create(_iKeyValueStore, _mutex);
        _iKeyValueStore = Runnable_getIThreadSafeKeyValueStoreInterface(_threadSafeKeyValueStore);
    }

    void TearDown() override
    {
    	ThreadSafeKeyValueStore_destroy(_threadSafeKeyValueStore);
    }

    virtual ~ThreadSafeKeyValueStoreTest()
    {
    }
    RamKeyValueStore_Handle _ramKeyValueStore;
    IKeyValueStore* _iKeyValueStore;
    MockMutexPrivateData _mockMutexPrivateData;
    IMutex* _mutex;
    ThreadSafeKeyValueStore_Handle _threadSafeKeyValueStore;
};

TEST_F(ThreadSafeKeyValueStoreTest, ThreadSafeKeyValueStoreCreated)
{
	// test that the template was created
    EXPECT_NE(nullptr, _threadSafeKeyValueStore);
    EXPECT_NE(nullptr, _mutex);
    EXPECT_NE(nullptr, _iKeyValueStore);
}

TEST_F(ThreadSafeKeyValueStoreTest, TestInt16) // generic test to see if get set works
{
    // init
    KeyValue_Data kv_data = {.i32 = 0};
    KeyValue_Value kv_value = {KEY_TYPE_NONE, kv_data};
    // test int16
    kv_data = {.i16 = -16};
    KeyValue_Value value_int16;
    value_int16.type = KEY_TYPE_INT16;
    value_int16.data.i16 = kv_data.i16;

    for (uint16_t key = 1u; key <= NUMBER_OF_ENTRIES; key++)
    {
        // test add
        // add a int16 value with key, not thread safe!
        EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, key, value_int16));
        // test get
        // get value for key
        EXPECT_EQ(true, _iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_int16.type, kv_value.type);
        EXPECT_EQ(value_int16.data.i16, kv_value.data.i16);
        // test set
        value_int16.data.i16++;
        // set value
        EXPECT_EQ(true, _iKeyValueStore->set(_iKeyValueStore->handle, key, value_int16));
        // get value for key
        EXPECT_EQ(true, _iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_int16.type, kv_value.type);
        EXPECT_EQ(value_int16.data.i16, kv_value.data.i16);
    }
}

TEST_F(ThreadSafeKeyValueStoreTest, TestMutexAvailability)
{
    // init
    KeyValue_Data kv_data = {.i32 = 0};
    KeyValue_Value kv_value = {KEY_TYPE_NONE, kv_data};
    // test int16
    kv_data = {.i16 = -16};
    KeyValue_Value value_int16;
    value_int16.type = KEY_TYPE_INT16;
    value_int16.data.i16 = kv_data.i16;

    // add entry
    EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, 1u, value_int16));
    // mutex unavailable
    _mockMutexPrivateData.isMutexAvailable = false;
    // test get when mutex is unavailable
    EXPECT_EQ(false, _iKeyValueStore->get(_iKeyValueStore->handle, 1u, &kv_value));
    // test set when mutex is unavailable
    EXPECT_EQ(false, _iKeyValueStore->set(_iKeyValueStore->handle, 1u, value_int16));
    // mutex available
    _mockMutexPrivateData.isMutexAvailable = true;
    // test get when mutex is available
    EXPECT_EQ(true, _iKeyValueStore->get(_iKeyValueStore->handle, 1u, &kv_value));
    // test set when mutex is available
    EXPECT_EQ(true, _iKeyValueStore->set(_iKeyValueStore->handle, 1u, value_int16));
}

TEST_F(ThreadSafeKeyValueStoreTest, TestMutexLocked)
{
    // init
    KeyValue_Data kv_data = {.i32 = 0};
    KeyValue_Value kv_value = {KEY_TYPE_NONE, kv_data};
    // test int16
    kv_data = {.i16 = -16};
    KeyValue_Value value_int16;
    value_int16.type = KEY_TYPE_INT16;
    value_int16.data.i16 = kv_data.i16;

    // add entry
    EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, 1u, value_int16));
    // mutex locked
    _mockMutexPrivateData.isMutexLocked = true;
    // test get when mutex is unavailable
    EXPECT_EQ(false, _iKeyValueStore->get(_iKeyValueStore->handle, 1u, &kv_value));
    // test set when mutex is unavailable
    EXPECT_EQ(false, _iKeyValueStore->set(_iKeyValueStore->handle, 1u, value_int16));
    // mutex unlocked
    _mockMutexPrivateData.isMutexLocked = false;
    // test get when mutex is available
    EXPECT_EQ(true, _iKeyValueStore->get(_iKeyValueStore->handle, 1u, &kv_value));
    // test set when mutex is available
    EXPECT_EQ(true, _iKeyValueStore->set(_iKeyValueStore->handle, 1u, value_int16));
}
