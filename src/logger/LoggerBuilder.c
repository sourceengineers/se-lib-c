/*!****************************************************************************************************************************************
 * @file         LoggerBuilder.c
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
#include <se-lib-c/logger/LoggerBuilder.h>
#include <stdlib.h>

/******************************************************************************
 Define private data
******************************************************************************/
typedef struct __LoggerBuilderPrivateData{
    IByteStreamHandle streamer;
    LoggerHandle  logger;
    size_t bufferSize;
} LoggerBuilderPrivateData;
/******************************************************************************
 Private functions
******************************************************************************/

/******************************************************************************
 Public functions
******************************************************************************/
LoggerBuilderHandle LoggerBuilder_create(void){

    LoggerBuilderHandle self = malloc(sizeof(LoggerBuilderPrivateData));

    self->logger = NULL;
    self->streamer = NULL;

    return self;
}

void LoggerBuilder_setBufferSize(LoggerBuilderHandle self, size_t bufferSize){
    self->bufferSize = bufferSize;
}

LoggerObject LoggerBuilder_build(LoggerBuilderHandle self){

    LoggerObject obj;

    //self->logger = Logger_create( self->bufferSize );
    obj.logger = Logger_getILogger(self->logger);

    return  obj;
}

char* LoggerBuilder_getBuffer(LoggerBuilderHandle self){
    return Logger_getBuffer(self->logger);
}

void LoggerBuilder_destroy(LoggerBuilderHandle self){
    LoggerDestroy(self->logger);
}

void LoggerBuilder_setStream(LoggerBuilderHandle self, IByteStreamHandle streamer){
    self->streamer = streamer;
}
