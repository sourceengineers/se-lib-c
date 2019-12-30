/*!****************************************************************************************************************************************
 * @file         MockRunnable.c
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/
#include "MockRunnable.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>


/**
 * The implementation of the Parent methods.
 * @{
 */ 
static bool run(IRunnableHandle handle);
/** @} */


void MockRunnable_init(MockRunnable* me)
{
    // initialize interface
    me->parent.handle = me;
    me->parent.run = &run;

    // initialize private variables
    me->callCountOfRun = 0;
    me->isRunSuccess = true;
}

IRunnable* MockRunnable_getIRunnableInterface(MockRunnable* me)
{
    assert(me != NULL);
    return &me->parent;
}


static bool run(IRunnableHandle handle)
{
    MockRunnable* me = (MockRunnable*)handle->handle;
    assert(me != NULL);
    me->callCountOfRun++;
    return me->isRunSuccess;
}
