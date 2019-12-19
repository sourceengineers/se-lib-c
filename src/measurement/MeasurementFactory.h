/*!****************************************************************************************************************************************
 * @file         MeasurementFactory.h
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#ifndef MEASUREMENTFACTORY_H_
#define MEASUREMENTFACTORY_H_

#include <util/runnable/IRunnable.h>
#include <driver/IAdcDriver.h>
#include "MeasuredValues.h"

/**
 * Initializes the MeasurementFactory instance.
 */
void MeasurementFactory_initialize(IAdcDriver* adcDriver);

/**
 * Get the runnable to run "measurement"
 */
IRunnable* MeasurementFactory_getRunnable(void);

/**
 * Get the measured values object
 * @note the const ensures that the values are read-only
 */
const MeasuredValues * MeasurementFactory_getMeasuredValuesSharedObject(void);


/**
 * Destroys a MeasurementFactory instance.
 */
void MeasurementFactory_destroy(void);


#endif // MEASUREMENTFACTORY_H_
