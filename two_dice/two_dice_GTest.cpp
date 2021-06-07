#include "two_dice.h" 
#include <gtest/gtest.h> 

TEST(two_dice, probability)
{
    int value;
    double probability;
    calculate(value, probability);

    EXPECT_NEAR(practice_probability(1000000, value), probability, 0.001);
}

