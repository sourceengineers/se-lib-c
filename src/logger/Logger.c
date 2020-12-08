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
#include "se-lib-c/stream/IByteStream.h"
#include "se-lib-c/stream/ThreadSafeByteStream.h"
#include "Scope/Core/Scope.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/******************************************************************************
 Define private data
******************************************************************************/
char* strSeverity[4] = {"INFO", "DEBUG", "WARNING", "ERROR"};

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
//static bool loggerStreamLogMessage(IByteStreamHandle stream, LoggerHandle self);		//TODO is this needed?

/******************************************************************************
 Private functions
******************************************************************************/

/******************************************************************************
 Public functions
******************************************************************************/

LoggerHandle Logger_create(size_t logMessageSize, size_t logBufferSize, IByteStreamHandle byteStream)
{
    LoggerHandle self = malloc(sizeof(LoggerPrivateData));
    assert(self);
    self->logBuffer = malloc(logBufferSize);
    assert(self->logBuffer);
    self->logMessageSize = logMessageSize;
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

// attach observer


static void loggerLog(ILoggerHandle parent, const char* msg)
{
	LoggerHandle self = (LoggerHandle) parent->handle;
	char logBufferLocal[self->logMessageSize];

    if (&self->logBuffer != NULL)
    {
    	strcpy(logBufferLocal, msg);
        if(self->byteStream &&
           !self->byteStream->write(self->byteStream, (uint8_t*) logBufferLocal, strlen(logBufferLocal)))
        {  /* Buffer overflow. Write "SCOPE BUF OVFL;" to byteStream */
        	//TODO ask how many bytes are available in the stream, print this many instead, add overflow message
        	if(self->byteStream->capacity(self->byteStream) > strlen("SCOPE_BUF_OVFL\n")){
            	self->byteStream->write(self->byteStream, (uint8_t*) "SCOPE BUF OVFL\n", strlen("SCOPE BUF OVFL\n"));
        	}
        	else{
            	self->byteStream->flush(self->byteStream);
            	self->byteStream->write(self->byteStream, (uint8_t*) "SCOPE BUF OVFL\n", strlen("SCOPE BUF OVFL\n"));
        	}
        }
    }
}

#ifdef UNIT_TEST
char* Logger_getBuffer(LoggerHandle self)
{
    return self->logBuffer;
}

void LoggerDestroy(LoggerHandle self)
{
    free(self);
}
#endif
