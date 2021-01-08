/*!****************************************************************************************************************************************
 * @file         Logger.c
 *
 * @copyright    Copyright (c) 2019 by Sourceengineers. All Rights Reserved.
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
