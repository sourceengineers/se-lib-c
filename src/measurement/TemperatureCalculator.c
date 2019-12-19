/*!****************************************************************************************************************************************
 * @file         TemperatureCalculator.c
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 *****************************************************************************************************************************************/

#include "TemperatureCalculator.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct TemperatureCalculator_PrivateData {
    IRunnable parent;
    IAdcDriver *adcDriver;
    float *resultingTemperature;
    uint16_t adcChannelId;
}PrivateData;

static void run(IRunnable_Handle handle)
{
    PrivateData* me = (PrivateData*)handle;
    assert(me != NULL);

    // get value from ADC
    uint16_t newAdcValue = me->adcDriver->getAdcValue(me->adcDriver->handle,5);

    // scale value
    // TODO use real NTC coefficient formual
    *me->resultingTemperature =  (newAdcValue * 5 - 3);
}

TemperatureCalculator_Handle TemperatureCalculator_create(
        IAdcDriver* adcDriver,
        float* resultingTemperature,
        uint16_t adcChannelId)
{
    PrivateData* me = malloc(sizeof(PrivateData));
    assert(me != NULL);

    // initialize runnable
    me->parent.handle = me;
    me->parent.run = &run;

    // initialize private variables
    me->adcDriver = adcDriver;
    me->resultingTemperature = resultingTemperature;
    me->adcChannelId = adcChannelId;

    return me;
}

IRunnable* TemperatureCalculator_getIRunnableInterface(TemperatureCalculator_Handle me)
{
    return &me->parent;
}

void TemperatureCalculator_destroy(TemperatureCalculator_Handle me)
{
    free(me);
}
