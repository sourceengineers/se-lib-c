/*!****************************************************************************************************************************************
 * @file         ThreadSafeKeyValueBuilder.c
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
