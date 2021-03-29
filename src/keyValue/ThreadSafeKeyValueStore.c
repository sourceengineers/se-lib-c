/*!****************************************************************************************************************************************
 * @file         ThreadSafeKeyValueStore.c
 *
 * @copyright    © by Source Engineers GmbH, 2020
 *
 * @license      This file is part of SE-Lib-C.
 *
 *               SE-Lib-C is free software; you can redistribute it and/or
 *               modify it under the terms of the GNU General Public License as
 *               published by the Free Software Foundation.
 *
 *               SE-Lib-C is distributed in the hope that it will be useful,
 *               but WITHOUT ANY WARRANTY; without even the implied warranty of
 *               MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *               GNU General Public License for more details.
 *
 *               You should have received a copy of the GNU General Public License
 *               along with SE-Lib-C.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @authors      Tobias Jäggi <tobias.jaeggi@sourceengineers.com>
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
