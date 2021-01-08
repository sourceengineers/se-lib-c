/*!****************************************************************************************************************************************
 * @file         LoggerBuilder.c
 *
 * @copyright    Copyright (c) 2019 by Sourceengineers. All Rights Reserved.
 *
 * @authors      Benjamin Rupp  benjamin.rupp@sourceengineers.com
 * 				 Anselm Fuhrer	anselm.fuhrer@sourceengineers.com
 *
 *****************************************************************************************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <se-lib-c/osal/IMutex.h>
#include <se-lib-c/logger/LoggerBuilder.h>

/******************************************************************************
 Define private data
******************************************************************************/
typedef struct __LoggerBuilderPrivateData{
	LoggerHandle logger;
    ThreadSafeByteStreamHandle tsLoggerBuffer;
    BufferedByteStreamHandle loggerBuffer;
} LoggerBuilderPrivateData;


// the builder is a singleton
static LoggerBuilderPrivateData me = {0};

/******************************************************************************
 Private functions
******************************************************************************/

/******************************************************************************
 Public functions
******************************************************************************/
void LoggerBuilder_create(void)
{
    me.logger = NULL;
    me.tsLoggerBuffer = NULL;
    me.loggerBuffer = NULL;
}

void LoggerBuilder_build(size_t logMessageSize, size_t logBufferSize){
	// build logger-buffer without mutex
	me.loggerBuffer = BufferedByteStream_create(logBufferSize);
	assert(me.loggerBuffer);
	// build logger on top of logger-buffer
	IByteStream* byteStream = BufferedByteStream_getIByteStream(me.loggerBuffer);
	assert(byteStream);
    me.logger = Logger_create(logMessageSize, byteStream);
	assert(me.logger);
}

void LoggerBuilder_buildThreadSafe(size_t logMessageSize, size_t logBufferSize,  IMutexHandle mutex)
{
	assert(mutex);

	me.loggerBuffer = BufferedByteStream_create(logBufferSize);
	assert(me.loggerBuffer);

	IByteStream* byteStream = BufferedByteStream_getIByteStream(me.loggerBuffer);
	assert(byteStream);

	me.tsLoggerBuffer = ThreadSafeByteStream_create(mutex, byteStream);
    assert(me.tsLoggerBuffer);

    byteStream = ThreadSafeByteStream_getIByteStream(me.tsLoggerBuffer);
    assert(byteStream);

	me.logger = Logger_create(logMessageSize, byteStream);
	assert(me.logger);
}


IByteStreamHandle LoggerBuilder_getILoggerBufferHandle()
{
	assert(me.loggerBuffer);

	IByteStream* byteStream = NULL;
	if(me.tsLoggerBuffer)
	{
		byteStream = ThreadSafeByteStream_getIByteStream(me.tsLoggerBuffer);
	}
	else
	{
		byteStream = BufferedByteStream_getIByteStream(me.loggerBuffer);
	}

	return byteStream;
}

ILoggerHandle LoggerBuilder_getILoggerHandle()
{
	assert(me.logger);
	return Logger_getILogger(me.logger);
}

