/*!****************************************************************************************************************************************
 * @file         Logger.c
 *
 * @copyright    Copyright (c) 2019 by Sourceengineers. All Rights Reserved.
 *
 * @authors      Benjamin Rupp  benjamin.rupp@sourceengineers.com
 *
 *****************************************************************************************************************************************/
#include <se-lib-c/logger/Logger.h>
#include <se-lib-c/stream/BufferedByteStream.h>
#include <se-lib-c/stream/BufferedIntStream.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/******************************************************************************
 Define private data
******************************************************************************/
char* strSeverity[4] = {"INFO","DEBUG", "WARNING", "ERROR"};

typedef struct __LoggerPrivateData{
    /* Inherit  */
    // TODO rename to base
    ILogger logger;

    // data to store current message
    char* logMessage; // message with severity as text
    size_t bufferSize; // TODO rename to logMessageSize

    // stream to store formatted message
    BufferedByteStreamHandle streamLogMsg;

    SEVERITY severity; // TODO remove this
    time_t timestamp; // TODO remove timestamp
    size_t streamBufferSize; // TODO remove?
    char* stream; // TODO remove
    IObserverHandle observer; // TODO remove
} LoggerPrivateData;

static void loggerLog(ILoggerHandle logger, SEVERITY severity, const char* msg);
bool loggerStreamLogMessage(IByteStreamHandle stream,LoggerHandle self);
char* loggerPrepareSeverity(SEVERITY severity);
/******************************************************************************
 Private functions
******************************************************************************/

static void loggerLog(ILoggerHandle logger, SEVERITY severity, const char* msg){
    LoggerHandle self = (LoggerHandle) logger->handle;

    Logger_log(self, severity, msg);
}

char* loggerPrepareSeverity(SEVERITY severity){
    return strSeverity[severity];
}

bool loggerStreamLogMessage(IByteStreamHandle stream,LoggerHandle self){
    // only store if there's enough space in the stream
    size_t capacity, length;
    capacity  = stream->capacity(stream);
    length = stream->length(stream);

    char* info;

    // TODO move to previous function
    info = loggerPrepareSeverity(self->severity);

    if (strlen(self->logMessage)+strlen(info) + 2 < (capacity - length)){
        for(unsigned int i = 0; i < strlen(info); i++){
            uint8_t data = (uint8_t)info[i];
            stream->writeByte(stream,data);
        }
        stream->writeByte(stream,(uint8_t )'_');

        for(unsigned int i = 0; i < strlen(self->logMessage); i ++ ) {
            uint8_t data = (uint8_t )self->logMessage[i];
            stream->writeByte(stream, data);
        }
        stream->writeByte(stream,(uint8_t )'\n');
        return true;
    }
    return  false;
}


/******************************************************************************
 Public functions
******************************************************************************/
LoggerHandle Logger_create(size_t bufferSize){

    LoggerHandle self = malloc(sizeof(LoggerPrivateData));

    // TODO rename to logBuffer
    self->logMessage = malloc(bufferSize);
    self->bufferSize = bufferSize;

    // TODO analyze what this is doing. can we move this into a different class?
    self->streamBufferSize = Logger_calculateBufferSize();
    self->stream = malloc(self->streamBufferSize);
    self->streamLogMsg = BufferedByteStream_create(self->streamBufferSize);

    // setup the base-class (ILog interface)
    self->logger.handle = self;
    self->logger.log = &loggerLog;

    return self;
}

ILoggerHandle Logger_getILogger(LoggerHandle self){
    return &self->logger;
}

void Logger_log(LoggerHandle self, SEVERITY severity, const char* msg ) {
    IByteStreamHandle streamLogMsg = BufferedByteStream_getIByteStream(self->streamLogMsg);

    // TODO remove
    self->severity = severity;
    // TODO remove
    self->timestamp = time(NULL);

    if (self->logMessage != NULL) {
        if (strlen(msg) < self->bufferSize) {
            // TODO add string for severity to message
            strcpy(self->logMessage, msg);
        }
        // TODO remove handling of long messages, just cut message after max-number of bytes
        else {
            if (Logger_reallocateMemory(self, strlen(msg))) {
                strcpy(self->logMessage, msg);
            }
        }
    }
    // TODO remove success, can not be used
    bool success = loggerStreamLogMessage(streamLogMsg,self);
}


char* Logger_getBuffer(LoggerHandle self){
    return self->logMessage;
}

// TODO just return IByteStreamhandle here and remove the rest
char* Logger_getBufferedByteStream(LoggerHandle self){
    IByteStreamHandle buffer;
    buffer = BufferedByteStream_getIByteStream(self->streamLogMsg);

    buffer->read(buffer,self->stream, buffer->length(buffer));

    return self->stream;
}

bool Logger_reallocateMemory(LoggerHandle self, size_t mem){
    free(self->logMessage);
    self->logMessage = malloc(mem);
}

void Logger_attachBufferObserver(LoggerHandle self, IObserverHandle observer){
    self->observer = observer;
}

size_t Logger_calculateBufferSize(){
    return 100;
}

void LoggerDestroy(LoggerHandle self){
    BufferedByteStream_destroy(self->streamLogMsg);

    free(self);
}