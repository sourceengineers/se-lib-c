#include <gtest/gtest.h>

#define numberOfEntries 5u
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
                numberOfEntries);
        _iKeyValueStore = RamKeyValueStore_getIKeyValueStoreInterface(_ramKeyValueStore);

    }

    void TearDown() override {
        RamKeyValueStore_destroy(_ramKeyValueStore);
    }

    virtual ~RamKeyValueStoreTest() {
    }

    RamKeyValueStore_Handle _ramKeyValueStore;
    IKeyValueStore *_iKeyValueStore;
};

TEST_F(RamKeyValueStoreTest, RamKeyValueStoreCreated) {
    // test that the template was created
    EXPECT_NE(nullptr, _ramKeyValueStore);
    EXPECT_NE(nullptr, _iKeyValueStore);
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

    for (uint16_t key = 1u; key <= numberOfEntries; key++)
    {
        // test add
        // add a int16 value with key
        EXPECT_TRUE(RamKeyValueStore_add(_ramKeyValueStore, key, value_int16));
        // test get
        // get value for key
        EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_int16.type, kv_value.type);
        EXPECT_EQ(value_int16.data.i16, kv_value.data.i16);
        // test set
        value_int16.data.i16++;
        // set value
        EXPECT_TRUE(_iKeyValueStore->set(_iKeyValueStore->handle, key, value_int16));
        // get value for key
        EXPECT_TRUE( _iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value));
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

    for (uint16_t key = 1u; key <= numberOfEntries; key++)
    {
        // test add
        // add a int32 value with key
        EXPECT_TRUE(RamKeyValueStore_add(_ramKeyValueStore, key, value_int32));
        // test get
        // get value for key
        EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_int32.type, kv_value.type);
        EXPECT_EQ(value_int32.data.i32, kv_value.data.i32);
        // test set
        value_int32.data.i32++;
        // set value
        EXPECT_TRUE( _iKeyValueStore->set(_iKeyValueStore->handle, key, value_int32));
        // get value for key
        EXPECT_TRUE( _iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value));
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

    for (uint16_t key = 1u; key <= numberOfEntries; key++)
    {
        // test add
        // add a uint16 value with key
        EXPECT_TRUE(RamKeyValueStore_add(_ramKeyValueStore, key, value_uint16));
        // test get
        // get value for key
        EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_uint16.type, kv_value.type);
        EXPECT_EQ(value_uint16.data.ui16, kv_value.data.ui16);
        // test set
        value_uint16.data.ui16++;
        // set value
        EXPECT_TRUE(_iKeyValueStore->set(_iKeyValueStore->handle, key, value_uint16));
        // get value for key
        EXPECT_TRUE( _iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value));
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

    for (uint16_t key = 1u; key <= numberOfEntries; key++)
    {
        // test add
        // add a uint32 value with key
        EXPECT_TRUE(RamKeyValueStore_add(_ramKeyValueStore, key, value_uint32));
        // test get
        // get value for key
        EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_uint32.type, kv_value.type);
        EXPECT_EQ(value_uint32.data.ui32, kv_value.data.ui32);
        // test set
        value_uint32.data.ui32++;
        // set value
        EXPECT_TRUE(_iKeyValueStore->set(_iKeyValueStore->handle, key, value_uint32));
        // get value for key
        EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value));
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

    for (uint16_t key = 1u; key <= numberOfEntries; key++)
    {
        // test add
        // add a float value with key
        EXPECT_TRUE(RamKeyValueStore_add(_ramKeyValueStore, key, value_float));
        // test get
        // get value for key
        EXPECT_TRUE(_iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value));
        // compare received with expected
        EXPECT_EQ(value_float.type, kv_value.type);
        EXPECT_EQ(value_float.data.f, kv_value.data.f);
        // test set
        value_float.data.f++;
        // set value
        EXPECT_TRUE(_iKeyValueStore->set(_iKeyValueStore->handle, key, value_float));
        // get value for key
        EXPECT_TRUE( _iKeyValueStore->get(_iKeyValueStore->handle, key, &kv_value));
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
    EXPECT_FALSE(RamKeyValueStore_add(_ramKeyValueStore, 0u, value_int16));

    // test get with invalid keys
    EXPECT_FALSE(_iKeyValueStore->get(_iKeyValueStore->handle, 6u, &kv_value));
    EXPECT_FALSE(_iKeyValueStore->get(_iKeyValueStore->handle, 0u, &kv_value));

    // test set with invalid key
    EXPECT_FALSE(_iKeyValueStore->set(_iKeyValueStore->handle, 6u, value_int16));
    EXPECT_FALSE(_iKeyValueStore->set(_iKeyValueStore->handle, 0u, value_int16));

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
    for (uint16_t key = 1u; key <= numberOfEntries; key++)
    {
        // add a int16 value with key
        EXPECT_TRUE( RamKeyValueStore_add(_ramKeyValueStore, key, value_int16));
    }
    // array is full, try to add another element
    EXPECT_FALSE( RamKeyValueStore_add(_ramKeyValueStore, numberOfEntries + 1, value_int16));
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
    EXPECT_TRUE( RamKeyValueStore_add(_ramKeyValueStore, key, value_int16));
    // use same key and try to add another element
    EXPECT_FALSE( RamKeyValueStore_add(_ramKeyValueStore, key, value_int16));
}



TEST_F(RamKeyValueStoreTest, AllTypes) {
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
