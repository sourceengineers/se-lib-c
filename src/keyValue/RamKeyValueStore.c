/*!****************************************************************************************************************************************
 * @file         RamKeyValueStore.c
 *
 * @copyright    © by Source Engineers GmbH, 2020
 *
 * @authors      Tobias Jäggi <tobias.jaeggi@sourceengineers.com>
 *
 *****************************************************************************************************************************************/

#include "RamKeyValueStore.h"
#include <assert.h>
#include <stdlib.h>

typedef struct RamKeyValueStore_PrivateData
{
    IKeyValueStore base;
    KeyValuePair* keyValueArray;
    uint16_t arraySize;
} PrivateData;

/**
 * The implementation of the Parent methods.
 * @{
 */
static bool set(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value value);
static bool get(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value* value);
/** @} */

RamKeyValueStore_Handle RamKeyValueStore_create(uint16_t numberOfKeys)
{
    PrivateData* me = malloc(sizeof(PrivateData));
    assert(me != NULL);

    // initialize interface
    me->base.handle = me;
    me->base.set = &set;
    me->base.get = &get;

    // initialize private variables
    me->arraySize = numberOfKeys;
    me->keyValueArray = (KeyValuePair *) malloc(sizeof(KeyValuePair)*(numberOfKeys));
    assert(me->keyValueArray != NULL);
    return me;
}

// private
// determine index of key in keyValueArray
bool RamKeyValueStore_getIndexOfKey(RamKeyValueStore_Handle me, uint16_t key, uint16_t* index)
{
    bool success = false;
    for(uint16_t i = 0; i < (me->arraySize); i++)
    {
        if(me->keyValueArray[i].key == key)
        {
            success = true;
            *index = i;
            break;
        }
    }
    return success;
}

// private
// determine index of first unused slot in keyValueArray
uint16_t RamKeyValueStore_getIndexOfFistUnusedSlot(RamKeyValueStore_Handle me, uint16_t* index) {
    bool success = false;
    if (RamKeyValueStore_getIndexOfKey(me, 0, index))
    {
        success = true;
    }
    return success;
}

// set function
bool set(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value value) //TODO: rename KeyValue_Value value to something more suiting
{
    bool success = false;
    PrivateData* me = (PrivateData*)handle;
    assert(me != NULL);
    uint16_t index;
    if(RamKeyValueStore_getIndexOfKey(me, key, &index))
    {
        me->keyValueArray[index].value = value;
        success = true;
    }
    return success;
}

// get function
bool get(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value* value)
{
    bool success = false;
    PrivateData* me = (PrivateData*)handle;
    assert(me != NULL);
    uint16_t index;
    if(RamKeyValueStore_getIndexOfKey(me, key, &index))
    {
        *value = me->keyValueArray[index].value;
        success = true;
    }
    return success;
}

// add function
bool RamKeyValueStore_add(RamKeyValueStore_Handle me, uint16_t key, KeyValue_Value initialValue)
{
    bool success = false;
    uint16_t index;
    if(RamKeyValueStore_getIndexOfFistUnusedSlot(me,&index) && key > 0)
    {
        me->keyValueArray[index].key = key;
        me->keyValueArray[index].value = initialValue;
        success = true;
    }
    return success;
}

IKeyValueStore* Runnable_getIKeyValueStoreInterface(RamKeyValueStore_Handle me)
{
    assert(me != NULL);
    return &me->base;
}


void RamKeyValueStore_destroy(RamKeyValueStore_Handle me)
{
    free(me);
}
