/*!*****************************************************************************
 * @file         ${HEADER_FILENAME}
 *
 * @copyright    Copyright (c) 2019 by Sourceengineers. All Rights Reserved.
 *
 * @authors      Benjamin Rupp  benjamin.rupp@sourceengineers.com
 *
 * @brief        Concrete logger class to process printf style log messages
 *
 ******************************************************************************/

#ifndef SE_LIBC_LOGGER_H
#define SE_LIBC_LOGGER_H

#include <se-lib-c/logger/ILogger.h>
#include <se-lib-c/util/observer/IObserver.h>
#include <se-lib-c/stream/IByteStream.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>

/******************************************************************************
 Define class handle data
******************************************************************************/
typedef struct __LoggerPrivateData* LoggerHandle;

/******************************************************************************
 Public functions 
******************************************************************************/
/**
 * Constructor
 * @param logMessageSize maximum size of one log message
 * @param logBufferSize size of buffer to store log-messages before they are sent.
 * @return handle to the logger instance
 */
LoggerHandle Logger_create(size_t logMessageSize, IByteStreamHandle byteStream);

/**
 * Returns the ILogger interface
 * @param LoggerHandle
 * @return ILoggerHandle
 */
ILoggerHandle Logger_getILogger(LoggerHandle self);


#endif //SE_LIBC_LOGGER_H
