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
 *               This module will take up
 *               (maxPriorities * maxItemsPerPriority + maxPriorities) of space
 *
 ******************************************************************************/

#ifndef AGINGPRIORITYQUEUE_H_
#define AGINGPRIORITYQUEUE_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 Define class handle data
******************************************************************************/
typedef struct __AgingPriorityQueuePrivateData* AgingPriorityQueueHandle;

/******************************************************************************
 Public functions
******************************************************************************/

/**
 * Create the aging priority queue
 * @param maxPriorities Max number of priorities (highest number is lowest priority)
 * @param maxItemsPerPriority Max items that will be saved in the queue per priority
 * @param oldestAge The oldest age of a priority before its priority gets elevated
 * @return
 */
AgingPriorityQueueHandle AgingPriorityQueue_create(uint32_t maxPriorities, uint32_t maxItemsPerPriority,
                                                   uint32_t oldestAge);
/**
 * Pushes a new item into the priority queue.
 * @param self
 * @param item
 * @param priority Note, lower number is higher priority
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
 * Check if the given item is already present in the priority queue. Returns true if already present
 * @param self
 * @param item
 * @return
 */
bool AgingPriorityQueue_contains(AgingPriorityQueueHandle self, uint32_t item);

/**
 * Checks if the queue is empty and no items are pending. Returns true if the queue is empty
 * @param self
 * @return
 */
bool AgingPriorityQueue_empty(AgingPriorityQueueHandle self);

/**
 * Deconstructor
 * @param self
 */
void AgingPriorityQueue_destroy(AgingPriorityQueueHandle self);

#endif
