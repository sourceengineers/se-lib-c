/*!****************************************************************************************************************************************
 * @file         TemperatureCalculator.h
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#ifndef TEMPERATURECALCULATOR_H_
#define TEMPERATURECALCULATOR_H_

#include <driver/IAdcDriver.h>
#include <util/runnable/IRunnable.h>

/**
 * Declaration of the TemperatureCalculator handle.
 */
typedef struct TemperatureCalculator_PrivateData* TemperatureCalculator_Handle;

/**
 * Creates a TemperatureCalculator instance.
 */
TemperatureCalculator_Handle TemperatureCalculator_create(
        IAdcDriver* adcDriver,
        float* resultingTemperature,
        uint16_t adcChannelId);

/**
 * Get the runnable interface
 */
IRunnable* TemperatureCalculator_getIRunnableInterface(TemperatureCalculator_Handle me);

/**
 * Destroys a TemperatureCalculator instance.
 */
void TemperatureCalculator_destroy(TemperatureCalculator_Handle me);

#endif // TEMPERATURECALCULATOR_H_
