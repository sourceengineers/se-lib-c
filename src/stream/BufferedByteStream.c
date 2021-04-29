/*!****************************************************************************************************************************************
 * @file         BufferedByteStream.c
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
 * @authors      Samuel Schuepbach <samuel.schuepbach@sourceengineers.com>
 *
 *****************************************************************************************************************************************/

#include <se-lib-c/stream/IByteStream.h>
#include <se-lib-c/stream/BufferedByteStream.h>
#include <se-lib-c/container/ByteRingBuffer.h>

#include <stdlib.h>
#include <assert.h>

/******************************************************************************
 Define private data
******************************************************************************/
/* Class data */
typedef struct __BufferedByteStreamPrivateData
{
    IByteStream parent;
    ByteRingBufferHandle buffer;
} BufferedByteStreamPrivateData;

/******************************************************************************
 Private functions
******************************************************************************/
static bool dataIsReady(IByteStreamHandle parent)
{
    BufferedByteStreamHandle self = (BufferedByteStreamHandle) parent->handle;

    if(ByteRingBuffer_getNumberOfUsedData(self->buffer) > 0){
        return true;
    }else{
        return false;
    }
}

static uint8_t readData(IByteStreamHandle parent)
{
    BufferedByteStreamHandle self = (BufferedByteStreamHandle) parent->handle;
    uint8_t data;
    ByteRingBuffer_read(self->buffer, &data, 1);
    return data;
}

static void readAll(IByteStreamHandle parent, uint8_t* data, const size_t length)
{
    BufferedByteStreamHandle self = (BufferedByteStreamHandle) parent->handle;
    ByteRingBuffer_read(self->buffer, data, length);
}

static size_t streamLength(IByteStreamHandle parent)
{
    BufferedByteStreamHandle self = (BufferedByteStreamHandle) parent->handle;
    return ByteRingBuffer_getNumberOfUsedData(self->buffer);
}

bool writeByte(IByteStreamHandle parent, const uint8_t data)
{
    BufferedByteStreamHandle self = (BufferedByteStreamHandle) parent->handle;
    bool success = false;

    if(-1 == ByteRingBuffer_write(self->buffer, &data, 1))
    {
        success = false;
    }
    else
    {
        success = true;
    }
   return success;
}

static bool write(IByteStreamHandle parent, const uint8_t* data, const size_t length)
{
    BufferedByteStreamHandle self = (BufferedByteStreamHandle) parent->handle;
    bool success = false;

    if(-1 == ByteRingBuffer_write(self->buffer,data,length))
    {
        success = false;
    } else
    {
        success = true;
    }
   return success;
}

static void flush(IByteStreamHandle parent)
{
    BufferedByteStreamHandle self = (BufferedByteStreamHandle) parent->handle;
    ByteRingBuffer_clear(self->buffer);
}

static size_t getCapacity(IByteStreamHandle stream)
{
    BufferedByteStreamHandle self = (BufferedByteStreamHandle) stream->handle;
    return ByteRingBuffer_getCapacity(self->buffer);
}
/******************************************************************************
 Public functions
******************************************************************************/
BufferedByteStreamHandle BufferedByteStream_create(size_t capacity)
{

    BufferedByteStreamHandle self = (BufferedByteStreamHandle) malloc(sizeof(BufferedByteStreamPrivateData));
    assert(self);

    self->buffer = ByteRingBuffer_create(capacity);

    self->parent.handle = self;
    self->parent.byteIsReady = &dataIsReady;
    self->parent.readByte = &readData;
    self->parent.length = &streamLength;
    self->parent.read = &readAll;
    self->parent.writeByte = &writeByte;
    self->parent.write = &write;
    self->parent.flush = &flush;
    self->parent.capacity = &getCapacity;

    return self;
}

void BufferedByteStream_destroy(BufferedByteStreamHandle self)
{
    ByteRingBuffer_destroy(self->buffer);
    free(self);
    self = NULL;
}

IByteStreamHandle BufferedByteStream_getIByteStream(BufferedByteStreamHandle self)
{
    return &self->parent;
}
