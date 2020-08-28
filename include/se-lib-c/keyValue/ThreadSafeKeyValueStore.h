/*!****************************************************************************************************************************************
 * @file         ThreadSafeKeyValueStore.h
 *
 * @copyright    © by Source Engineers GmbH, 2020
 *
 * @authors      Tobias Jäggi <tobias.jaeggi@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#ifndef THREADSAFEKEYVALUESTORE_H_
#define THREADSAFEKEYVALUESTORE_H_

#include "se-lib-c/keyValue/IKeyValueStore.h"
#include "se-lib-c/osal/IMutex.h"


/**
 * Declaration of the ThreadSafeKeyValueStore handle.
 */
typedef struct ThreadSafeKeyValueStore_PrivateData* ThreadSafeKeyValueStore_Handle;

/**
 * Creates a ThreadSafeKeyValueStore instance.
 */

ThreadSafeKeyValueStore_Handle ThreadSafeKeyValueStore_create(IKeyValueStore* composite, IMutex* mutex);

/**
 * Returns a pointer to the IKeyValueStore.
 */
IKeyValueStore* ThreadSafeKeyValueStore_getIKeyValueStoreInterface(ThreadSafeKeyValueStore_Handle me);

/**
 * Destroys a ThreadSafeKeyValueStore instance.
 */
void ThreadSafeKeyValueStore_destroy(ThreadSafeKeyValueStore_Handle me);

#endif // THREADSAFEKEYVALUESTORE_H_
