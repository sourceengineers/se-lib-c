/*!****************************************************************************************************************************************
 * @file         RunnableList.c
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
 *               is not valid. In these cases the purchased commercial license is applied.
 *               Please contact us at scope@sourceengineers.com for a commercial license.
 * }
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/
#include <se-lib-c/util/runnable/RunnableList.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct RunnableListElement* RunnableListElement_Handle;

typedef struct RunnableListElement
{
    IRunnable* runnable;
    RunnableListElement_Handle next;
}ListElement;

typedef struct RunnableList_PrivateData
{
	IRunnable parent;
    RunnableListElement_Handle first;
	uint16_t numberOfListElements;
} PrivateData;


/**
 * The implementation of the Parent methods.
 * @{
 */ 
static bool run(IRunnableHandle handle);
/** @} */


RunnableList_Handle RunnableList_create(void)
{
    PrivateData* me = malloc(sizeof(PrivateData));
    assert(me != NULL);

    // initialize interface
    me->parent.handle = me;
    me->parent.run = &run;

    // initialize private variables
    me->first = NULL;

    return me;
}

void RunnableList_destroy(RunnableList_Handle me)
{
    if(me->first != NULL)
    {
        RunnableListElement_Handle element = (RunnableListElement_Handle)me->first;
        while(element->next != NULL)
        {
            RunnableListElement_Handle elementToFree = element;
            element = element->next;
            free(elementToFree);
        }
    }

    free(me);
}


IRunnable* RunnableList_getIRunnableInterface(RunnableList_Handle me)
{
    assert(me != NULL);
    return &me->parent;
}

void RunnableList_add(RunnableList_Handle me, IRunnable* runnable)
{
    assert(runnable);
    assert(me);

    if(me->first == NULL)
    {
        me->first = (RunnableListElement_Handle)malloc(sizeof(ListElement));
        assert(me->first);
        me->first->runnable = runnable;
        me->first->next = NULL;
    }
    else
    {
        RunnableListElement_Handle element = me->first;
        while(element->next != NULL)
        {
            element = element->next;
        }
        element->next =  (RunnableListElement_Handle)malloc(sizeof(ListElement));
        assert(element->next);
        element = element->next;
        element->runnable = runnable;
        element->next = NULL;
    }
}

static bool run(IRunnableHandle handle)
{
    PrivateData* me = (PrivateData*)handle->handle;
    assert(me != NULL);
    bool success = true;

    RunnableListElement_Handle element = me->first;
    while(element->next != NULL)
    {
        assert(element->runnable);
        success &= element->runnable->run(element->runnable->handle);
        element = element->next;
    }
    // run last element
    assert(element->runnable);
    success &= element->runnable->run(element->runnable->handle);
    return success;
}
