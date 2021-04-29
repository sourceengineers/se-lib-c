/*!****************************************************************************************************************************************
 * @file         RunnableList.h
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
 *               is not valid. In this case the commercial license received with the purchase
 *               is applied (See SeScopeLicense.pdf).
 *               Please contact us at scope@sourceengineers.com for a commercial license.
 * }
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#ifndef RUNNABLELIST_H_
#define RUNNABLELIST_H_

#include <se-lib-c/util/runnable/IRunnable.h>

/**
 * Declaration of the Template handle.
 */
typedef struct RunnableList_PrivateData* RunnableList_Handle;

/**
 * Creates a RunnableList instance.
 */
RunnableList_Handle RunnableList_create(void);

/**
 * Destroys a RunnableList instance.
 */
void RunnableList_destroy(RunnableList_Handle me);

/**
 * Add a runnable to the list
 */
void RunnableList_add(RunnableList_Handle me, IRunnable*  runnable);


/**
 * Returns a pointer to the IRunnable.
 */ 
IRunnable* RunnableList_getIRunnableInterface(RunnableList_Handle me);


#endif // RUNNABLELIST_H_
