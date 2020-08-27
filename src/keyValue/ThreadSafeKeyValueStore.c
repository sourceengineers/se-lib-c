/*!****************************************************************************************************************************************
 * @file         ThreadSafeKeyValueStore.c
 *
 * @copyright    © by Source Engineers GmbH, 2020
 *
 * @authors      Tobias Jäggi <tobias.jaeggi@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "se-lib-c/keyValue/ThreadSafeKeyValueStore.h"
#include "se-lib-c/keyValue/KeyValueTypes.h"

typedef struct ThreadSafeKeyValueStore_PrivateData
{
    IKeyValueStore base;
    IKeyValueStore* composite;
    IMutex* mutex;
} PrivateData;

static bool set(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value value);
static bool get(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value* value);

ThreadSafeKeyValueStore_Handle ThreadSafeKeyValueStore_create(IKeyValueStore* composite, IMutex* mutex)
{
    PrivateData* me = malloc(sizeof(PrivateData));
    assert(me != NULL);

    // initialize private variables
    me->base.handle = me;
    me->base.set = &set;
    me->base.get = &get;

    me->composite = composite;
    //TODO assert
    me->mutex = mutex;
    //TODO assert

    return me;
}

static bool set(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value value)
{
    PrivateData* me = (PrivateData*)handle;
    assert(me != NULL);

    bool success = false;
    if(me->mutex->lock(me->mutex->handle,10))
    {
        me->composite->set(me->composite, key, value);
        me->mutex->unlock(me->mutex->handle);
        success = true;
    }
    return success;
}

static bool get(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value* value)
{
    PrivateData* me = (PrivateData*)handle;
    assert(me != NULL);

    bool success = false;
    if(me->mutex->lock(me->mutex->handle,10))
    {
        me->composite->get(me->composite, key, value);
        me->mutex->unlock(me->mutex->handle);
        success = true;
    }
    return success;
}

IKeyValueStore* Runnable_getIThreadSafeKeyValueStoreInterface(ThreadSafeKeyValueStore_Handle me)
{
    assert(me != NULL);
    return &me->base;
}

void ThreadSafeKeyValueStore_destroy(ThreadSafeKeyValueStore_Handle me)
{
    free(me);
}
