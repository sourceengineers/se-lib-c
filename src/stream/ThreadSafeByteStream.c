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
    IByteStream* composite;
} ThreadSafeByteStreamPrivateData;

/******************************************************************************
 Private functions
******************************************************************************/


static bool byteIsReady(IByteStreamHandle self)
{
	bool success = false;
	ThreadSafeByteStreamPrivateData* me = (ThreadSafeByteStreamPrivateData*)self->handle;
	if(me->mutex->lock(me->mutex, 0xFFF))
	{
		success = me->composite->byteIsReady(me->composite);
		me->mutex->unlock(me->mutex);
	}

	return success;
}

static uint8_t readByte(IByteStreamHandle self)
{
	ThreadSafeByteStreamPrivateData* me = (ThreadSafeByteStreamPrivateData*)self->handle;
	uint8_t readValue;
	if(me->mutex->lock(me->mutex, 0xFFF))
	{
		readValue = me->composite->readByte(me->composite);
		me->mutex->unlock(me->mutex);
	}
	return readValue;
}

static size_t length(IByteStreamHandle self)
{
	ThreadSafeByteStreamPrivateData* me = (ThreadSafeByteStreamPrivateData*)self->handle;
	size_t length = 0;
	if(me->mutex->lock(me->mutex, 0xFFF))
	{
		length = me->composite->length(me->composite);
		me->mutex->unlock(me->mutex);
	}
	return length;
}

static bool writeByte(IByteStreamHandle self, const uint8_t data)
{
	ThreadSafeByteStreamPrivateData* me = (ThreadSafeByteStreamPrivateData*)self->handle;
	bool success = false;
	if(me->mutex->lock(me->mutex, 0xFFF))
	{
		success = me->composite->writeByte(me->composite, data);
		me->mutex->unlock(me->mutex);
	}
	return success;
}

static void flush(IByteStreamHandle self)
{
	ThreadSafeByteStreamPrivateData* me = (ThreadSafeByteStreamPrivateData*)self->handle;
	if(me->mutex->lock(me->mutex, 0xFFF))
	{
		me->composite->flush(me->composite);
		me->mutex->unlock(me->mutex);
	}
}

static size_t capacity (IByteStreamHandle self)
{
	ThreadSafeByteStreamPrivateData* me = (ThreadSafeByteStreamPrivateData*)self->handle;
	size_t capacity;
	if(me->mutex->lock(me->mutex, 0xFFF))
	{
		capacity = me->composite->capacity(me->composite);
		me->mutex->unlock(me->mutex);
	}
	return capacity;
}

static bool write(IByteStreamHandle self, const uint8_t* data, const size_t length)
{
	ThreadSafeByteStreamPrivateData* me = (ThreadSafeByteStreamPrivateData*)self->handle;
	bool success = false;
    if(me->mutex->lock(me->mutex, 0xFFF))
    {
    	success = me->composite->write(me->composite, data, length);
        me->mutex->unlock(me->mutex);
    }
    return success;
}

static void read(IByteStreamHandle self, uint8_t* data, const size_t length)
{
	ThreadSafeByteStreamPrivateData* me = (ThreadSafeByteStreamPrivateData*)self->handle;
    if(me->mutex->lock(me->mutex, 0xFFF))
    {
		me->composite->read(me->composite, data, length);
        me->mutex->unlock(me->mutex);
    }
}



/******************************************************************************
 Public functions
******************************************************************************/

ThreadSafeByteStreamHandle ThreadSafeByteStream_create(IMutexHandle mutex, IByteStream* streamToProtect)
{
    ThreadSafeByteStreamHandle me = (ThreadSafeByteStreamHandle) malloc(sizeof(ThreadSafeByteStreamPrivateData));
    assert(me);

    me->mutex = mutex;
    me->composite = streamToProtect;

    me->parent.handle = me;
    me->parent.read = &read;
    me->parent.write = &write;
    me->parent.capacity = &capacity;
    me->parent.flush = &flush;
    me->parent.writeByte = &writeByte;
    me->parent.length = &length;
    me->parent.readByte = &readByte;
    me->parent.byteIsReady = &byteIsReady;

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
