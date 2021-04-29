/*!****************************************************************************************************************************************
 * @file         LoggerBuilder.c
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
