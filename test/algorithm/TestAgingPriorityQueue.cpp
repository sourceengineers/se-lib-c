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

TEST_F(TestAgingPriorityQueue, Aging)
{

}