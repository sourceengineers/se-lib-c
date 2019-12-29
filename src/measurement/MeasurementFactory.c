/*!****************************************************************************************************************************************
 * @file         MeasurementFactory.c
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 *****************************************************************************************************************************************/

#include "MeasurementFactory.h"
#include <se-lib-c/util/runnable/RunnableList.h>
#include "TemperatureCalculator.h"
#include "MeasuredValues.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct MeasurementFactory_PrivateData
{
	RunnableList_Handle  runnables;
    TemperatureCalculator_Handle ambientTemperature;
    TemperatureCalculator_Handle igbtTemperature1;
    TemperatureCalculator_Handle igbtTemperature2;
    TemperatureCalculator_Handle cpuTemperature;
    MeasuredValues measuredValues;
    bool isInitialized;
} PrivateData;

// factories are mostly singletons
static PrivateData me = {NULL,NULL,NULL,NULL,NULL,{0},false};

void MeasurementFactory_initialize(IAdcDriver* adcDriver)
{
    me.runnables = RunnableList_create();
    assert(me.runnables);

    me.ambientTemperature = TemperatureCalculator_create(adcDriver,&me.measuredValues.ambientTemperature,5);
    assert(me.ambientTemperature);
    RunnableList_add(me.runnables,TemperatureCalculator_getIRunnableInterface(me.ambientTemperature));

    me.igbtTemperature1 = TemperatureCalculator_create(adcDriver,&me.measuredValues.igbtTemperature1,4);
    assert(me.igbtTemperature1);
    RunnableList_add(me.runnables,TemperatureCalculator_getIRunnableInterface(me.igbtTemperature1));

    me.igbtTemperature2 = TemperatureCalculator_create(adcDriver,&me.measuredValues.igbtTemperature2,3);
    assert(me.igbtTemperature2);
    RunnableList_add(me.runnables,TemperatureCalculator_getIRunnableInterface(me.igbtTemperature2));

    me.cpuTemperature = TemperatureCalculator_create(adcDriver,&me.measuredValues.cpuTemperature,2);
    assert(me.cpuTemperature);
    RunnableList_add(me.runnables,TemperatureCalculator_getIRunnableInterface(me.cpuTemperature));

    me.isInitialized = true;
}

IRunnable* MeasurementFactory_getRunnable(void)
{
    assert(me.runnables);
    assert(me.isInitialized);
    return RunnableList_getIRunnableInterface(me.runnables);
}

const MeasuredValues * MeasurementFactory_getMeasuredValuesSharedObject(void)
{
    assert(me.isInitialized);
    return &me.measuredValues;
}

void MeasurementFactory_destroy()
{
    TemperatureCalculator_destroy(me.ambientTemperature);
    TemperatureCalculator_destroy(me.igbtTemperature1);
    TemperatureCalculator_destroy(me.igbtTemperature2);
    TemperatureCalculator_destroy(me.cpuTemperature);
    RunnableList_destroy(me.runnables);
}
