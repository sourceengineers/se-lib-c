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
//    ICompositeHandle composite;
} ThreadSafeByteStreamPrivateData;

/******************************************************************************
 Private functions
******************************************************************************/


/******************************************************************************
 Public functions
******************************************************************************/

// TODO with composite composite
void write(ThreadSafeByteStreamHandle me, const uint8_t* data, const size_t length)
{
    if(me->mutex->lock(me->mutex, 0xFF))
    {
//    	me->composite->write(me->composite)
        me->parent.write(me->parent.handle, data, length);
        me->mutex->unlock(me->mutex);
    }
}


void read(ThreadSafeByteStreamHandle me, uint8_t* data, const size_t length)
{
    if(me->mutex->lock(me->mutex, 0xFF))
    {
//        me->composite->read(me->composite);
        me->parent.read(me->parent.handle, data, length);
        me->mutex->unlock(me->mutex);
    }
}


ThreadSafeByteStreamHandle ThreadSafeByteStream_create(IMutexHandle mutex, IByteStreamHandle streamToProtect)
{
    ThreadSafeByteStreamHandle me = (ThreadSafeByteStreamHandle) malloc(sizeof(ThreadSafeByteStreamPrivateData));
    assert(me);

    me->mutex = mutex;

    me->parent.handle = streamToProtect;
    me->parent.write = &write;
    me->parent.read = &read;
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
