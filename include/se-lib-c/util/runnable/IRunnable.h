/*!*****************************************************************************
 * @file         IRunnable.h
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
 *               is not valid. In these cases the purchased commercial license is applied.
 *               Please contact us at scope@sourceengineers.com for a commercial license.
 * }
 *
 * @authors      Samuel Schuepbach <samuel.schuepbach@sourceengineers.com>
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
