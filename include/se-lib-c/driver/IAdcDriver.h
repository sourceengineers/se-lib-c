/*!****************************************************************************************************************************************
 * @file         IAdcDriver.h
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
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 * 
 *****************************************************************************************************************************************/

#ifndef IADCDRIVER_H_
#define IADCDRIVER_H_

#include <stdint.h>

// Declare the handle to the interface
typedef void* IAdcDriver_Handle;

// Declares the methods of the interface
typedef uint16_t (*IAdcDriver_getAdcValue)(IAdcDriver_Handle handle, uint16_t channelId);

// Declare the interface
typedef struct __IAdcDriver
{
    IAdcDriver_Handle handle;
    IAdcDriver_getAdcValue getAdcValue;
} IAdcDriver;

#endif //IADCDRIVER_H_
