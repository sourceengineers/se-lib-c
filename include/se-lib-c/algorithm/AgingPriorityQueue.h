/*!*****************************************************************************
 * @file         AgingPriorityQueue.h
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
 * @authors      Samuel Schuepbach <samuel.schuepbach@sourceengineers.com>
 *
 * @brief        Implementation of a priority queue with an aging mechanism to prevent starvation
 *               See: https://en.wikipedia.org/wiki/Aging_(scheduling)
 *
 *               Note: Perhaps this makes sense to implement: https://gitlab.com/hansonry/guide-to-ursa-major/-/blob/master/backend/common/Queue.h
 *
 ******************************************************************************/

#ifndef AGINGPRIORITYQUEUE_H_
#define AGINGPRIORITYQUEUE_H_

#include <stddef.h>
#include <stdint.h>

/******************************************************************************
 Define class handle data
******************************************************************************/
typedef struct __AgingPriorityQueuePrivateData* AgingPriorityQueueHandle;

/******************************************************************************
 Public functions
******************************************************************************/
/**
 * Constructor
 * @param capacity
 * @return
 */
AgingPriorityQueueHandle AgingPriorityQueue_create(uint32_t maxPriorities, uint32_t maxItemsPerPriority,
                                                   uint32_t oldestAge);

/**
 * Pushes a new item into the priority queue.
 * @param self
 * @param item
 * @param priority
 * @return -1 when the queue is full or the priority > maxPriorities. 1 is returned on success
 */
int AgingPriorityQueue_push(AgingPriorityQueueHandle self, uint32_t item, uint32_t priority);

/**
 *
 * @param self
 * @return
 */
int AgingPriorityQueue_pop(AgingPriorityQueueHandle self, uint32_t* item);

/**
 * Deconstructor
 * @param self
 */
void AgingPriorityQueue_destroy(AgingPriorityQueueHandle self);

#endif
