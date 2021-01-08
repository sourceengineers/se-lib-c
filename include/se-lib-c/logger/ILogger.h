/*!*****************************************************************************
 * @file         ${HEADER_FILENAME}
 *
 * @copyright    Copyright (c) 2019 by Sourceengineers. All Rights Reserved.
 *
 * @authors      Benjamin Rupp  benjamin.rupp@sourceengineers.com
 *
 * @brief        Interface to log printf-syle data
 *
 ******************************************************************************/

#ifndef ILOGGER_H_
#define ILOGGER_H_

#include <se-lib-c/definition/SeLibCTypes.h>

/******************************************************************************
 Define interface handle data
******************************************************************************/
typedef struct ILoggerStruct* ILoggerHandle;


/******************************************************************************
 Define interface
******************************************************************************/
typedef struct ILoggerStruct{
    SeLibGenericReferece handle;

    /**
     * Adds log messages to the buffer
     * @param logger
     */
 void (* log)(ILoggerHandle logger, const char* msg);

} ILogger;
#endif
