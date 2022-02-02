/*!****************************************************************************************************************************************
 * @file         ThreadSafeKeyValueBuilder.h
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
