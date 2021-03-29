/*!****************************************************************************************************************************************
 * @file         ICheckable.h
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

#ifndef ICHECKABLE_H_
#define ICHECKABLE_H_

#include <se-lib-c/definition/SeLibCTypes.h>
#include <stdbool.h>

// Declare the handle to the interface
typedef struct __ICheckable* ICheckableHandle;

// Declares the methods of the interface
typedef void (*ICheckable_setActive)(ICheckableHandle handle, bool isActive);
typedef bool (*ICheckable_isCheckOk)(ICheckableHandle handle);

// Declare the interface
typedef struct __ICheckable
{
    SeLibGenericReferece handle;
    ICheckable_setActive setActive;
    ICheckable_isCheckOk isCheckOk;
} ICheckable;

#endif //ICHECKABLE_H_
