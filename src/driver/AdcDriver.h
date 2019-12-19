/*!****************************************************************************************************************************************
 * @file         AdcDriver.h
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#ifndef ADCDRIVER_H_
#define ADCDRIVER_H_

#include "IAdcDriver.h"

/**
 * Declaration of the Template handle.
 */
typedef struct AdcDriver_PrivateData* AdcDriver_Handle;

/**
 * Creates a AdcDriver instance.
 */
AdcDriver_Handle AdcDriver_create(void);

/**
 * Destroys a AdcDriver instance.
 */
void AdcDriver_destroy(AdcDriver_Handle me);

/**
 * Returns a pointer to the IAdcDriver.
 */ 
IAdcDriver* AdcDriver_getIAdcDriverInterface(AdcDriver_Handle me);


#endif // ADCDRIVER_H_
