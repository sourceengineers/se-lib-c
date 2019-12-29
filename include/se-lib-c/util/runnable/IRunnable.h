/*!****************************************************************************************************************************************
 * @file         IRunnable.h
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 * 
 *****************************************************************************************************************************************/

#ifndef IRUNNABLE_H_
#define IRUNNABLE_H_

// Declare the handle to the interface (void* because type of derived class is not known)
typedef void* IRunnable_Handle;

// Declares the methods of the interface
typedef void (*IRunnable_run)(IRunnable_Handle handle);

// Declare the interface
typedef struct __IRunnable
{
    IRunnable_Handle handle;       // the explicit 'this' pointer
    IRunnable_run run; // pointer to function implementation
} IRunnable;

#endif //IRUNNABLE_H_
