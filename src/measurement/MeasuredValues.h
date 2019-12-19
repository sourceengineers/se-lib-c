/*!****************************************************************************************************************************************
 * @file         MeasuredValues.h
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#ifndef MEASUREDVALUES_H_
#define MEASUREDVALUES_H_
#include <float.h>

typedef struct __MeasuredValues
{
    float igbtTemperature1;
    float igbtTemperature2;
    float cpuTemperature;
    float ambientTemperature;
}MeasuredValues;


#endif // MEASUREDVALUES_H_
