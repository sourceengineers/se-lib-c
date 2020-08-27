/*!****************************************************************************************************************************************
 * @file         ThreadSafeKeyValueStore.c
 *
 * @copyright    © by Source Engineers GmbH, 2020
 *
 * @authors      Tobias Jäggi <tobias.jaeggi@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#include "ThreadSafeKeyValueStore.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ThreadSafeKeyValueStore_PrivateData
{
	uint16_t privateVariable;
	bool mutex;
} PrivateData;


ThreadSafeKeyValueStore_Handle ThreadSafeKeyValueStore_create(void)
{
    PrivateData* me = malloc(sizeof(PrivateData));
    assert(me != NULL);

    // initialize private variables
    me->privateVariable = 0; 

    return me;
}

void ThreadSafeKeyValueStore_destroy(ThreadSafeKeyValueStore_Handle me)
{
    free(me);
}
