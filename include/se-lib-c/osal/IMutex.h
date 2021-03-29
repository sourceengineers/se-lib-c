/*!*****************************************************************************
 * @file         IMutex.h
 *
 * @copyright    Copyright (c) 2018 by Sourceengineers. All Rights Reserved.
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
 * @authors      Samuel Schuepbach samuel.schuepbach@sourceengineers.com
 *
 * @brief        Supplies an Interface which has to be implemented to be able to synchronise
 *               tasks. Implementing this Interface, enables to run the scope as a multi task
 *               application on various operating systems such as RTOS.
 *
 ******************************************************************************/

#ifndef IMUTEX_H
#define IMUTEX_H

#include <se-lib-c/definition/SeLibCTypes.h>
#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 Define interface handle data
******************************************************************************/
typedef struct IMutexStruct* IMutexHandle;

/******************************************************************************
 Define interface
******************************************************************************/
typedef struct IMutexStruct{
    SeLibGenericReferece handle;

    /**
     * Implement lock for the specific operating system mutex lock operation.
     * Locks the mutex
     * @param self
     * @return
     */
    bool (*lock)(IMutexHandle self, uint32_t timeout);

    /**
     * Implement unlock for the specific operating system mutex unlock operation.
     * Unlocks the mutex
     * @param self
     */
    void (*unlock)(IMutexHandle self);

} IMutex;

#endif
