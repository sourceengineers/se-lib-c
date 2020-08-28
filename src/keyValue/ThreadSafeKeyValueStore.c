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

typedef struct ThreadSafeKeyValueStore_PrivateData
{
    IKeyValueStore base;
    IKeyValueStore* composite;
    const IMutex* mutex;
} PrivateData;

static bool set(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value value);
static bool get(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value* value);

ThreadSafeKeyValueStore_Handle ThreadSafeKeyValueStore_create(IKeyValueStore* composite, const IMutex* mutex)
{
    PrivateData* me = malloc(sizeof(PrivateData));
    assert(me != NULL);

    // initialize private variables
    me->base.handle = me;
    me->base.set = &set;
    me->base.get = &get;

    me->composite = composite;
    assert(me->composite != NULL);
    me->mutex = mutex;
    assert(me->mutex != NULL);

    return me;
}

static bool set(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value value)
{
    PrivateData* me = (PrivateData*)handle;
    assert(me != NULL);

    bool success = false;
    if(me->mutex->lock(me->mutex->handle,10))
    {
        success = me->composite->set(me->composite, key, value);
        me->mutex->unlock(me->mutex->handle);
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
        success = me->composite->get(me->composite, key, value);
        me->mutex->unlock(me->mutex->handle);
    }
    return success;
}

IKeyValueStore* ThreadSafeKeyValueStore_getIKeyValueStoreInterface(ThreadSafeKeyValueStore_Handle me)
{
    assert(me != NULL);
    return &me->base;
}

void ThreadSafeKeyValueStore_destroy(ThreadSafeKeyValueStore_Handle me)
{
    free(me);
}
