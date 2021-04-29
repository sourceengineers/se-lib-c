#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <se-lib-c/algorithm/AgingPriorityQueue.h>
}


class TestAgingPriorityQueue : public ::testing::Test {
protected:
    TestAgingPriorityQueue()
            : Test() {
    }

    void SetUp() override {
        _priorityQueue = AgingPriorityQueue_create(5, 5, 3);
    }

    void TearDown() override {
    }

    virtual ~TestAgingPriorityQueue() {
    }

    AgingPriorityQueueHandle _priorityQueue;

};

TEST_F(TestAgingPriorityQueue, OrdinaryOperation) {

    int ret = AgingPriorityQueue_push(_priorityQueue, 1, 3);
    EXPECT_NE(-1, ret);

    ret = AgingPriorityQueue_push(_priorityQueue, 2, 4);
    EXPECT_NE(-1, ret);

    ret = AgingPriorityQueue_push(_priorityQueue, 3, 2);
    EXPECT_NE(-1, ret);

    ret = AgingPriorityQueue_push(_priorityQueue, 4, 1);
    EXPECT_NE(-1, ret);


    uint32_t item;
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(4, item);
    EXPECT_NE(-1, ret);

    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(3, item);
    EXPECT_NE(-1, ret);

    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(1, item);
    EXPECT_NE(-1, ret);

    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(2, item);
    EXPECT_NE(-1, ret);

    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(-1, ret);
}

TEST_F(TestAgingPriorityQueue, OrdinaryOperationButMoreDifficult)
{

    int ret = AgingPriorityQueue_push(_priorityQueue, 1, 0);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 10, 3);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 13, 4);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 2, 0);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 7, 2);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 4, 1);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 8, 2);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 3, 0);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 5, 1);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 6, 1);
    EXPECT_NE(-1, ret);

    uint32_t item;

    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(1, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(2, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(3, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(4, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(5, item);
    EXPECT_NE(-1, ret);

    ret = AgingPriorityQueue_push(_priorityQueue, 11, 3);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 12, 3);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 14, 4);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 15, 4);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 9, 2);
    EXPECT_NE(-1, ret);

    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(6, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(7, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(8, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    // There's a aging occuring, so flipp 10/9
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(9, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(11, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(12, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(13, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(14, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(15, item);
    EXPECT_NE(-1, ret);
}

TEST_F(TestAgingPriorityQueue, Aging) {

    int ret = AgingPriorityQueue_push(_priorityQueue, 1, 0);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 1, 0);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 1, 0);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 1, 0);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 1, 0);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 2, 1);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_push(_priorityQueue, 2, 1);
    EXPECT_NE(-1, ret);

    uint32_t item;

    // After poping three times, we expect the priority of prio 1 elements to be raise
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(1, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(1, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(1, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(1, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(1, item);
    EXPECT_NE(-1, ret);

    // To check that the prio of the 1's has actually been elevated, append one 0 and check that the 1's come first
    ret = AgingPriorityQueue_push(_priorityQueue, 1, 0);
    EXPECT_NE(-1, ret);

    // Now we get our prio ones
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(2, item);
    EXPECT_NE(-1, ret);
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(2, item);
    EXPECT_NE(-1, ret);

    // And the prio 0 that was only appended later
    ret = AgingPriorityQueue_pop(_priorityQueue, &item);
    EXPECT_EQ(1, item);
    EXPECT_NE(-1, ret);






}
