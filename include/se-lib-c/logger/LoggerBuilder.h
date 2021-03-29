/*!*****************************************************************************
 * @file         ${HEADER_FILENAME}
 *
 * @copyright    Copyright (c) 2019 by Sourceengineers. All Rights Reserved.
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


/******************************************************************************
 Define class handle data
******************************************************************************/
typedef struct __LoggerBuilderPrivateData* LoggerBuilderHandle;


/******************************************************************************
 Define Interface
******************************************************************************/
typedef struct LoggerObjectStruct{

    ILoggerHandle logger;

} LoggerObject;
/******************************************************************************
 Public functions 
******************************************************************************/
/**
 * Constructor
 * @param 
 * @return LoggerBuilderHandle
 */
LoggerBuilderHandle LoggerBuilder_create(void);

/**
 * Set the buffer size of the message buffer
 * @param bufferSize
 */
void LoggerBuilder_setBufferSize(LoggerBuilderHandle self, size_t bufferSize);

/**
 * Builds the logger and return an object
 * @param self
 * @return LoggerObject
 */
LoggerObject LoggerBuilder_build(LoggerBuilderHandle self);

/**
 * Builds the logger and return an object
 * @param self
 * @return char* buffer of the current message
 */
char* LoggerBuilder_getBuffer(LoggerBuilderHandle self);

/**
 * Returns the content of the ByteStream
 * @param self
 */
char* LoggerBuilder_getBufferedByteStream(LoggerBuilderHandle self);

/**
 * Builds the logger and return an object
 * @param self
 * @param output
 */
void LoggerBuilder_setStream(LoggerBuilderHandle self, IByteStreamHandle output);
/**
 * Deconstructor
 * @param self
 */
void LoggerBuilder_destroy(LoggerBuilderHandle self);

#endif //SE_SCOPE_LOGGERBUILDER_H
