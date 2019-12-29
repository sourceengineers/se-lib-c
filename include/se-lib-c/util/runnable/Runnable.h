/*!****************************************************************************************************************************************
 * @file         Runnable.h
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#ifndef RUNNABLE_H_
#define RUNNABLE_H_

#include "IRunnable.h"
#include <stdint.h>

/**
 * Declaration of the Template handle.
 */
typedef struct Runnable_PrivateData* Runnable_Handle;

/**
 * Creates a Runnable instance.
 */
Runnable_Handle Runnable_create(void);

/**
 * Destroys a Runnable instance.
 */
void Runnable_destroy(Runnable_Handle me);

/**
 * get the call count of run
 */
 uint16_t Runnable_getCallCountOfRun(Runnable_Handle me);

/**
 * Returns a pointer to the IRunnable.
 */ 
IRunnable* Runnable_getIRunnableInterface(Runnable_Handle me);


#endif // RUNNABLE_H_
