/*!****************************************************************************************************************************************
 * @file         IKeyValueStore.h
 *
 * @copyright    © by Source Engineers GmbH, 2020
 *
 * @authors      Tobias Jäggi <tobias.jaeggi@sourceengineers.com>
 *
 * @brief        TODO
 * 
 *****************************************************************************************************************************************/

#ifndef IKEYVALUESTORE_H_
#define IKEYVALUESTORE_H_

#include <stdint.h>
#include <stdbool.h>
#include "KeyValueTypes.h"


// Declare the handle to the interface
typedef void* IKeyValueStore_Handle;

// Declares the methods of the interface
typedef bool (*IKeyValueStore_set)(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value value);
/**
 *
 * @param key, key of the key-value pair, @warning: key must be > 0
 */
typedef bool (*IKeyValueStore_get)(IKeyValueStore_Handle handle, uint16_t key, KeyValue_Value* value);

// Declare the interface
typedef struct __IKeyValueStore
{
    IKeyValueStore_Handle handle;       // the explicit 'this' pointer
    IKeyValueStore_set set;             // pointer to function implementation
    IKeyValueStore_get get;             // pointer to function implementation
} IKeyValueStore;

#endif //IKEYVALUESTORE_H_
