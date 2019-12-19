/*!****************************************************************************************************************************************
 * @file         MockAdcDriver.c
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/
#include "MockAdcDriver.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


/**
 * The implementation of the Parent methods.
 * @{
 */
static uint16_t getAdcValue(IAdcDriver_Handle handle, uint16_t channelId);
/** @} */


void MockAdcDriver_init(MockAdcDriverPrivateData* me)
{
    // initialize interface
    me->parent.handle = me;
    me->parent.getAdcValue = &getAdcValue;

    // initialize private variables
    memset(me->analogValue,0,sizeof(uint16_t)*NUMBER_OF_ADC_CHANNELS);
}

IAdcDriver* MockAdcDriver_getIAdcDriverInterface(MockAdcDriverPrivateData* me)
{
    assert(me != NULL);
    return &me->parent;
}


static uint16_t getAdcValue(IAdcDriver_Handle handle, uint16_t channelId)
{
    MockAdcDriverPrivateData* me = (MockAdcDriverPrivateData*)handle;
    assert(me != NULL);

    assert(channelId < NUMBER_OF_ADC_CHANNELS);
    return me->analogValue[channelId];
}
