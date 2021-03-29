/*!*****************************************************************************
 * @file         IRunnable.h
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
 * @brief        Interface to be implemented if a runnable should be used
 *
 ******************************************************************************/

#ifndef IRUNNABLE_H_
#define IRUNNABLE_H_

#include <se-lib-c/definition/SeLibCTypes.h>
#include <stdbool.h>

/******************************************************************************
 Define interface handle data
******************************************************************************/
typedef struct IRunnableStruct* IRunnableHandle;

/******************************************************************************
 Define interface
******************************************************************************/
typedef struct IRunnableStruct{
    SeLibGenericReferece handle;

    /**
     * Runs the class which implemented the runnable
     * @param runnable
     */
    bool (* run)(IRunnableHandle runnable);

} IRunnable;

#endif
