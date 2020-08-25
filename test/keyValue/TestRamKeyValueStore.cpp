#include <gtest/gtest.h>

extern "C" {
    #include "../../src/keyValue/RamKeyValueStore.h"
    #include "../../src/keyValue/KeyValueTypes.h"
}

class RamKeyValueStoreTest : public ::testing::Test
{
protected:
    RamKeyValueStoreTest()
        : Test()
    {
    }

    void SetUp() override
    {
        _ramKeyValueStore = RamKeyValueStore_create(5u); //5 corresponds to the number of types defined for KeyValue_Data
        iKeyValueStore = Runnable_getIKeyValueStoreInterface(_ramKeyValueStore);

    }

    void TearDown() override
    {
    	RamKeyValueStore_destroy(_ramKeyValueStore);
    }

    virtual ~RamKeyValueStoreTest()
    {
    }

    RamKeyValueStore_Handle _ramKeyValueStore;
    IKeyValueStore* iKeyValueStore;
};
TEST_F(RamKeyValueStoreTest, RamKeyValueStoreCreated)
{
    // test that the template was created
    EXPECT_NE(nullptr, _ramKeyValueStore);
    EXPECT_NE(nullptr, iKeyValueStore);


}
TEST_F(RamKeyValueStoreTest, AddGetSet)
{

    // TEST ADD AND GET
    //init
    KeyValue_Data kv_data = {.i32 = 0};
    KeyValue_Value kv_value = {KEY_TYPE_NONE, kv_data};

    //int 16
    kv_data = {.i16 = -16};
    KeyValue_Value value_int16 = {KEY_TYPE_INT16, kv_data}; // create KeyValue_Value
    // add a int16 value with key 1
    EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, 1u, value_int16));
    // get value for key 1
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 1u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_int16.type, kv_value.type);
    EXPECT_EQ(value_int16.data.i16, kv_value.data.i16); //TODO: remove hardcoded type when reading kv_value.data, should be based on kv_value.type

    //int 32
    kv_data.i32 = -32;
    //KeyValue_Value value_int32 = {KEY_TYPE_INT32, kv_data.data.i32};
    KeyValue_Value value_int32 = {KEY_TYPE_INT32, kv_data};
    // add a int32 value with key 2
    EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, 2u, value_int32));
    // get value for key 2
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 2u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_int32.type, kv_value.type);
    EXPECT_EQ(value_int32.data.i32, kv_value.data.i32); //TODO: remove hardcoded type when reading kv_value.data, should be based on kv_value.type

    //uint 16
    kv_data.ui16 = 16u;
    KeyValue_Value value_uint16 = {KEY_TYPE_UINT16, kv_data};
    // add a uint16 value with key 3
    EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, 3u, value_uint16));
    // get value for key 3
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 3u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_uint16.type, kv_value.type);
    EXPECT_EQ(value_uint16.data.ui16, kv_value.data.ui16); //TODO: remove hardcoded type when reading kv_value.data, should be based on kv_value.type

    //uint 32
    kv_data.ui32 = 32u;
    KeyValue_Value value_uint32 = {KEY_TYPE_UINT32, kv_data};
    // add a uint32 value with key 4
    EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, 4u, value_uint32));
    // get value for key 4
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 4u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_uint32.type, kv_value.type);
    EXPECT_EQ(value_uint32.data.ui32, kv_value.data.ui32); //TODO: remove hardcoded type when reading kv_value.data, should be based on kv_value.type

    /*
    //float
    kv_data.f = 0.0f;
    KeyValue_Value value_float = {KEY_TYPE_FLOAT, kv_data};
    // add a float value with key 5
    EXPECT_EQ(true, RamKeyValueStore_add(_ramKeyValueStore, 5u, value_float));
    // get value for key 5
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 5u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_float.type, kv_value.type);
    EXPECT_EQ(value_float.data.f, kv_value.data.f); //TODO: remove hardcoded type when reading kv_value.data, should be based on kv_value.type
*/
    // test add with invalid keys
    EXPECT_EQ(false, RamKeyValueStore_add(_ramKeyValueStore, 6u, value_int16));
    EXPECT_EQ(false, RamKeyValueStore_add(_ramKeyValueStore, 0u, value_int16));

    // test get with invalid keys
    EXPECT_EQ(false, iKeyValueStore->get(iKeyValueStore->handle, 6u, &kv_value));
    EXPECT_EQ(false, iKeyValueStore->get(iKeyValueStore->handle, 0u, &kv_value));

    // TEST SET

    // set key 1 to value_int32
    EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, 1u, value_int32));
    // get key 1, should be value_int32
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 1u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_int32.type, kv_value.type);
    EXPECT_EQ(value_int32.data.i32, kv_value.data.i32); //TODO: remove hardcoded type when reading kv_value.data, should be based on kv_value.type

    // set key 2 to value_uint16
    EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, 2u, value_uint16));
    // get key 2, should be value_uint16
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 2u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_uint16.type, kv_value.type);
    EXPECT_EQ(value_uint16.data.ui16, kv_value.data.ui16); //TODO: remove hardcoded type when reading kv_value.data, should be based on kv_value.type

    // set key 3 to value_uint32
    EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, 3u, value_uint32));
    // get key 3, should be value_uint32
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 3u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_uint32.type, kv_value.type);
    EXPECT_EQ(value_uint32.data.ui32, kv_value.data.ui32); //TODO: remove hardcoded type when reading kv_value.data, should be based on kv_value.type
/*
    // set key 4 to value_float
    EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, 4u, value_float));
    // get key 4 should be value_float
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 4u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_float.type, kv_value.type);
    EXPECT_EQ(value_float.data.f, kv_value.data.f); //TODO: remove hardcoded type when reading kv_value.data, should be based on kv_value.type
*/
    // set key 5 to value_int16
    EXPECT_EQ(true, iKeyValueStore->set(iKeyValueStore->handle, 5u, value_int16));
    // get key 5 should be value_int16
    EXPECT_EQ(true, iKeyValueStore->get(iKeyValueStore->handle, 5u, &kv_value));
    // compare received with expected
    EXPECT_EQ(value_int16.type, kv_value.type);
    EXPECT_EQ(value_int16.data.i16, kv_value.data.i16); //TODO: remove hardcoded type when reading kv_value.data, should be based on kv_value.type

    // test set with invalid keys
    EXPECT_EQ(false, iKeyValueStore->set(iKeyValueStore->handle, 6u, value_int16));
    EXPECT_EQ(false, iKeyValueStore->set(iKeyValueStore->handle, 0u, value_int16));

/*
    // messing around
    KeyValue_Data *kv_data_pointer;
    kv_data_pointer = &(kv_value.data);
    //int16_t val = kv_data_pointer[0];
    EXPECT_EQ(value_int16.data.i16, kv_data_pointer[0]);
    KeyValue_KeyType kv_key_type = kv_value.type;

*/
 }
