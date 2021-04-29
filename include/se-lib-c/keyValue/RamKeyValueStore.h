/*!****************************************************************************************************************************************
 * @file         RamKeyValueStore.h
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
IKeyValueStore* RamKeyValueStore_getIKeyValueStoreInterface(RamKeyValueStore_Handle me);

/**
 * Destroys a RamKeyValueStore instance.
 */
void RamKeyValueStore_destroy(RamKeyValueStore_Handle me);

#endif // RAMKEYVALUESTORE_H_
