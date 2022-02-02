/*!****************************************************************************************************************************************
 * @file         MinCheck.h
 *
 * @copyright    Copyright (c) 2021 by Source Engineers GmbH. All Rights Reserved.
 *
 * @license {    This file is part of se-lib-c.
 *
 *               se-lib-c is free software; you can redistribute it and/or
 *               modify it under the terms of the GPLv3 General Public License Version 3
 *               as published by the Free Software Foundation.
 *
 *               se-lib-c is distributed in the hope that it will be useful,
 *               but WITHOUT ANY WARRANTY; without even the implied warranty of
 *               MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *               GNU General Public License for more details.
 *
 *               You should have received a copy of the GPLv3 General Public License Version 3
 *               along with se-lib-c.  If not, see <http://www.gnu.org/licenses/>.
 *
 *               In closed source or commercial projects, GPLv3 General Public License Version 3
 *               is not valid. In these cases the purchased commercial license is applied.
 *               Please contact us at scope@sourceengineers.com for a commercial license.
 * }
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
