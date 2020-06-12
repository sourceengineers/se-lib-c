/*!****************************************************************************************************************************************
 * @file         Logger.c
 *
 * @copyright    Copyright (c) 2019 by Sourceengineers. All Rights Reserved.
 *
 * @authors      Benjamin Rupp  benjamin.rupp@sourceengineers.com
 *
 *****************************************************************************************************************************************/
#include <se-lib-c/logger/Logger.h>
#include <se-lib-c/stream/IByteStream.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


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
static bool loggerStreamLogMessage(IByteStreamHandle stream,LoggerHandle self);
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
    // TODO why is the byteStream always NULL, should not be!
    LoggerHandle self = malloc(sizeof(LoggerPrivateData));
    //TODO ASSERT(self);
    self->logBuffer = malloc(logMessageSize);
    //TODO ASSERT(self->logBuffer);
    self->logMessageSize = logMessageSize;
    self->byteStream = byteStream;
    //TODO ASSERT(self->byteStream);

    // setup the base-class (ILog interface)
    self->loggerBase.handle = self;
    self->loggerBase.log = &loggerLog;

    return self;
}

ILoggerHandle Logger_getILogger(LoggerHandle self)
{
    return &self->loggerBase;
}

static void loggerLog(LoggerHandle self, SEVERITY severity, const char* msg )
{
    char separating_seq[] = ": ";       // sequence between severity and log message
    char *severity_string = loggerPrepareSeverity(severity);

    if (self->logBuffer != NULL) {
        strcpy(self->logBuffer, severity_string);
        strcat(self->logBuffer, separating_seq);
        uint32_t lengthOfCurrentMessage = strlen(msg)+strlen(separating_seq)+strlen(severity_string);
        if (lengthOfCurrentMessage < self->logMessageSize)
        {
            strcat(self->logBuffer, msg);
        }
        else    /* string is too long, must be shortened */
        {
            lengthOfCurrentMessage = self->logMessageSize;
            strncat(self->logBuffer, msg, self->logMessageSize - strlen(severity_string) - strlen(separating_seq));
        }

        //byteStream is NULL
        if(self->byteStream &&
           !self->byteStream->write(self->byteStream,self->logBuffer,lengthOfCurrentMessage))
        {
            //TODO remove 10 bytes, add "BUF OVFL;"
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
    //TODO this. Who has to destroy the BufferedByteStream?
    free(self);
}
#endif