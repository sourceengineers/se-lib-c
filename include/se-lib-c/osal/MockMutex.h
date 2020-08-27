/*!****************************************************************************************************************************************
 * @file         MockMutex.h
 *
 * @copyright    © by Source Engineers GmbH, 2020
 *
 * @authors      Tobias Jäggi <tobias.jaeggi@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#ifndef MOCKMUTEX_H_
#define MOCKMUTEX_H_

#include <stdint.h>
#include <stdbool.h>
#include <se-lib-c/osal/IMutex.h>

/**
 * Declaration of the mock object.
 */
typedef struct __MockMutexPrivateData
{
    IMutex parent;
    bool isMutexLocked;
    bool isMutexAvailable;
    uint16_t  numCallsLock;
    uint16_t  numCallsUnlock;
} MockMutexPrivateData;


/**
 * initialize a MockMutex instance.
 */
void MockMutex_init(MockMutexPrivateData* me);

/**
 * Returns a pointer to the IMutex.
 */
IMutex* MockMutex_getIMutexInterface(MockMutexPrivateData* me);


#endif // MOCKMUTEX_H_
