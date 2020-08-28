/*!****************************************************************************************************************************************
 * @file         Builder.h
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
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
