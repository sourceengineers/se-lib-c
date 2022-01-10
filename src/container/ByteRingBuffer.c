/*!****************************************************************************************************************************************
 * @file         ByteRingBuffer.c
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

#include <se-lib-c/container/ByteRingBuffer.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

/******************************************************************************
 Define private data
******************************************************************************/
/* Class data */
typedef struct __ByteRingBufferPrivateData{
    uint8_t* data;
    uint8_t* head;
    uint8_t* tail;
    size_t capacity;

} ByteRingBufferPrivateData;

/* Returns the next index of the given index */
inline static uint8_t* nextIndex(ByteRingBufferHandle self, uint8_t* index);

/* Increments the tail index */
inline static bool incTail(ByteRingBufferHandle self);

/* Increments the head index */
inline static bool incHead(ByteRingBufferHandle self);

/******************************************************************************
 Private functions
******************************************************************************/
inline static uint8_t* nextIndex(ByteRingBufferHandle self, uint8_t* index){
    const uint32_t positionRelative = ((index + 1) - self->data);
    return (positionRelative % self->capacity) + self->data;
}

static bool incTail(ByteRingBufferHandle self){
    if(self->tail != self->head){
        self->tail = nextIndex(self, self->tail);
        return true;
    }
    return false;
}

static bool incHead(ByteRingBufferHandle self){
    if(nextIndex(self, self->head) != self->tail){
        self->head = nextIndex(self, self->head);
        return true;
    }
    return false;
}

/******************************************************************************
 Public functions
******************************************************************************/
ByteRingBufferHandle ByteRingBuffer_create(size_t capacity){

    /* Allocate memory and set _private variables */
    ByteRingBufferHandle self = malloc(sizeof(ByteRingBufferPrivateData));
    assert(self);

    self->capacity = capacity + 1;
    self->data = malloc(sizeof(uint8_t) * self->capacity);
    assert(self->data);

    self->tail = self->data;
    self->head = self->data;

    return self;
}

void ByteRingBuffer_destroy(ByteRingBufferHandle self){
    free(self->data);
    self->data = NULL;
    free(self);
    self = NULL;
}

size_t ByteRingBuffer_getCapacity(ByteRingBufferHandle self){
    return self->capacity - 1;
}

size_t ByteRingBuffer_getNumberOfFreeData(ByteRingBufferHandle self){
    return (size_t) (self->capacity - (ByteRingBuffer_getNumberOfUsedData(self))) - 1;
}

size_t ByteRingBuffer_getNumberOfUsedData(ByteRingBufferHandle self){

    const size_t absSize = (self->head >= self->tail) ?
                           (self->head - self->tail) :
                           (self->capacity - (self->tail - self->head));

    return absSize % self->capacity;
}

void ByteRingBuffer_clear(ByteRingBufferHandle self){
    self->head = self->data;
    self->tail = self->data;
}

int ByteRingBuffer_write(ByteRingBufferHandle self, const uint8_t* data, const size_t length){

    if(length > ByteRingBuffer_getNumberOfFreeData(self)){
        return -1;
    }

    size_t i = 0;
    do{
        *(self->head) = data[i++];
        /* Catch buffer overflow */
        if(incHead(self) == false){
            return -1;
        }
    }while(length > i);

    return i;
}

int ByteRingBuffer_readNoPosInc(ByteRingBufferHandle self, uint8_t* data, const size_t length){

    uint8_t* tailBackup = self->tail;
    int ret = ByteRingBuffer_read(self, data, length);
    self->tail = tailBackup;
		return ret;
}

int ByteRingBuffer_read(ByteRingBufferHandle self, uint8_t* data, const size_t length){

    if(length > ByteRingBuffer_getNumberOfUsedData(self)){
        return -1;
    }

    size_t i = 0;
    do{
        data[i++] = *(self->tail);
        /* Catch buffer overflow */
        if(incTail(self) == false){
            return -1;
        }
    }while(length > i);

    return i;
}
