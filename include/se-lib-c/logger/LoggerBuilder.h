/*!*****************************************************************************
 * @file         ${HEADER_FILENAME}
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
