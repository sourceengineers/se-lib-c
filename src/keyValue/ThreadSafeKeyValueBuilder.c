/*!****************************************************************************************************************************************
 * @file         ThreadSafeKeyValueBuilder.c
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

#include "se-lib-c/keyValue/ThreadSafeKeyValueBuilder.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "se-lib-c/keyValue/ThreadSafeKeyValueStore.h"
#include "se-lib-c/keyValue/RamKeyValueStore.h"

typedef struct ThreadSafeKeyValueBuilder_PrivateData
{
    IKeyValueStore* iKeyValueStore;
} PrivateData;

Builder_Handle ThreadSafeKeyValueBuilder_create(uint16_t numberOfKeys, const KeyValue_Pair initialKeyValuePairArray[], const IMutex* mutex)
{
    PrivateData* me = malloc(sizeof(PrivateData));
    assert(me != NULL);

    IKeyValueStore* iKeyValueStore = NULL;
    // init RamKeyValueStore
    RamKeyValueStore_Handle ramKeyValueStore = RamKeyValueStore_create(numberOfKeys);
    iKeyValueStore = RamKeyValueStore_getIKeyValueStoreInterface(ramKeyValueStore);

    // add initial values
    for(uint16_t i = 0u; i < numberOfKeys; i++)
    {
        RamKeyValueStore_add(ramKeyValueStore, initialKeyValuePairArray[i].key, initialKeyValuePairArray[i].value);
    }

    // init ThreadSafeKeyValueStore
    ThreadSafeKeyValueStore_Handle threadSafeKeyValueStore = ThreadSafeKeyValueStore_create(iKeyValueStore, mutex);
    iKeyValueStore = ThreadSafeKeyValueStore_getIKeyValueStoreInterface(threadSafeKeyValueStore);

    me->iKeyValueStore = iKeyValueStore;
    assert(me->iKeyValueStore != NULL);
    return me;
}

const IKeyValueStore* ThreadSafeKeyValueBuilder_getIKeyValueStoreInterface(Builder_Handle me)
{
    assert(me != NULL);
    return me->iKeyValueStore;
}

void ThreadSafeKeyValueBuilder_destroy(Builder_Handle me)
{
    free(me);
}
