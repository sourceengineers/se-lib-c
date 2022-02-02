/*!****************************************************************************************************************************************
 * @file         IKeyValueStore.h
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
