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
 *               is not valid. In these cases the purchased commercial license is applied.
 *               Please contact us at scope@sourceengineers.com for a commercial license.
 * }
 *
 * @authors      Samuel Schuepbach <samuel.schuepbach@sourceengineers.com>
 *
 * @brief        Implementation of a priority queue with an aging mechanism to prevent starvation
 *               See: https://en.wikipedia.org/wiki/Aging_(scheduling)
 *               This module will take up
 *               (maxPriorities * maxItemsPerPriority + maxPriorities) of space
 ******************************************************************************/

#include <se-lib-c/algorithm/AgingPriorityQueue.h>
#include <se-lib-c/container/IntRingBuffer.h>
#include <stdlib.h>
#include <assert.h>

/******************************************************************************
 Define private data
******************************************************************************/
/* Class data */
typedef struct __AgingPriorityQueuePrivateData{
    IntRingBufferHandle* queues;
    uint32_t maxPriorities;
    uint32_t* ages;
    uint32_t oldestAge;
    uint32_t* anySearchBuffer;
} AgingPriorityQueuePrivateData;

static void updateAgePastPriority(AgingPriorityQueueHandle self, uint32_t updatePast);

static int increasePriority(IntRingBufferHandle higherPriority, IntRingBufferHandle lowerPriority);

/******************************************************************************
 Private functions
******************************************************************************/

static int increasePriority(IntRingBufferHandle higherPriority, IntRingBufferHandle lowerPriority) {

    size_t numberOfItems = IntRingBuffer_getNumberOfUsedData(lowerPriority);
    size_t numberOfItemsThatFit = IntRingBuffer_getNumberOfFreeData(higherPriority);

    // Make sure that all the items are going to fit, so that we are not going to loose data
    if (numberOfItemsThatFit < numberOfItems) {
        numberOfItems = numberOfItemsThatFit;
    }

    for (int i = 0; i < numberOfItems; ++i) {

        uint32_t item;

        if (IntRingBuffer_read(lowerPriority, &item, 1) < 0) {
            // If we couldn't read anymore for some reason, abort
            return -1;
        }

        if (IntRingBuffer_write(higherPriority, &item, 1) < 0) {
            // If we couldn't fit the data for what ever reason, put it back into the original
            IntRingBuffer_write(lowerPriority, &item, 1);
        }
    }

    return 0;
}

static void updateAgePastPriority(AgingPriorityQueueHandle self, uint32_t updatePast) {

    // Don't update if the last priority got poped
    if (updatePast >= (self->maxPriorities - 1)) {
        return;
    }

    // Start checking if the priorities must be raised
    for (size_t i = updatePast; i < (self->maxPriorities - 2); ++i) {
        self->ages[i] += 1;

        if (self->ages[i] >= self->oldestAge) {
            increasePriority(self->queues[i], self->queues[i + 1]);
            // Reset the age
            self->ages[i] = 0;
        }
    }
}


/******************************************************************************
 Public functions
******************************************************************************/
AgingPriorityQueueHandle AgingPriorityQueue_create(uint32_t maxPriorities, uint32_t maxItemsPerPriority,
                                                   uint32_t oldestAge) {

    // There have to be at least two priorities
    assert(maxPriorities > 1);

    /* Allocate memory and set _private variables */
    AgingPriorityQueueHandle self = malloc(sizeof(AgingPriorityQueuePrivateData));
    assert(self);

    self->queues = malloc(sizeof(IntRingBufferHandle) * maxPriorities);
    assert(self->queues);

    // The highest priority cannot age since it is already at the max priority.
    // Therefor one less age than priority is required
    self->ages = malloc(sizeof(uint32_t) * (maxPriorities - 1));
    assert(self->ages);

    self->anySearchBuffer = malloc(sizeof(uint32_t) * (maxItemsPerPriority));
    assert(self->anySearchBuffer);

    for (size_t i = 0; i < maxPriorities; ++i) {
        self->queues[i] = IntRingBuffer_create(maxItemsPerPriority);
        assert(self->queues[i]);
        self->ages[i] = 0;
    }

    self->oldestAge = oldestAge;
    self->maxPriorities = maxPriorities;

    return self;
}

bool AgingPriorityQueue_contains(AgingPriorityQueueHandle self, uint32_t item) {
    for (size_t i = 0; i < self->maxPriorities; ++i) {
        size_t elements = IntRingBuffer_getNumberOfUsedData(self->queues[i]);
        IntRingBuffer_readNoPosInc(self->queues[i], self->anySearchBuffer, elements);
        for (int j = 0; j < elements; ++j) {
            if (self->anySearchBuffer[j] == item) {
                return true;
            }
        }
    }

    return false;
}

int AgingPriorityQueue_push(AgingPriorityQueueHandle self, uint32_t item, uint32_t priority) {
    if (priority >= self->maxPriorities) {
        return -1;
    }

    return IntRingBuffer_write(self->queues[priority], &item, 1);
}

bool AgingPriorityQueue_empty(AgingPriorityQueueHandle self) {

    for (int i = 0; i < self->maxPriorities; ++i) {
        if (IntRingBuffer_getNumberOfUsedData(self->queues[i]) != 0) {
            return false;
        }
    }

    return true;
}

int AgingPriorityQueue_pop(AgingPriorityQueueHandle self, uint32_t* item) {

    uint32_t tmpItem = 0;
    bool itemFound = false;
    size_t priority = 0;

    for (; priority < self->maxPriorities; ++priority) {
        if(IntRingBuffer_getNumberOfUsedData(self->queues[priority]) > 0) {
            if (IntRingBuffer_read(self->queues[priority], &tmpItem, 1) < 0) {
                return -1;
            }
            itemFound = true;
            break;
        }
    }

    // Abort if not item is found. This means that the queue is empty
    if (!itemFound) {
        return -1;
    }

    updateAgePastPriority(self, priority);

    // Update the item
    *item = tmpItem;

    return 0;
}

void AgingPriorityQueue_destroy(AgingPriorityQueueHandle self) {

    free(self->ages);

    for (size_t i = 0; i < self->maxPriorities; ++i) {
        IntRingBuffer_destroy(self->queues[i]);
    }

    free(self->queues);
}
