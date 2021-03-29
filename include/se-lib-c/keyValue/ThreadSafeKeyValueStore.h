/*!****************************************************************************************************************************************
 * @file         ThreadSafeKeyValueStore.h
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

ThreadSafeKeyValueStore_Handle ThreadSafeKeyValueStore_create(IKeyValueStore* composite, const IMutex* mutex);

/**
 * Returns a pointer to the IKeyValueStore.
 */
IKeyValueStore* ThreadSafeKeyValueStore_getIKeyValueStoreInterface(ThreadSafeKeyValueStore_Handle me);

/**
 * Destroys a ThreadSafeKeyValueStore instance.
 */
void ThreadSafeKeyValueStore_destroy(ThreadSafeKeyValueStore_Handle me);

#endif // THREADSAFEKEYVALUESTORE_H_
