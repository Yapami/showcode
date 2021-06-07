#include "Stack.h"
#include <gtest/gtest.h>

TEST(Stack, verify_push)
{
    const uint32_t stack_size = 20;
    Stack test(stack_size);

    for (uint32_t i = 0; i < stack_size / 2; ++i)
    {
        test.push(i, Id::FRONT);
        test.push(i, Id::BACK);
    }

    EXPECT_THROW(test.push(10, Id::FRONT), std::overflow_error);

    test.clear(Id::FRONT);
    test.clear(Id::BACK);

    for (uint32_t i = 0; i < stack_size; ++i)
    {
        test.push(i, Id::BACK);
    }

    EXPECT_THROW(test.push(20, Id::BACK), std::overflow_error);
}

TEST(Stack, verify_pop)
{
    const uint32_t stack_size = 20;
    Stack test(stack_size);

    for (uint32_t i = 0; i < stack_size / 2; ++i)
    {
        test.push(i, Id::FRONT);
        test.push(i, Id::BACK);
    }

    for (uint32_t i = stack_size / 2; i != 0; --i)
    {
        uint32_t value = 0;

        value = test.pop(Id::FRONT);
        EXPECT_EQ(value, i - 1);

        value = test.pop(Id::BACK);
        EXPECT_EQ(value, i - 1);
    }

    EXPECT_TRUE(test.size(Id::FRONT) == 0);
    EXPECT_TRUE(test.size(Id::BACK) == 0);

    test.push(1, Id::BACK);
    test.pop(Id::BACK);

    EXPECT_THROW(test.pop(Id::BACK), std::out_of_range);

    test.push(1, Id::FRONT);
    test.pop(Id::FRONT);

    EXPECT_THROW(test.pop(Id::FRONT), std::out_of_range);

    EXPECT_EQ(test.capacity(), stack_size);
}

TEST(Stack, verify_top)
{
    const uint32_t stack_size = 20;
    Stack test(stack_size);

    for (uint32_t i = 0; i < stack_size; ++i)
    {
        test.push(i, Id::BACK);
    }

    uint32_t top_back = test.top(Id::BACK);

    EXPECT_EQ(top_back, stack_size - 1);

    EXPECT_THROW(uint32_t top_front = test.top(Id::FRONT), std::out_of_range);
}

TEST(Stack, verify_size_and_clear)
{
    const uint32_t stack_size = 20;
    Stack test(stack_size);

    for (uint32_t i = 0; i < stack_size / 2; ++i)
    {
        test.push(i, Id::FRONT);
        test.push(i, Id::BACK);
    }

    EXPECT_EQ(test.size(Id::FRONT), stack_size / 2);
    EXPECT_EQ(test.size(Id::BACK), stack_size / 2);

    test.clear(Id::FRONT);
    test.clear(Id::BACK);

    EXPECT_EQ(test.size(Id::FRONT), 0);
    EXPECT_EQ(test.size(Id::BACK), 0);

    EXPECT_EQ(test.capacity(), stack_size);
}