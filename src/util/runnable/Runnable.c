/*!****************************************************************************************************************************************
 * @file         Runnable.c
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/
#include "Runnable.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct Runnable_PrivateData
{
	IRunnable parent;
	uint16_t callCountOfRun;
} PrivateData;


/**
 * The implementation of the Parent methods.
 * @{
 */ 
static void run(IRunnable_Handle handle);
/** @} */


Runnable_Handle Runnable_create(void)
{
    PrivateData* me = malloc(sizeof(PrivateData));
    assert(me != NULL);

    // initialize interface
    me->parent.handle = me;
    me->parent.run = &run;

    // initialize private variables
    me->callCountOfRun = 0;

    return me;
}

void Runnable_destroy(Runnable_Handle me)
{
    free(me);
}

uint16_t Runnable_getCallCountOfRun(Runnable_Handle me)
{
    return me->callCountOfRun;
}

IRunnable* Runnable_getIRunnableInterface(Runnable_Handle me)
{
    assert(me != NULL);
    return &me->parent;
}


static void run(IRunnable_Handle handle)
{
    PrivateData* me = (PrivateData*)handle;
    assert(me != NULL);
    me->callCountOfRun++;
}
