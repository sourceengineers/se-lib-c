#include <gtest/gtest.h>

extern "C" {
#include "se-lib-c/keyValue/ThreadSafeKeyValueStore.h"
#include "se-lib-c/keyValue/RamKeyValueStore.h"
#include "../osal/MockMutex.h"
}

static const uint16_t numberOfEntries = 5u;

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
        _ramKeyValueStore = RamKeyValueStore_create(numberOfEntries);
        _iKeyValueStore = RamKeyValueStore_getIKeyValueStoreInterface(_ramKeyValueStore);
        _threadSafeKeyValueStore = ThreadSafeKeyValueStore_create(_iKeyValueStore, _mutex);
        _iKeyValueStore = ThreadSafeKeyValueStore_getIKeyValueStoreInterface(_threadSafeKeyValueStore);
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

TEST_F(ThreadSafeKeyValueStoreTest, AllTypes) {
    // init
    KeyValue_Value kv_value_set;
    KeyValue_Value kv_value_get;
    uint16_t key;

    // INT16
    key = 1u;
    kv_value_set = {.type = KEY_TYPE_INT16, .data = {.i16 = -16}};
    // add
    EXPECT_TRUE(RamKeyValueStore_add(_ramKeyValueStore, key, kv_value_set));
    // get
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value_get));
    // compare with expected
    EXPECT_EQ(kv_value_set.type, kv_value_get.type);
    EXPECT_EQ(kv_value_set.data.i16, kv_value_get.data.i16);
    // set
    kv_value_set.data.i16++;
    EXPECT_TRUE(_iKeyValueStore->set(_iKeyValueStore->handle, key, kv_value_set));
    // get and compare with expected
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value_get));
    EXPECT_EQ(kv_value_set.type, kv_value_get.type);
    EXPECT_EQ(kv_value_set.data.i16, kv_value_get.data.i16);

    // INT32
    key = 2u;
    kv_value_set = {.type = KEY_TYPE_INT32, .data = {.i32 = -32}};
    // add
    EXPECT_TRUE(RamKeyValueStore_add(_ramKeyValueStore, key, kv_value_set));
    // get
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value_get));
    // compare with expected
    EXPECT_EQ(kv_value_set.type, kv_value_get.type);
    EXPECT_EQ(kv_value_set.data.i32, kv_value_get.data.i32);
    // set
    kv_value_set.data.i32++;
    EXPECT_TRUE(_iKeyValueStore->set(_iKeyValueStore->handle, key, kv_value_set));
    // get and compare with expected
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value_get));
    EXPECT_EQ(kv_value_set.type, kv_value_get.type);
    EXPECT_EQ(kv_value_set.data.i32, kv_value_get.data.i32);

    // UINT16
    key = 3u;
    kv_value_set = {.type = KEY_TYPE_UINT16, .data = {.ui16 = 16}};
    // add
    EXPECT_TRUE(RamKeyValueStore_add(_ramKeyValueStore, key, kv_value_set));
    // get
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value_get));
    // compare with expected
    EXPECT_EQ(kv_value_set.type, kv_value_get.type);
    EXPECT_EQ(kv_value_set.data.ui16, kv_value_get.data.ui16);
    // set
    kv_value_set.data.ui16++;
    EXPECT_TRUE(_iKeyValueStore->set(_iKeyValueStore->handle, key, kv_value_set));
    // get and compare with expected
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value_get));
    EXPECT_EQ(kv_value_set.type, kv_value_get.type);
    EXPECT_EQ(kv_value_set.data.ui16, kv_value_get.data.ui16);

    // UINT32
    key = 4u;
    kv_value_set = {.type = KEY_TYPE_UINT32, .data = {.i32 = 32}};
    // add
    EXPECT_TRUE(RamKeyValueStore_add(_ramKeyValueStore, key, kv_value_set));
    // get
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value_get));
    // compare with expected
    EXPECT_EQ(kv_value_set.type, kv_value_get.type);
    EXPECT_EQ(kv_value_set.data.ui32, kv_value_get.data.ui32);
    // set
    kv_value_set.data.ui32++;
    EXPECT_TRUE(_iKeyValueStore->set(_iKeyValueStore->handle, key, kv_value_set));
    // get and compare with expected
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value_get));
    EXPECT_EQ(kv_value_set.type, kv_value_get.type);
    EXPECT_EQ(kv_value_set.data.ui32, kv_value_get.data.ui32);

    // FLOAT
    key = 5u;
    kv_value_set = {.type = KEY_TYPE_FLOAT, .data = {.f = 0.1f}};
    // add
    EXPECT_TRUE(RamKeyValueStore_add(_ramKeyValueStore, key, kv_value_set));
    // get
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value_get));
    // compare with expected
    EXPECT_EQ(kv_value_set.type, kv_value_get.type);
    EXPECT_EQ(kv_value_set.data.f, kv_value_get.data.f);
    // set
    kv_value_set.data.f++;
    EXPECT_TRUE(_iKeyValueStore->set(_iKeyValueStore->handle, key, kv_value_set));
    // get and compare with expected
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value_get));
    EXPECT_EQ(kv_value_set.type, kv_value_get.type);
    EXPECT_EQ(kv_value_set.data.f, kv_value_get.data.f);
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
    EXPECT_TRUE( RamKeyValueStore_add(_ramKeyValueStore, 1u, value_int16));
    // mutex unavailable
    _mockMutexPrivateData.isMutexAvailable = false;
    // test get when mutex is unavailable
    EXPECT_FALSE( _iKeyValueStore->get(_iKeyValueStore->handle, 1u, &kv_value));
    // test set when mutex is unavailable
    EXPECT_FALSE( _iKeyValueStore->set(_iKeyValueStore->handle, 1u, value_int16));
    // mutex available
    _mockMutexPrivateData.isMutexAvailable = true;
    // test get when mutex is available
    EXPECT_TRUE( _iKeyValueStore->get(_iKeyValueStore->handle, 1u, &kv_value));
    // test set when mutex is available
    EXPECT_TRUE( _iKeyValueStore->set(_iKeyValueStore->handle, 1u, value_int16));
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
    EXPECT_TRUE( RamKeyValueStore_add(_ramKeyValueStore, 1u, value_int16));
    // mutex locked
    _mockMutexPrivateData.isMutexLocked = true;
    // test get when mutex is unavailable
    EXPECT_FALSE( _iKeyValueStore->get(_iKeyValueStore->handle, 1u, &kv_value));
    // test set when mutex is unavailable
    EXPECT_FALSE( _iKeyValueStore->set(_iKeyValueStore->handle, 1u, value_int16));
    // mutex unlocked
    _mockMutexPrivateData.isMutexLocked = false;
    // test get when mutex is available
    EXPECT_TRUE( _iKeyValueStore->get(_iKeyValueStore->handle, 1u, &kv_value));
    // test set when mutex is available
    EXPECT_TRUE(_iKeyValueStore->set(_iKeyValueStore->handle, 1u, value_int16));
}


TEST_F(ThreadSafeKeyValueStoreTest, InvalidKeySet)
{
    ASSERT_NE(nullptr, _iKeyValueStore);

    KeyValue_Value kv_value_set = {.type = KEY_TYPE_FLOAT, .data = {.f = -0.1f}};

    // set value
    EXPECT_FALSE(_iKeyValueStore->set(_iKeyValueStore->handle, 0u, kv_value_set));
    EXPECT_FALSE(_iKeyValueStore->set(_iKeyValueStore->handle, numberOfEntries + 1, kv_value_set));
}

TEST_F(ThreadSafeKeyValueStoreTest, InvalidKeyGet)
{
    ASSERT_NE(nullptr, _iKeyValueStore);
    KeyValue_Value kv_value_get;

    EXPECT_FALSE(_iKeyValueStore->get(_iKeyValueStore->handle, 0u, &kv_value_get));
    EXPECT_FALSE(_iKeyValueStore->get(_iKeyValueStore->handle, numberOfEntries + 1, &kv_value_get));
}
