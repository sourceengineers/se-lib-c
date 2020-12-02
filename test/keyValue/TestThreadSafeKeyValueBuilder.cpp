#include <gtest/gtest.h>
#include <se-lib-c/keyValue/IKeyValueStore.h>

extern "C" {
    #include "se-lib-c/keyValue/ThreadSafeKeyValueBuilder.h"
    #include "osal/MockMutex.h"
}

static const uint16_t numberOfEntries = 5u;

static const KeyValue_Pair initialKeyValueList[] = {
        {.key = 1,  .value = {.type = KEY_TYPE_INT16, .data = {.i16 = -16}}},
        {.key = 2,  .value = {.type = KEY_TYPE_INT32, .data = {.i32 = -32}}},
        {.key = 3,  .value = {.type = KEY_TYPE_UINT16, .data = {.ui16 = 16u}}},
        {.key = 4,  .value = {.type = KEY_TYPE_UINT32, .data = {.ui32 = 32u}}},
        {.key = 5,  .value = {.type = KEY_TYPE_FLOAT, .data = {.f = 0.0f}}}
};

class ThreadSafeKeyValueBuilderTest : public ::testing::Test
{
protected:
    ThreadSafeKeyValueBuilderTest()
        : Test()
    {
    }

    void SetUp() override
    {

        // init Mutex, use Mock
        MockMutexPrivateData _mockMutexPrivateData;
        MockMutex_init(&_mockMutexPrivateData);
        IMutex* _mutex = MockMutex_getIMutexInterface(&_mockMutexPrivateData);


        _threadSafeKeyValueBuilder = ThreadSafeKeyValueBuilder_create(numberOfEntries, initialKeyValueList, _mutex); // TODO: remove hardcoded list size

        _iKeyValueStore = ThreadSafeKeyValueBuilder_getIKeyValueStoreInterface(_threadSafeKeyValueBuilder);
    }

    void TearDown() override
    {
        ThreadSafeKeyValueBuilder_destroy(_threadSafeKeyValueBuilder);
    }

    virtual ~ThreadSafeKeyValueBuilderTest()
    {
    }

    Builder_Handle _threadSafeKeyValueBuilder;
    const IKeyValueStore* _iKeyValueStore;
};

TEST_F(ThreadSafeKeyValueBuilderTest, BuilderCreated)
{
	// test that the template was created
    EXPECT_NE(nullptr, _threadSafeKeyValueBuilder);
    EXPECT_NE(nullptr, _iKeyValueStore);
}

TEST_F(ThreadSafeKeyValueBuilderTest, SimpleTest)
{
    KeyValue_Value kv_value;
    EXPECT_EQ(true, _iKeyValueStore->get(_iKeyValueStore->handle, 1u, &kv_value));
    EXPECT_EQ(initialKeyValueList->value.data.i16, kv_value.data.i16);
}

TEST_F(ThreadSafeKeyValueBuilderTest, CheckInitialValues)
{
    ASSERT_NE(nullptr, _iKeyValueStore);

    KeyValue_Value kv_value_get;
    // first element must be int16
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, 1u, &kv_value_get));
    EXPECT_EQ(initialKeyValueList[0].value.type, kv_value_get.type);
    EXPECT_EQ(initialKeyValueList[0].value.data.i16, kv_value_get.data.i16);

    // second element must be int32
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, 2u, &kv_value_get));
    EXPECT_EQ(initialKeyValueList[1].value.type, kv_value_get.type);
    EXPECT_EQ(initialKeyValueList[1].value.data.i32, kv_value_get.data.i32);

    // third element must be uint16
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, 3u, &kv_value_get));
    EXPECT_EQ(initialKeyValueList[2].value.type, kv_value_get.type);
    EXPECT_EQ(initialKeyValueList[2].value.data.ui16, kv_value_get.data.ui16);

    // forth element must be uint32
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, 4u, &kv_value_get));
    EXPECT_EQ(initialKeyValueList[3].value.type, kv_value_get.type);
    EXPECT_EQ(initialKeyValueList[3].value.data.ui32, kv_value_get.data.ui32);

    // fifth element (hehe) must be float
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, 5u, &kv_value_get));
    EXPECT_EQ(initialKeyValueList[4].value.type, kv_value_get.type);
    EXPECT_EQ(initialKeyValueList[4].value.data.f, kv_value_get.data.f);

}

TEST_F(ThreadSafeKeyValueBuilderTest, SetValue)
{
    ASSERT_NE(nullptr, _iKeyValueStore);

    KeyValue_Value kv_value_set = {.type = KEY_TYPE_FLOAT, .data = {.f = -0.1f}};
    KeyValue_Value kv_value_get;

    // set value
    EXPECT_TRUE(_iKeyValueStore->set(_iKeyValueStore->handle, 1u, kv_value_set));
    // check if set worked
    EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, 1u, &kv_value_get));
    EXPECT_EQ(kv_value_set.type, kv_value_get.type);
    EXPECT_EQ(kv_value_set.data.f, kv_value_get.data.f);
}

TEST_F(ThreadSafeKeyValueBuilderTest, InvalidKeySet)
{
    ASSERT_NE(nullptr, _iKeyValueStore);

    KeyValue_Value kv_value_set = {.type = KEY_TYPE_FLOAT, .data = {.f = -0.1f}};

    // set value
    EXPECT_FALSE(_iKeyValueStore->set(_iKeyValueStore->handle, 0u, kv_value_set));
    EXPECT_FALSE(_iKeyValueStore->set(_iKeyValueStore->handle, numberOfEntries+1, kv_value_set));
}

TEST_F(ThreadSafeKeyValueBuilderTest, InvalidKeyGet)
{
    ASSERT_NE(nullptr, _iKeyValueStore);
    KeyValue_Value kv_value_get;

    EXPECT_FALSE(_iKeyValueStore->get(_iKeyValueStore->handle, 0u, &kv_value_get));
    EXPECT_FALSE(_iKeyValueStore->get(_iKeyValueStore->handle, 6u, &kv_value_get));


}