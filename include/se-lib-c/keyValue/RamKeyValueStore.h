/*!****************************************************************************************************************************************
 * @file         RamKeyValueStore.h
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
