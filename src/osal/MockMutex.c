/*!****************************************************************************************************************************************
 * @file         MockMutex.c
 *
 * @copyright    © by Source Engineers GmbH, 2020
 *
 * @authors      Tobias Jäggi <tobias.jaeggi@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/
#include "se-lib-c/osal/MockMutex.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>


/**
 * The implementation of the Parent methods.
 * @{
 */
static bool lock(IMutexHandle self, uint32_t timeout);
static void unlock(IMutexHandle self);

/** @} */

void MockAdcMutex_init(MockMutexPrivateData* me)
{
    // initialize interface
    me->parent.handle = me;
    me->parent.lock = &lock;
    me->parent.unlock = &unlock;
    me->isMutexLocked = false;
    me->isMutexAvailable = false;
}

IMutex* MockMutex_getIMutexInterface(MockMutexPrivateData* me)
{
    assert(me != NULL);
    return &me->parent;
}

bool lock(IMutexHandle self, uint32_t timeout)
{
    MockMutexPrivateData * me = (MockMutexPrivateData *)self;
    assert(me != NULL);
    // TODO: timeout
    bool success = false;
    if(me->isMutexAvailable)
    {
        me->isMutexLocked = true;
        success = true;
    }
    me->numCallsLock++;
    return success; // if false, mutex is already locked
}

void unlock(IMutexHandle self)
{
    MockMutexPrivateData * me = (MockMutexPrivateData *)self;
    assert(me != NULL);

    if(me->isMutexAvailable)
    {
        me->isMutexLocked = false;
    }
    me->numCallsUnlock++;
}

