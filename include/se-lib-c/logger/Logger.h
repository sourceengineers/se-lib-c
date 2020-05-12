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
 * @param 
 * @return
 */
LoggerHandle Logger_create(size_t bufferSize);

/**
 * Log of messages
 * @param self
 * @return
 */
 // TODO check if this is needed? I think it would be better to make this function private to avoid direct access
void Logger_log(LoggerHandle self, SEVERITY severity, const char* msg );

/**
 * Returns the ILogger interface
 * @param LoggerHandle
 * @return ILoggerHandle
 */
ILoggerHandle Logger_getILogger(LoggerHandle self);

/**
 * Returns the messagebuffer
 * @param self
 * @return char*
 */
// TODO check if this is needed?
char* Logger_getBuffer(LoggerHandle self);

/**
 * Returns the buffered byte stream
 * @param self
 * @return char*
 */
// TODO check if this is needed?
char* Logger_getBufferedByteStream(LoggerHandle self);


/**
 * Destructor
 * @param
 * @return
 */
 void LoggerDestroy(LoggerHandle self);

#endif //SE_SCOPE_LOGGER_H