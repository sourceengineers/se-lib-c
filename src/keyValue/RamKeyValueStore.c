/*!****************************************************************************************************************************************
 * @file         RamKeyValueStore.c
 *
 * @copyright    Copyright (c) 2021 by Source Engineers GmbH. All Rights Reserved.
 *
 * @license {    This file is part of se-lib-c.
 *
 *               se-lib-c is free software; you can redistribute it and/or
 *               modify it under the terms of the GPLv3 General Public License Version 3
 *               as published by the Free Software Foundation.
 *
 *               se-lib-c is distributed in the hope that it will be useful,
 *               but WITHOUT ANY WARRANTY; without even the implied warranty of
 *               MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *               GNU General Public License for more details.
 *
 *               You should have received a copy of the GPLv3 General Public License Version 3
 *               along with se-lib-c.  If not, see <http://www.gnu.org/licenses/>.
 *
 *               In closed source or commercial projects, GPLv3 General Public License Version 3
 *               is not valid. In these cases the purchased commercial license is applied.
 *               Please contact us at scope@sourceengineers.com for a commercial license.
 * }
 *
 * @authors      Tobias Jäggi <tobias.jaeggi@sourceengineers.com>
 *
 *****************************************************************************************************************************************/

#include "se-lib-c/keyValue/RamKeyValueStore.h"
#include <assert.h>
#include <stdlib.h>

typedef struct RamKeyValueStore_PrivateData
{
    IKeyValueStore base;
    KeyValue_Pair* keyValueArray;
    uint16_t numberOfPairs;
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
    me->numberOfPairs = numberOfKeys;
    me->keyValueArray = calloc(numberOfKeys, sizeof(KeyValue_Pair));
    assert(me->keyValueArray != NULL);
    return me;
}

// determine index of key in keyValueArray
static bool getIndexOfKey(RamKeyValueStore_Handle me, uint16_t key, uint16_t* index)
{
    bool success = false;
    for(uint16_t i = 0; i < (me->numberOfPairs); i++)
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

// set function
static bool set(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value value)
{
    bool success = false;
    if(key <= 0) //invalid key
    {
        return success;
    }
    PrivateData* me = (PrivateData*)handle;
    assert(me != NULL);
    uint16_t index;
    if(getIndexOfKey(me, key, &index))
    {
        me->keyValueArray[index].value = value;
        success = true;
    }
    return success;
}

// get function
static bool get(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value* value)
{
    bool success = false;
    if(key <= 0) //invalid key
    {
        return success;
    }
    PrivateData* me = (PrivateData*)handle;
    assert(me != NULL);
    uint16_t index;
    if(getIndexOfKey(me, key, &index))
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
    if(key <= 0) //invalid key
    {
        return success;
    }
    uint16_t index;
    // check if key already is used
    if(getIndexOfKey(me, key, &index))
    {
        return success;
    }
    // search empty entry
        if(getIndexOfKey(me, 0, &index)) // key = 0 => field empty
    {
        me->keyValueArray[index].key = key;
        me->keyValueArray[index].value = initialValue;
        success = true;
    }
    return success;
}

IKeyValueStore* RamKeyValueStore_getIKeyValueStoreInterface(RamKeyValueStore_Handle me)
{
    assert(me != NULL);
    return &me->base;
}


void RamKeyValueStore_destroy(RamKeyValueStore_Handle me)
{
    free(me);
}
