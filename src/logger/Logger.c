/*!****************************************************************************************************************************************
 * @file         Logger.c
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
 * 			     Anselm Fuhrer  anselm.fuhrer@sourceengineers.com
 *
 *****************************************************************************************************************************************/
#include "se-lib-c/logger/Logger.h"
#include "se-lib-c/stream/ThreadSafeByteStream.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/******************************************************************************
 Define private data
******************************************************************************/
typedef struct __LoggerPrivateData
{
    /* Inherit  */
    ILogger loggerBase;
    // data to store current message
    char* logBuffer; // message with severity as text
    size_t logMessageSize;
    // stream to store formatted message
    IByteStreamHandle byteStream;
} LoggerPrivateData;

static void loggerLog(ILoggerHandle parent, const char* msg);

/******************************************************************************
 Private functions
******************************************************************************/

/******************************************************************************
 Public functions
******************************************************************************/

LoggerHandle Logger_create(size_t logMessageSize, IByteStreamHandle byteStream)
{
    LoggerHandle self = malloc(sizeof(LoggerPrivateData));
    assert(self);
    self->logMessageSize = logMessageSize;
    self->logBuffer = malloc(self->logMessageSize);
    assert(self->logBuffer);
    self->byteStream = byteStream;
    assert(self->byteStream);

    // setup the base-class (ILog interface)
    self->loggerBase.handle = self;
    self->loggerBase.log = &loggerLog;

    return self;
}

ILoggerHandle Logger_getILogger(LoggerHandle self)
{
    return &self->loggerBase;
}

static void loggerLog(ILoggerHandle parent, const char* msg)
{
    LoggerHandle self = (LoggerHandle) parent->handle;
    assert(strlen(msg)<=self->logMessageSize);

    if (&self->logBuffer != NULL)
    {
    	strcpy(self->logBuffer, msg);
        if(self->byteStream &&
           !self->byteStream->write(self->byteStream, (const uint8_t*) self->logBuffer, strlen(self->logBuffer)))
        {  /* Buffer overflow. Write "SCOPE BUF OVFL;" to byteStream */
        	if(self->byteStream->numOfFreeBytes(self->byteStream) > strlen("LOG BUF OVFL\n")){
            	self->byteStream->write(self->byteStream, (const uint8_t*) "LOG BUF OVFL\n", strlen("LOG BUF OVFL\n"));
        	}
        	else{   /* Not enough free space to write it. Flush, then write */
            	self->byteStream->flush(self->byteStream);
            	self->byteStream->write(self->byteStream, (const uint8_t*) "LOG BUF OVFL\n", strlen("LOG BUF OVFL\n"));
        	}
        }
    }
}
