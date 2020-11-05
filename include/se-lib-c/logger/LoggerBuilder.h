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
#ifndef SE_SCOPE_LOGGERBUILDER_H
#define SE_SCOPE_LOGGERBUILDER_H

#include <se-lib-c/logger/Logger.h>
#include <se-lib-c/stream/IByteStream.h>
#include <se-lib-c/stream/BufferedByteStream.h>
#include <se-lib-c/stream/ThreadSafeByteStream.h>


/******************************************************************************
 Define class handle data
******************************************************************************/
typedef struct __LoggerBuilderPrivateData* LoggerBuilderHandle;


/******************************************************************************
 Define Interface
******************************************************************************/

/******************************************************************************
 Public functions 
******************************************************************************/

LoggerBuilderHandle LoggerBuilder_create(void);

void LoggerBuilder_setBufferSize(LoggerBuilderHandle me, size_t bufferSize);

void LoggerBuilder_setLoggerBuffer(LoggerBuilderHandle me, BufferedByteStreamHandle loggerBuffer);

void LoggerBuilder_setMutex(LoggerBuilderHandle me, IMutexHandle mutex);

void LoggerBuilder_setThreadSafeByteStream(LoggerBuilderHandle me, ThreadSafeByteStreamHandle tsLoggerBuffer);

void LoggerBuilder_buildThreadSafe(LoggerBuilderHandle me);

void LoggerBuilder_build(LoggerBuilderHandle me);

char* LoggerBuilder_getBuffer(LoggerBuilderHandle me);

char* LoggerBuilder_getBufferedByteStream(LoggerBuilderHandle me);

IByteStreamHandle LoggerBuilder_getILoggerBufferHandle(LoggerBuilderHandle me);

ILoggerHandle LoggerBuilder_getILoggerHandle(LoggerBuilderHandle me);


/**
 * Deconstructor
 * @param me
 */
void LoggerBuilder_destroy(LoggerBuilderHandle me);

#endif //SE_SCOPE_LOGGERBUILDER_H
