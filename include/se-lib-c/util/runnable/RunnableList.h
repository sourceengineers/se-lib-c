/*!****************************************************************************************************************************************
 * @file         RunnableList.h
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
