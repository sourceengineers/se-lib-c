/*!****************************************************************************************************************************************
 * @file         ThreadSafeKeyValueStore.c
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
 *               is not valid. In this case the commercial license received with the purchase
 *               is applied (See SeScopeLicense.pdf).
 *               Please contact us at scope@sourceengineers.com for a commercial license.
 * }
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
