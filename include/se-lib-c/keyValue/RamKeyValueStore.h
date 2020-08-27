/*!****************************************************************************************************************************************
 * @file         RamKeyValueStore.h
 *
 * @copyright    © by Source Engineers GmbH, 2020
 *
 * @authors      Tobias Jäggi <tobias.jaeggi@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#ifndef RAMKEYVALUESTORE_H_
#define RAMKEYVALUESTORE_H_

#include "se-lib-c/keyValue/IKeyValueStore.h"
#include "KeyValueTypes.h"
#include <stdint.h>
#include <stdbool.h>


/**
 * Declaration of the RamKeyValueStore handle.
 */
typedef struct RamKeyValueStore_PrivateData* RamKeyValueStore_Handle;

/**
 * Creates a RamKeyValueStore instance.
 */
RamKeyValueStore_Handle RamKeyValueStore_create(uint16_t numberOfKeys);

/**
 * Adds key value pair.
 * @param key, key of the key-value pair, @warning: key must be > 0
 */
bool RamKeyValueStore_add(RamKeyValueStore_Handle me, uint16_t key, KeyValue_Value initialValue);

/**
 * Returns a pointer to the IKeyValueStore.
 */
IKeyValueStore* Runnable_getIKeyValueStoreInterface(RamKeyValueStore_Handle me);

/**
 * Destroys a RamKeyValueStore instance.
 */
void RamKeyValueStore_destroy(RamKeyValueStore_Handle me);

#endif // RAMKEYVALUESTORE_H_
