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
static void run(IRunnable_Handle handle);
/** @} */


void MockRunnable_init(MockRunnablePrivateData* me)
{
    // initialize interface
    me->parent.handle = me;
    me->parent.run = &run;

    // initialize private variables
    me->callCountOfRun = 0;
}

IRunnable* MockRunnable_getIRunnableInterface(MockRunnablePrivateData* me)
{
    assert(me != NULL);
    return &me->parent;
}


static void run(IRunnable_Handle handle)
{
    MockRunnablePrivateData* me = (MockRunnablePrivateData*)handle;
    assert(me != NULL);
    me->callCountOfRun++;
}
