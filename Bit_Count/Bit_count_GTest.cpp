#include "Bit_count.h"
#include <gtest/gtest.h>

TEST(Bit_count_GTest, positive_pow_of_two)
{
    int value = 2;

    EXPECT_EQ(set_bits(1), 1);
    EXPECT_EQ(set_bits(2), 1);
    for (uint16_t i = 0; i < max_bit_count - 2; ++i)
    {
        value <<= 1;
        EXPECT_EQ(set_bits(value), 1);
    }
}

TEST(Bit_count_GTest, negative_pow_of_two)
{
    int value = -2;

    EXPECT_EQ(set_bits(-1), max_bit_count + 1);
    EXPECT_EQ(set_bits(-2), max_bit_count);
    for (uint16_t i = max_bit_count - 1; i > 0; --i)
    {
        value <<= 1;
        EXPECT_EQ(set_bits(value), i);
    }
}

TEST(Bit_count_GTest, other_positive_value)
{
    EXPECT_EQ(set_bits(57), 4);
    EXPECT_EQ(set_bits(235674), 9);
    EXPECT_EQ(set_bits(4564), 6);
    EXPECT_EQ(set_bits(33), 2);
    EXPECT_EQ(set_bits(234534657), 16);
}

TEST(Bit_count_GTest, other_negative_value)
{
    EXPECT_EQ(set_bits(-57), 29);
    EXPECT_EQ(set_bits(-235674), 23);
    EXPECT_EQ(set_bits(-4564), 25);
    EXPECT_EQ(set_bits(-33), 31);
    EXPECT_EQ(set_bits(-234534657), 17);
}
