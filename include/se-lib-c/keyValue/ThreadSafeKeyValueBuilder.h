/*!****************************************************************************************************************************************
 * @file         ThreadSafeKeyValueBuilder.h
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

#ifndef BUILDER_H_
#define BUILDER_H_
#include <stdint.h>
#include "se-lib-c/keyValue/IKeyValueStore.h"
#include "se-lib-c/keyValue/KeyValueTypes.h"
#include "se-lib-c/osal/IMutex.h"
/**
 * Declaration of the Builder handle.
 */
typedef struct ThreadSafeKeyValueBuilder_PrivateData* Builder_Handle;

/**
 * Creates a Builder instance.
 */
Builder_Handle ThreadSafeKeyValueBuilder_create(uint16_t numberOfKeys, const KeyValue_Pair initialKeyValuePairArray[], const IMutex* mutex);
/**
 * Returns a pointer to the IKeyValueStore.
 */
const IKeyValueStore* ThreadSafeKeyValueBuilder_getIKeyValueStoreInterface(Builder_Handle me);

/**
 * Destroys a Builder instance.
 */
void ThreadSafeKeyValueBuilder_destroy(Builder_Handle me);

#endif // BUILDER_H_
