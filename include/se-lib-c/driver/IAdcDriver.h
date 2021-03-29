/*!****************************************************************************************************************************************
 * @file         IAdcDriver.h
 *
 * @copyright    © by Source Engineers GmbH, 2019
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
