/*!*****************************************************************************
 * @file         ThreadSafeByteStream.h
 *
 * @copyright    Copyright (c) 2020 by Sourceengineers. All Rights Reserved.
 *
 * @authors      Anselm Fuhrer anselm.fuhrer@sourceengineers.com
 *
 * @brief        TODO
 *
 ******************************************************************************/

#ifndef BYTESTREAM_H_
#define BYTESTREAM_H_

#include <se-lib-c/definition/SeLibCTypes.h>
#include <se-lib-c/stream/IByteStream.h>
#include <se-lib-c/osal/IMutex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/******************************************************************************
 Define class handle data
******************************************************************************/
typedef struct __ThreadSafeByteStreamPrivateData* ThreadSafeByteStreamHandle;

/******************************************************************************
 Public functions
******************************************************************************/
/**
 * Constructor
 * @param capacity size of the buffer
 * @return
 */
ThreadSafeByteStreamHandle ThreadSafeByteStream_create(IMutexHandle mutex, IByteStream streamToProtect);

/**
 * Returns the stream interface
 * @param self
 * @return
 */
IByteStreamHandle ThreadSafeByteStream_getIByteStream(ThreadSafeByteStreamHandle self);

/**
 * Deconstructor
 * @param self
 */
void ThreadSafeByteStream_destroy(ThreadSafeByteStreamHandle self);

#endif
