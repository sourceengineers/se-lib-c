/*!****************************************************************************************************************************************
 * @file         ICheckable.h
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 * 
 *****************************************************************************************************************************************/

#ifndef ICHECKABLE_H_
#define ICHECKABLE_H_

#include <stdbool.h>

// Declare the handle to the interface
typedef void* ICheckable_Handle;

// Declares the methods of the interface
typedef void (*ICheckable_setActive)(ICheckable_Handle handle, bool isActive);
typedef bool (*ICheckable_isCheckOk)(ICheckable_Handle handle);

// Declare the interface
typedef struct __ICheckable
{
    ICheckable_Handle handle;
    ICheckable_setActive setActive;
    ICheckable_isCheckOk isCheckOk;
} ICheckable;

#endif //ICHECKABLE_H_
