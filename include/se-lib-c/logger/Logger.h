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
LoggerHandle Logger_create(size_t logMessageSize, IByteStreamHandle byteStream);

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
