/*!****************************************************************************************************************************************
 * @file         MockRunnable.h
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#ifndef MOCKRUNNABLE_H_
#define MOCKRUNNABLE_H_

#include "util/runnable/IRunnable.h"
#include <stdint.h>

/**
 * Declaration of the mock object.
 */
typedef struct __MockRunnablePrivateData
{
	IRunnable parent;
	uint16_t callCountOfRun;
} MockRunnablePrivateData;


/**
 * initialize a MockRunnable instance.
 */
void MockRunnable_init(MockRunnablePrivateData* me);

/**
 * Returns a pointer to the IRunnable.
 */ 
IRunnable* MockRunnable_getIRunnableInterface(MockRunnablePrivateData* me);


#endif // MOCKRUNNABLE_H_
