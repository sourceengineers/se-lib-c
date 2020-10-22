/*!****************************************************************************************************************************************
 * @file         ThreadSafeByteStream.c
 *
 * @copyright    Copyright (c) 2020 by Sourceengineers. All Rights Reserved.
 *
 * @authors      Anselm Fuhrer anselm.fuhrer@sourceengineers.com
 *
 *****************************************************************************************************************************************/

#include <se-lib-c/stream/IByteStream.h>
#include <se-lib-c/stream/ThreadSafeByteStream.h>
#include <se-lib-c/osal/IMutex.h>
#include <se-lib-c/util/composite/IComposite.h>

#include <stdlib.h>
#include <assert.h>

/******************************************************************************
 Define private data
******************************************************************************/

/* Class data */
typedef struct __ThreadSafeByteStreamPrivateData
{
    IByteStream parent;
    IMutexHandle mutex;
    ICompositeHandle composite;
} ThreadSafeByteStreamPrivateData;

/******************************************************************************
 Private functions
******************************************************************************/


/******************************************************************************
 Public functions
******************************************************************************/

void write(ThreadSafeByteStreamHandle me)
{
    //TODO adjust timeout
    if(me->mutex->lock(me->mutex, 0x10))
    {
        me->composite->write(me->composite);
        me->mutex->unlock(me->mutex);
    }
}


void read(ThreadSafeByteStreamHandle me)
{
    if(me->mutex->lock(me->mutex, 0x10))
    {
        me->composite->read(me->composite);
        me->mutex->unlock(me->mutex);
    }
}


ThreadSafeByteStreamHandle ThreadSafeByteStream_create(IMutex mutex, IByteStream streamToProtect)
{
    ThreadSafeByteStreamHandle me = (ThreadSafeByteStreamHandle) malloc(sizeof(ThreadSafeByteStreamPrivateData));
    assert(me);
    //TODO
    return me;
}

void ThreadSafeByteStream_destroy(ThreadSafeByteStreamHandle me)
{
    free(me);
    me = NULL;
}

IByteStreamHandle ThreadSafeByteStream_getIByteStream(ThreadSafeByteStreamHandle me)
{
    return &me->parent;
}
