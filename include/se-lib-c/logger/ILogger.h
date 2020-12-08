/*!*****************************************************************************
 * @file         ${HEADER_FILENAME}
 *
 * @copyright    Copyright (c) 2019 by Sourceengineers. All Rights Reserved.
 *
 * @authors      Benjamin Rupp  benjamin.rupp@sourceengineers.com
 *
 * @brief        
 *
 *
 ******************************************************************************/

#ifndef ILOGGER_H_
#define ILOGGER_H_

#include <se-lib-c/definition/SeLibCTypes.h>

/******************************************************************************
 Define interface handle data
******************************************************************************/
typedef struct ILoggerStruct* ILoggerHandle;
typedef enum severity {SC_INFO, SC_DEBUG, SC_WARNING, SC_ERROR} SEVERITY;       //TODO change to unique names

/******************************************************************************
 Define interface
******************************************************************************/
typedef struct ILoggerStruct{
    SeLibGenericReferece handle;

    /**
     * Adds log messages to the buffer
     * @param logger
     * @return
     */
 void (* log)(ILoggerHandle logger, const char* msg);

} ILogger;
#endif
