/*!****************************************************************************************************************************************
 * @file         MaxCheck.c
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
 *               is not valid. In this case the commercial license received with the purchase
 *               is applied (See SeScopeLicense.pdf).
 *               Please contact us at scope@sourceengineers.com for a commercial license.
 * }
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
static void setActive(ICheckableHandle handle, bool isActive);
static bool isCheckOk(ICheckableHandle handle);
/** @} */

/**
 * The implementation of the IRunnable methods.
 * @{
 */
static bool run(IRunnableHandle handle);
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

static void setActive(ICheckableHandle handle, bool isActive)
{
    PrivateData* me = (PrivateData*)handle->handle;
    assert(me != NULL);
    me->isActive = isActive;
}

static bool isCheckOk(ICheckableHandle handle)
{
    PrivateData* me = (PrivateData*)handle->handle;
    assert(me != NULL);
    return me->isCheckOk;
}

static bool run(IRunnableHandle handle)
{
    PrivateData* me = (PrivateData*)handle->handle;
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

    return true;
}