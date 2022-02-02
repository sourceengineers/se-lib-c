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
 *               is not valid. In these cases the purchased commercial license is applied.
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

void LoggerBuilder_buildThreadSafe(size_t logMessageSize, size_t logBufferSize, IMutexHandle mutex);

void LoggerBuilder_build(size_t logMessageSize, size_t logBufferSize);

IByteStreamHandle LoggerBuilder_getILoggerBufferHandle(void);

ILoggerHandle LoggerBuilder_getILoggerHandle(void);


#endif //SE_SCOPE_LOGGERBUILDER_H
