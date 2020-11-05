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

/******************************************************************************
 Define Interface
******************************************************************************/

/******************************************************************************
 Public functions 
******************************************************************************/

void LoggerBuilder_create(void);

void LoggerBuilder_buildThreadSafe(size_t bufferSize, IMutexHandle mutex);

void LoggerBuilder_build(size_t bufferSize);

IByteStreamHandle LoggerBuilder_getILoggerBufferHandle(void);

ILoggerHandle LoggerBuilder_getILoggerHandle(void);


#endif //SE_SCOPE_LOGGERBUILDER_H
