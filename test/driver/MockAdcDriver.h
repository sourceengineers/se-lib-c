/*!****************************************************************************************************************************************
 * @file         MockAdcDriver.h
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#ifndef MOCKADCDRIVER_H_
#define MOCKADCDRIVER_H_

#include "driver/IAdcDriver.h"
#include <stdint.h>

#define NUMBER_OF_ADC_CHANNELS 6
/**
 * Declaration of the mock object.
 */
typedef struct __MockAdcDriverPrivateData
{
	IAdcDriver parent;
	uint16_t analogValue[NUMBER_OF_ADC_CHANNELS];
} MockAdcDriverPrivateData;


/**
 * initialize a MockAdcDriver instance.
 */
void MockAdcDriver_init(MockAdcDriverPrivateData* me);

/**
 * Returns a pointer to the IAdcDriver.
 */ 
IAdcDriver* MockAdcDriver_getIAdcDriverInterface(MockAdcDriverPrivateData* me);


#endif // MOCKADCDRIVER_H_
