#include "Buffer.h"
#include <gtest/gtest.h>

TEST(Buffer, capacity_and_size)
{
    const uint32_t elements_amount = 55;
    const uint32_t buffer_size = 20;
    Buffer test(buffer_size);

    for (uint32_t i = 0; i < elements_amount; ++i)
    {
        test.add_element(i);
    }

    EXPECT_EQ(test.capacity(), buffer_size);
    EXPECT_EQ(test.size(), elements_amount % buffer_size);
}

TEST(Buffer, correct_work)
{
    const uint32_t elements_amount = 55;
    const uint32_t buffer_size = 20;
    Buffer test(buffer_size);
    Buffer expected_values(buffer_size);

    for (uint32_t i = 0; i < elements_amount; ++i)
    {
        test.add_element(i);
        if (i >= (elements_amount - (elements_amount % buffer_size)))
        {
            expected_values.add_element(i);
        }
    }

    EXPECT_TRUE(equal(test.begin(), test.end(), expected_values.begin(), expected_values.end()));
}
