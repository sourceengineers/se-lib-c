/*!****************************************************************************************************************************************
 * @file         MinCheck.h
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @license      This file is part of SE-Lib-C.
 *
 *               SE-Lib-C is free software; you can redistribute it and/or
 *               modify it under the terms of the GNU General Public License as
 *               published by the Free Software Foundation.
 *
 *               SE-Lib-C is distributed in the hope that it will be useful,
 *               but WITHOUT ANY WARRANTY; without even the implied warranty of
 *               MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *               GNU General Public License for more details.
 *
 *               You should have received a copy of the GNU General Public License
 *               along with SE-Lib-C.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#ifndef MINCHECK_H_
#define MINCHECK_H_

#include <se-lib-c/util/checkable/ICheckable.h>
#include <se-lib-c/util/runnable/IRunnable.h>
#include <stdint.h>

/**
 * Declaration of the Template handle.
 */
typedef struct MinCheck_PrivateData* MinCheck_Handle;

/**
 * Creates a MinCheck instance.
 */
MinCheck_Handle MinCheck_create(float* valueToCheck, float tripLimit, uint16_t tripTimeMs, uint16_t callIntvervallMs);

/**
 * Destroys a MinCheck instance.
 */
void MinCheck_destroy(MinCheck_Handle me);

/**
 * Returns a pointer to the ICheckable.
 */ 
ICheckable* MinCheck_getICheckableInterface(MinCheck_Handle me);

/**
 * Returns a pointer to the IRunnable.
 */
IRunnable* MinCheck_getIRunnableInterface(MinCheck_Handle me);


#endif // MinCheck_H_
