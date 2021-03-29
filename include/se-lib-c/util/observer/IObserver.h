/*!*****************************************************************************
 * @file         IObserver.h
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
 * @brief        Interface to implement the Observer design pattern
 *
 ******************************************************************************/

#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <se-lib-c/definition/SeLibCTypes.h>

/******************************************************************************
 Define interface handle data
******************************************************************************/
typedef struct IObserverStruct* IObserverHandle;

/******************************************************************************
 Define interface
******************************************************************************/
typedef struct IObserverStruct{
    SeLibGenericReferece handle;

    /**
     * Calls an update on the class which implemented the observer
     * @param runnable
     * @param state
     */
    void (* update)(IObserverHandle runnable, void* state);

} IObserver;
#endif
