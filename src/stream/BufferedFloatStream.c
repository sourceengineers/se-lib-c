/*!****************************************************************************************************************************************
 * @file         BufferedFloatStream.c
 *
 * @copyright    Copyright (c) 2018 by Sourceengineers. All Rights Reserved.
 *
 * @license      This file is part of SE-Lib-C.
 *
 *               SE-Lib-C is free software; you can redistribute it and/or
 *               modify it under the terms of the GNU General Public License as
 *               published by the Free Software Foundation.
 *
 *               SE-Lib-C is distributed in the hope that it will be useful,
 *               but WITHOUT ANY WARRANTY; without even the implied warranty of
 *               MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *               GNU General Public License for more details.
 *
 *               You should have received a copy of the GNU General Public License
 *               along with SE-Lib-C.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @authors      Samuel Schuepbach samuel.schuepbach@sourceengineers.com
 *
 *****************************************************************************************************************************************/

#include <se-lib-c/stream/BufferedFloatStream.h>
#include <se-lib-c/container/FloatRingBuffer.h>
#include <se-lib-c/stream/IFloatStream.h>
#include <stdlib.h>
#include <assert.h>

/******************************************************************************
 Define private data
******************************************************************************/
/* Class data */
typedef struct __BufferedFloatStreamPrivateData{
    IFloatStream parent;
    FloatRingBufferHandle buffer;

} BufferedFloatStreamPrivateData;

static bool dataIsReady(IFloatStreamHandle stream);

static float readData(IFloatStreamHandle stream);

static void readAll(IFloatStreamHandle stream, float* data, const size_t length);

static size_t streamLength(IFloatStreamHandle stream);

static void writeData(IFloatStreamHandle stream, const float data);

static void writeAll(IFloatStreamHandle stream, const float* data, const size_t length);

static void flush(IFloatStreamHandle stream);

static size_t getCapacity(IFloatStreamHandle stream);

/******************************************************************************
 Private functions
******************************************************************************/
static bool dataIsReady(IFloatStreamHandle stream){
    BufferedFloatStreamHandle self = (BufferedFloatStreamHandle) stream->handle;

    if(FloatRingBuffer_getNumberOfUsedData(self->buffer) > 0){
        return true;
    }else{
        return false;
    }
}

static float readData(IFloatStreamHandle stream){
    BufferedFloatStreamHandle self = (BufferedFloatStreamHandle) stream->handle;

    float data;
    FloatRingBuffer_read(self->buffer, &data, 1);

    return data;
}

static void readAll(IFloatStreamHandle stream, float* data, const size_t length){
    BufferedFloatStreamHandle self = (BufferedFloatStreamHandle) stream->handle;

    FloatRingBuffer_read(self->buffer, data, length);
}

static size_t streamLength(IFloatStreamHandle stream){
    BufferedFloatStreamHandle self = (BufferedFloatStreamHandle) stream->handle;

    return FloatRingBuffer_getNumberOfUsedData(self->buffer);
}

static void writeData(IFloatStreamHandle stream, const float data){
    BufferedFloatStreamHandle self = (BufferedFloatStreamHandle) stream->handle;

    if(FloatRingBuffer_write(self->buffer, &data, 1) == -1){
        float dump;
        FloatRingBuffer_read(self->buffer, &dump, 1);
        FloatRingBuffer_write(self->buffer, &data, 1);
    }
}

static void writeAll(IFloatStreamHandle stream, const float* data, const size_t length){
    for(int i = 0; i < length; ++i){
        stream->writeData(stream, data[i]);
    }
}

static void flush(IFloatStreamHandle stream){
    BufferedFloatStreamHandle self = (BufferedFloatStreamHandle) stream->handle;

    FloatRingBuffer_clear(self->buffer);
}

static size_t getCapacity(IFloatStreamHandle stream){
    BufferedFloatStreamHandle self = (BufferedFloatStreamHandle) stream->handle;

    return FloatRingBuffer_getCapacity(self->buffer);
}

/******************************************************************************
 Public functions
******************************************************************************/

BufferedFloatStreamHandle BufferedFloatStream_create(size_t capacity){

    BufferedFloatStreamHandle self = (BufferedFloatStreamHandle) malloc(sizeof(BufferedFloatStreamPrivateData));
    assert(self);
    self->buffer = FloatRingBuffer_create(capacity);

    self->parent.handle = self;
    self->parent.dataIsReady = &dataIsReady;
    self->parent.readData = &readData;
    self->parent.length = &streamLength;
    self->parent.read = &readAll;
    self->parent.writeData = writeData;
    self->parent.write = writeAll;
    self->parent.flush = flush;
    self->parent.capacity = &getCapacity;

    return self;
}

void BufferedFloatStream_destroy(BufferedFloatStreamHandle self){
    FloatRingBuffer_destroy(self->buffer);

    free(self);
    self = NULL;
}

IFloatStreamHandle BufferedFloatStream_getIFloatStream(BufferedFloatStreamHandle self){
    return &self->parent;
}
