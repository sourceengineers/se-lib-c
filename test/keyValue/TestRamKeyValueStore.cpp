#include <gtest/gtest.h>

#define NUMBER_OF_ENTRIES 5u
extern "C" {
#include "se-lib-c/keyValue/RamKeyValueStore.h"
}

class RamKeyValueStoreTest : public ::testing::Test {
protected:
    RamKeyValueStoreTest()
            : Test() {
    }

    void SetUp() override {
        _ramKeyValueStore = RamKeyValueStore_create(
                NUMBER_OF_ENTRIES);
        iKeyValueStore = Runnable_getIKeyValueStoreInterface(_ramKeyValueStore);

    }

    void TearDown() override {
        RamKeyValueStore_destroy(_ramKeyValueStore);
    }

    virtual ~RamKeyValueStoreTest() {
    }

    RamKeyValueStore_Handle _ramKeyValueStore;
    IKeyValueStore *iKeyValueStore;
};

TEST_F(RamKeyValueStoreTest, RamKeyValueStoreCreated) {
    // test that the template was created
    EXPECT_NE(nullptr, _ramKeyValueStore);
    EXPECT_NE(nullptr, iKeyValueStore);
    // TODO: can I test if all cells of KeyValueArray are set to 0?


}

TEST_F(RamKeyValueStoreTest, TestInt16)
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
        // add a int16 value with key
        EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, key, value_int16));
        // test get
        // get value for key
        EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_int16.type, kv_value.type);
        EXPECT_EQ(value_int16.data.i16, kv_value.data.i16);
        // test set
        value_int16.data.i16++;
        // set value
        EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, key, value_int16));
        // get value for key
        EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_int16.type, kv_value.type);
        EXPECT_EQ(value_int16.data.i16, kv_value.data.i16);
    }
}

TEST_F(RamKeyValueStoreTest, TestInt32)
{
    // init
    KeyValue_Data kv_data = {.i32 = 0};
    KeyValue_Value kv_value = {KEY_TYPE_NONE, kv_data};
    // test int32
    kv_data = {.i32 = -32};
    KeyValue_Value value_int32;
    value_int32.type = KEY_TYPE_INT32;
    value_int32.data.i32 = kv_data.i32;

    for (uint16_t key = 1u; key <= NUMBER_OF_ENTRIES; key++)
    {
        // test add
        // add a int32 value with key
        EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, key, value_int32));
        // test get
        // get value for key
        EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_int32.type, kv_value.type);
        EXPECT_EQ(value_int32.data.i32, kv_value.data.i32);
        // test set
        value_int32.data.i32++;
        // set value
        EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, key, value_int32));
        // get value for key
        EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_int32.type, kv_value.type);
        EXPECT_EQ(value_int32.data.i32, kv_value.data.i32);
    }
}

TEST_F(RamKeyValueStoreTest, TestUInt16)
{
    // init
    KeyValue_Data kv_data = {.i32 = 0};
    KeyValue_Value kv_value = {KEY_TYPE_NONE, kv_data};
    // test uint16
    kv_data = {.ui16 = 16};
    KeyValue_Value value_uint16;
    value_uint16.type = KEY_TYPE_UINT16;
    value_uint16.data.ui16 = kv_data.ui16;

    for (uint16_t key = 1u; key <= NUMBER_OF_ENTRIES; key++)
    {
        // test add
        // add a uint16 value with key
        EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, key, value_uint16));
        // test get
        // get value for key
        EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_uint16.type, kv_value.type);
        EXPECT_EQ(value_uint16.data.ui16, kv_value.data.ui16);
        // test set
        value_uint16.data.ui16++;
        // set value
        EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, key, value_uint16));
        // get value for key
        EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_uint16.type, kv_value.type);
        EXPECT_EQ(value_uint16.data.ui16, kv_value.data.ui16);
    }
}

TEST_F(RamKeyValueStoreTest, TestUInt32)
{
    // init
    KeyValue_Data kv_data = {.i32 = 0};
    KeyValue_Value kv_value = {KEY_TYPE_NONE, kv_data};
    // test uint32
    kv_data = {.ui32 = 32};
    KeyValue_Value value_uint32;
    value_uint32.type = KEY_TYPE_UINT32;
    value_uint32.data.ui32 = kv_data.ui32;

    for (uint16_t key = 1u; key <= NUMBER_OF_ENTRIES; key++)
    {
        // test add
        // add a uint32 value with key
        EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, key, value_uint32));
        // test get
        // get value for key
        EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_uint32.type, kv_value.type);
        EXPECT_EQ(value_uint32.data.ui32, kv_value.data.ui32);
        // test set
        value_uint32.data.ui32++;
        // set value
        EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, key, value_uint32));
        // get value for key
        EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_uint32.type, kv_value.type);
        EXPECT_EQ(value_uint32.data.ui32, kv_value.data.ui32);
    }
}

TEST_F(RamKeyValueStoreTest, TestFloat)
{
    // init
    KeyValue_Data kv_data = {.i32 = 0};
    KeyValue_Value kv_value = {KEY_TYPE_NONE, kv_data};
    // test float
    kv_data = {.f = 0.0f};
    KeyValue_Value value_float;
    value_float.type = KEY_TYPE_FLOAT;
    value_float.data.f = kv_data.f;

    for (uint16_t key = 1u; key <= NUMBER_OF_ENTRIES; key++)
    {
        // test add
        // add a float value with key
        EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, key, value_float));
        // test get
        // get value for key
        EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_float.type, kv_value.type);
        EXPECT_EQ(value_float.data.f, kv_value.data.f);
        // test set
        value_float.data.f++;
        // set value
        EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, key, value_float));
        // get value for key
        EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_float.type, kv_value.type);
        EXPECT_EQ(value_float.data.f, kv_value.data.f);
    }
}
TEST_F(RamKeyValueStoreTest, TestInvalidKeys) {
    // TEST ADD AND GET
    // init
    KeyValue_Data kv_data = {.i32 = 0};
    KeyValue_Value kv_value = {KEY_TYPE_NONE, kv_data};

    KeyValue_Value value_int16;
    value_int16.type = KEY_TYPE_INT16;
    value_int16.data.i16 = kv_data.i16;

    // test add with invalid keys
    EXPECT_EQ(false, RamKeyValueStore_add(_ramKeyValueStore, 0u, value_int16));

    // test get with invalid keys
    EXPECT_EQ(false, iKeyValueStore->get(iKeyValueStore->handle, 6u, &kv_value));
    EXPECT_EQ(false, iKeyValueStore->get(iKeyValueStore->handle, 0u, &kv_value));

    // test set with invalid key
    EXPECT_EQ(false, iKeyValueStore->set(iKeyValueStore->handle, 6u, value_int16));
    EXPECT_EQ(false, iKeyValueStore->set(iKeyValueStore->handle, 0u, value_int16));

}

TEST_F(RamKeyValueStoreTest, TestFullArray) {
    // init
    KeyValue_Data kv_data = {.i32 = 0};
    KeyValue_Value kv_value = {KEY_TYPE_NONE, kv_data};
    // test int16
    kv_data = {.i16 = -16};
    KeyValue_Value value_int16;
    value_int16.type = KEY_TYPE_INT16;
    value_int16.data.i16 = kv_data.i16;
    // fill array
    for (uint16_t key = 1u; key <= NUMBER_OF_ENTRIES; key++)
    {
        // add a int16 value with key
        EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, key, value_int16));
    }
    // array is full, try to add another element
    EXPECT_EQ(false, RamKeyValueStore_add(_ramKeyValueStore, NUMBER_OF_ENTRIES+1, value_int16));
}

TEST_F(RamKeyValueStoreTest, TestKeyNotUnique) {
    // init
    KeyValue_Data kv_data = {.i32 = 0};
    KeyValue_Value kv_value = {KEY_TYPE_NONE, kv_data};
    // test int16
    kv_data = {.i16 = -16};
    KeyValue_Value value_int16;
    value_int16.type = KEY_TYPE_INT16;
    value_int16.data.i16 = kv_data.i16;

    uint16_t key = 1u;
    // add element with key to array
    EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, key, value_int16));
    // use same key and try to add another element
    EXPECT_EQ(false, RamKeyValueStore_add(_ramKeyValueStore, key, value_int16));
}

TEST_F(RamKeyValueStoreTest, AllTypes) {

    // init
    KeyValue_Data kv_data = {.i32 = 0};
    KeyValue_Value kv_value = {KEY_TYPE_NONE, kv_data};

    // test add and get

    // int16
    kv_data = {.i16 = -16};
    KeyValue_Value value_int16;
    value_int16.type = KEY_TYPE_INT16;
    value_int16.data.i16 = kv_data.i16;
    // add a int16 value with key 1
    EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, 1u, value_int16));
    // get value for key 1
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 1u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_int16.type, kv_value.type);
    EXPECT_EQ(value_int16.data.i16, kv_value.data.i16);

    // int32
    kv_data.i32 = -32;
    KeyValue_Value value_int32; // = {KEY_TYPE_INT32, kv_data};
    value_int32.type = KEY_TYPE_INT32;
    value_int32.data.i32 = kv_data.i32;
    EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, 2u, value_int32));
    // get value for key 2
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 2u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_int32.type, kv_value.type);
    EXPECT_EQ(value_int32.data.i32, kv_value.data.i32);

    // uint16
    kv_data.ui16 = 16u;
    KeyValue_Value value_uint16; // = {KEY_TYPE_UINT16, kv_data};
    value_uint16.type = KEY_TYPE_UINT16;
    value_uint16.data.ui16 = kv_data.ui16;
    // add a uint16 value with key 3
    EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, 3u, value_uint16));
    // get value for key 3
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 3u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_uint16.type, kv_value.type);
    EXPECT_EQ(value_uint16.data.ui16, kv_value.data.ui16);

    // uint32
    kv_data.ui32 = 32u;
    KeyValue_Value value_uint32; // = {KEY_TYPE_UINT32, kv_data};
    value_uint32.type = KEY_TYPE_UINT32;
    value_uint32.data.ui32 = kv_data.ui32;
    // add a uint32 value with key 4
    EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, 4u, value_uint32));
    // get value for key 4
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 4u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_uint32.type, kv_value.type);
    EXPECT_EQ(value_uint32.data.ui32, kv_value.data.ui32);

    // float
    kv_data.f = 0.0f;
    KeyValue_Value value_float; // = {KEY_TYPE_FLOAT, kv_data};
    value_float.type = KEY_TYPE_FLOAT;
    value_float.data.f = kv_data.f;
    // add a float value with key 5
    EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, 5u, value_float));
    // get value for key 5
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 5u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_float.type, kv_value.type);
    EXPECT_EQ(value_float.data.f, kv_value.data.f);

    // test set

    // set key 1 to value_int32
    EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, 1u, value_int32));
    // get key 1, should be value_int32
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 1u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_int32.type, kv_value.type);
    EXPECT_EQ(value_int32.data.i32, kv_value.data.i32);

    // set key 2 to value_uint16
    EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, 2u, value_uint16));
    // get key 2, should be value_uint16
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 2u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_uint16.type, kv_value.type);
    EXPECT_EQ(value_uint16.data.ui16, kv_value.data.ui16);

    // set key 3 to value_uint32
    EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, 3u, value_uint32));
    // get key 3, should be value_uint32
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 3u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_uint32.type, kv_value.type);
    EXPECT_EQ(value_uint32.data.ui32, kv_value.data.ui32);

    // set key 4 to value_float
    EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, 4u, value_float));
    // get key 4 should be value_float
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 4u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_float.type, kv_value.type);
    EXPECT_EQ(value_float.data.f, kv_value.data.f);

    // set key 5 to value_int16
    EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, 5u, value_int16));
    // get key 5 should be value_int16
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 5u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_int16.type, kv_value.type);
    EXPECT_EQ(value_int16.data.i16, kv_value.data.i16);
}
