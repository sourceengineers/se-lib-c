/*!****************************************************************************************************************************************
 * @file         AdcDriver.c
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        Config-header fro AdcDriver
 *
 *****************************************************************************************************************************************/
#include "AdcDriver.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <driver/AdcDriverConfig.h>

typedef struct AdcDriver_PrivateData
{
	IAdcDriver parent;
} PrivateData;


/**
 * The implementation of the Parent methods.
 * @{
 */
static uint16_t getAdcValue(IAdcDriver_Handle handle, uint16_t channelId);
/** @} */


AdcDriver_Handle AdcDriver_create(void)
{
    PrivateData* me = malloc(sizeof(PrivateData));
    assert(me != NULL);

    // initialize interface
    me->parent.handle = me;
    me->parent.getAdcValue = &getAdcValue;

    return me;
}

void AdcDriver_destroy(AdcDriver_Handle me)
{
    free(me);
}


IAdcDriver* AdcDriver_getIAdcDriverInterface(AdcDriver_Handle me)
{
    assert(me != NULL);
    return &me->parent;
}


static uint16_t getAdcValue(IAdcDriver_Handle handle, uint16_t channelId)
{
    PrivateData* me = (PrivateData*)handle;
    assert(me != NULL);

    return ADC_RESULT(channelId);
}
