/*!*****************************************************************************
 * @file         IntRingBuffer.h
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
 * @brief        Implementation of a ringbuffer for int values.
 *
 ******************************************************************************/

#ifndef INTRINGBUFFER_H_
#define INTRINGBUFFER_H_

#include <se-lib-c/definition/SeLibCTypes.h>
#include <se-lib-c/stream/IIntStream.h>
#include <stddef.h>
#include <stdint.h>

/******************************************************************************
 Define class handle data
******************************************************************************/
typedef struct __IntRingBufferPrivateData* IntRingBufferHandle;

/******************************************************************************
 Public functions
******************************************************************************/
/**
 * Constructor
 * @param capacity
 * @return
 */
IntRingBufferHandle IntRingBuffer_create(size_t capacity);

/**
 * Returns the capacity of the buffer
 * @param self
 * @return
 */
size_t IntRingBuffer_getCapacity(IntRingBufferHandle self);

/**
 * Returns the amount of empty space in the buffer
 * @param self
 * @return
 */
size_t IntRingBuffer_getNumberOfFreeData(IntRingBufferHandle self);

/**
 * Returns the amount of filled space in the buffer
 * @param self
 * @return
 */
size_t IntRingBuffer_getNumberOfUsedData(IntRingBufferHandle self);

/**
 * Writes the data in to the buffer. The amount of written data will be returned.
 * @param self
 * @param data Array from which the data will be copied
 * @param length Amount of data to be written
 * @return If length > ByteRingBuffer_getNumberOfFreeData, -1 will be returned. Otherwise the amount of written
 *         data is returned
 */
int IntRingBuffer_write(IntRingBufferHandle self, const uint32_t* data, size_t length);

/**
 * Reads newest data and writes them in the passed byte array
 * @param self
 * @param data Array into which the data has to be written
 * @param length Max length of the data array.
 * @return If length < ByteRingBuffer_getNumberOfUsedData, -1 will be returned. Otherwise the amount of read data
 *          returned.
 */
int IntRingBuffer_read(IntRingBufferHandle self, uint32_t* data, size_t length);

/**
 * Same as a normal read operation, but resets the tail pointer to its original position.
 * therefore data can be read without being destroyed.
 * @param self
 * @param data
 * @param length
 * @return
 */
int IntRingBuffer_readNoPosInc(IntRingBufferHandle self, uint32_t* data, size_t length);

/**
 * Resets head and tail to their original position and therefore clearing the channel
 * @param self
 */
void IntRingBuffer_clear(IntRingBufferHandle self);

/**
 * Deconstructor
 * @param self
 */
void IntRingBuffer_destroy(IntRingBufferHandle self);

#endif
