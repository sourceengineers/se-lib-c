/*!****************************************************************************************************************************************
 * @file         MaxCheck.c
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/
#include <se-lib-c/monitoring/MaxCheck.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct MaxCheck_PrivateData
{
	ICheckable checkable;
	IRunnable runnable;
    float * valueToCheck;
    float tripLimit;
    uint16_t tripTimeMs;
    uint16_t callIntvervallMs;
    uint16_t timeAboveLimitMs;
	bool isActive;
	bool isCheckOk;
} PrivateData;


/**
 * The implementation of the ICheckable methods.
 * @{
 */
static void setActive(ICheckable_Handle handle, bool isActive);
static bool isCheckOk(ICheckable_Handle handle);
/** @} */

/**
 * The implementation of the IRunnable methods.
 * @{
 */
static void run(IRunnable_Handle handle);
/** @} */


MaxCheck_Handle MaxCheck_create(float* valueToCheck, float tripLimit, uint16_t tripTimeMs, uint16_t callIntvervallMs)
{
    PrivateData* me = malloc(sizeof(PrivateData));
    assert(me != NULL);

    // initialize activable interface
    me->checkable.handle = me;
    me->checkable.setActive = &setActive;
    me->checkable.isCheckOk = &isCheckOk;

    // initialize runnable interface
    me->runnable.handle = me;
    me->runnable.run = &run;

    // initialize private variables
    me->isActive = false;
    me->isCheckOk = true;
    me->tripLimit = tripLimit;
    me->tripTimeMs = tripTimeMs;
    me->callIntvervallMs = callIntvervallMs;
    me->valueToCheck = valueToCheck;
    me->timeAboveLimitMs = 0;

    return me;
}

void MaxCheck_destroy(MaxCheck_Handle me)
{
    free(me);
}


ICheckable* MaxCheck_getICheckableInterface(MaxCheck_Handle me)
{
    assert(me != NULL);
    return &me->checkable;
}

IRunnable* MaxCheck_getIRunnableInterface(MaxCheck_Handle me)
{
    assert(me != NULL);
    return &me->runnable;
}

static void setActive(ICheckable_Handle handle, bool isActive)
{
    PrivateData* me = (PrivateData*)handle;
    assert(me != NULL);
    me->isActive = isActive;
}

static bool isCheckOk(ICheckable_Handle handle)
{
    PrivateData* me = (PrivateData*)handle;
    assert(me != NULL);
    return me->isCheckOk;
}

static void run(IRunnable_Handle handle)
{
    PrivateData* me = (PrivateData*)handle;
    assert(me != NULL);

    if(me->isActive)
    {
        float value = *me->valueToCheck;
        if(value > me->tripLimit)
        {
            me->timeAboveLimitMs += me->callIntvervallMs;
        }
        else
        {
            // check is ok again
            me->timeAboveLimitMs = 0;
            me->isCheckOk = true;
        }

        if(me->timeAboveLimitMs >= me->tripTimeMs)
        {
            me->isCheckOk = false;
        }
    }
    else
    {
        me->isCheckOk = true;
        me->timeAboveLimitMs = 0;
    }
}