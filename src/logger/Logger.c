/*!****************************************************************************************************************************************
 * @file         Logger.c
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
 *****************************************************************************************************************************************/
#include <se-lib-c/logger/Logger.h>
#include <se-lib-c/stream/IByteStream.h>
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
    LoggerHandle self = malloc(sizeof(LoggerPrivateData));
    assert(self);
    self->logBuffer = malloc(logMessageSize);
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

        if(self->byteStream &&
           !self->byteStream->write(self->byteStream, self->logBuffer, lengthOfCurrentMessage))
        {  /* Buffer Overflow */
            //TODO instead of replacing the contens, add buf ovfl at the end
            strcpy(self->logBuffer, "SCOPE BUF OVFL;");
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