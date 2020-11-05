/*!****************************************************************************************************************************************
 * @file         LoggerBuilder.c
 *
 * @copyright    Copyright (c) 2019 by Sourceengineers. All Rights Reserved.
 *
 * @authors      Benjamin Rupp  benjamin.rupp@sourceengineers.com
 *
 *****************************************************************************************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <Scope/GeneralPurpose/IMutex.h>
#include <se-lib-c/logger/LoggerBuilder.h>
#include <se-lib-c/stream/BufferedByteStream.h>
#include <se-lib-c/stream/ThreadSafeByteStream.h>

/******************************************************************************
 Define private data
******************************************************************************/
typedef struct __LoggerBuilderPrivateData{
    LoggerHandle logger;
    IByteStreamHandle loggerBufferByteStream;
    BufferedByteStreamHandle loggerBuffer;
    ThreadSafeByteStreamHandle tsLoggerBuffer;
    IMutexHandle mutex;
    size_t bufferSize;
} LoggerBuilderPrivateData;

// the builder is a singleton
//static LoggerBuilderPrivateData me;

/******************************************************************************
 Private functions
******************************************************************************/

/******************************************************************************
 Public functions
******************************************************************************/
LoggerBuilderHandle LoggerBuilder_create(void){
    LoggerBuilderHandle me = malloc(sizeof(LoggerBuilderPrivateData));

    me->logger = NULL;
    me->loggerBufferByteStream = NULL;
    me->loggerBuffer = NULL;
    me->tsLoggerBuffer = NULL;
    me->mutex = NULL;
    return me;
}

void LoggerBuilder_setBufferSize(LoggerBuilderHandle me, size_t bufferSize){
    me->bufferSize = bufferSize;
}

void LoggerBuilder_setLoggerBuffer(LoggerBuilderHandle me, BufferedByteStreamHandle loggerBuffer){
	me->loggerBuffer = loggerBuffer;
}

void LoggerBuilder_setMutex(LoggerBuilderHandle me, IMutexHandle mutex){
	me->mutex = mutex;
}

void LoggerBuilder_setThreadSafeByteStream(LoggerBuilderHandle me, ThreadSafeByteStreamHandle tsLoggerBuffer){
	me->tsLoggerBuffer = tsLoggerBuffer;
}

//LoggerObject LoggerBuilder_build(size){

void LoggerBuilder_build(LoggerBuilderHandle me){
	assert(me->loggerBuffer);
	me->loggerBufferByteStream = BufferedByteStream_getIByteStream(me->loggerBuffer);
	assert(me->loggerBufferByteStream);

    me->logger = Logger_create(me->bufferSize, me->loggerBufferByteStream);
	assert(me->logger);
}

//LoggerObject LoggerBuilder_buildThreadSafe(LoggerBuilderHandle me){

void LoggerBuilder_buildThreadSafe(LoggerBuilderHandle me){
	assert(me->loggerBuffer);
	assert(me->mutex);

	me->loggerBufferByteStream = ThreadSafeByteStream_getIByteStream(me->loggerBuffer);
	assert(me->loggerBufferByteStream);
	me->tsLoggerBuffer = ThreadSafeByteStream_create(me->mutex, me->loggerBufferByteStream);
	assert(me->tsLoggerBuffer);
}

char* LoggerBuilder_getBuffer(LoggerBuilderHandle me){
    return Logger_getBuffer(me->logger);
}

IByteStreamHandle LoggerBuilder_getILoggerBufferHandle(LoggerBuilderHandle me){
	return me->loggerBufferByteStream;
}

ILoggerHandle LoggerBuilder_getILoggerHandle(LoggerBuilderHandle me){
	return Logger_getILogger(me->logger);
}


void LoggerBuilder_destroy(LoggerBuilderHandle me){
    LoggerDestroy(me->logger);
}

