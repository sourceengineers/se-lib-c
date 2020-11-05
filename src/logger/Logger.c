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

static void loggerLog(LoggerHandle self, SEVERITY severity, const char* msg);
//static bool loggerStreamLogMessage(IByteStreamHandle stream, LoggerHandle self);		//TODO is this needed?
static char* loggerPrepareSeverity(SEVERITY severity);
/******************************************************************************
 Private functions
******************************************************************************/

static char* loggerPrepareSeverity(SEVERITY severity)
{
    return strSeverity[severity];
}

/******************************************************************************
 Public functions
******************************************************************************/

LoggerHandle Logger_create(size_t logMessageSize, IByteStreamHandle byteStream)
{
    LoggerHandle self = malloc(sizeof(LoggerPrivateData));
    assert(self);
    self->logBuffer = malloc(logMessageSize);
    assert(self->logBuffer);
    self->logMessageSize = logMessageSize;
    self->byteStream = byteStream;
    assert(self->byteStream);

    // setup the base-class (ILog interface)
    self->loggerBase.handle = self;
    self->loggerBase.log = &loggerLog;		//TODO dem nachgehen

    return self;
}

ILoggerHandle Logger_getILogger(LoggerHandle self)
{
    return &self->loggerBase;
}


static void loggerLog(LoggerHandle self, SEVERITY severity, const char* msg)
{
    char separating_seq[] = ": ";       // sequence between severity and log message
    char *severity_string = loggerPrepareSeverity(severity);

    // hier mutex-lock

    // funktion reentrant machen mit
    char logBufferLocal[50];
//    strcpy(logBufferLocal, self->logBuffer);
    if (&self->logBuffer != NULL)
    {
        strcpy(logBufferLocal, severity_string);
        strcat(logBufferLocal, separating_seq);
        uint32_t lengthOfCurrentMessage = strlen(msg)+strlen(separating_seq)+strlen(severity_string);
        if (lengthOfCurrentMessage < self->logMessageSize)
        {
            strcat(logBufferLocal, msg);
        }
        else    /* string is too long, must be shortened */
        {
            lengthOfCurrentMessage = self->logMessageSize;
            strncat(logBufferLocal, msg, self->logMessageSize - strlen(severity_string) - strlen(separating_seq));
        }

        if(self->byteStream &&
           !self->byteStream->write(self->byteStream, logBufferLocal, lengthOfCurrentMessage))
        {  /* Buffer Overflow */
            if(lengthOfCurrentMessage<strlen("SCOPE BUF OVFL;")){
                strcpy(logBufferLocal, "SCOPE BUF OVFL;");
            }
            else{
                strncpy(logBufferLocal + (lengthOfCurrentMessage-strlen("SCOPE BUF OVFL;")), "SCOPE BUF OVFL;", strlen("SCOPE BUF OVFL;"));
            }
        }
//        strcpy(self->logBuffer, logBufferLocal);	//TODO this is not reentrant, is it? If not, how can i make it
    }

	//    TODO hier sc_log setzen ähnlich wie in CommandAnnounce, damit bekannt gegeben wird, dass eine log-nachricht bereit ist.
	//    Oder einfach Scope_log() aufrufen? Macht genau das.
	//    self
	//    CommandAnnounceHandle self = (CommandAnnounceHandle) command->handle;
	//    MessageType packType = SC_LOG;
	//    self->
	//    self->packObserver->update(self->packObserver, &packType);
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
