#include "Happy_daddies.h"
#include <gtest/gtest.h>

TEST(Happy_daddies, form)
{
    uint32_t numb_of_fam = 5;
    EXPECT_EQ(round(ratio_form(numb_of_fam)), 1);
}

TEST(Happy_daddies, comparison)
{
    uint32_t numb_of_fam = 10000;

    EXPECT_NEAR(ratio_form(numb_of_fam), ratio_practice(numb_of_fam), 0.1);
}