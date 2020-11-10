/*!*****************************************************************************
 * @file         ${HEADER_FILENAME}
 *
 * @copyright    Copyright (c) 2019 by Sourceengineers. All Rights Reserved.
 *
 * @authors      Benjamin Rupp  benjamin.rupp@sourceengineers.com
 *
 * @brief        
 *
 *
 ******************************************************************************/

#ifndef SE_SCOPE_LOGGER_H
#define SE_SCOPE_LOGGER_H

#include <se-lib-c/logger/ILogger.h>
#include <se-lib-c/util/observer/IObserver.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include <se-lib-c/stream/IByteStream.h>

/******************************************************************************
 Define class handle data
******************************************************************************/
typedef struct __LoggerPrivateData* LoggerHandle;

/******************************************************************************
 Public functions 
******************************************************************************/
/**
 * Constructor
 * @param 
 * @return
 */
LoggerHandle Logger_create(size_t logMessageSize, size_t logBufferSize, IByteStreamHandle byteStream);
/**
 * Returns the ILogger interface
 * @param LoggerHandle
 * @return ILoggerHandle
 */
ILoggerHandle Logger_getILogger(LoggerHandle self);


/**
 * Returns the buffered byte stream
 * @param self
 * @return char*
 */
IByteStreamHandle Logger_getBufferedByteStream(LoggerHandle self);


#ifdef UNIT_TEST
/**
 * Returns the messagebuffer
 * @param self
 * @return char*
 */
char* Logger_getBuffer(LoggerHandle self);

/**
 * Destructor
 * @param
 * @return
 */
 void LoggerDestroy(LoggerHandle self);
#endif

#endif //SE_SCOPE_LOGGER_H
