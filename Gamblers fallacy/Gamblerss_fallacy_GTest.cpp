#include "Gamblerss_fallacy.h"
#include <gtest/gtest.h>

TEST(Gamblerss_fallacy, show)
{
    uint32_t numb_of_true = 5;

    EXPECT_NEAR(necessary_iterations_form(numb_of_true),
                necessary_iterations_experiment(numb_of_true),
                round(necessary_iterations_form(numb_of_true) * 0.1));
}
