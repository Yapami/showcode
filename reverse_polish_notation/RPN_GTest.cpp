#include "RPN.h" 
#include <gtest/gtest.h> 

TEST(RPT, toRPN)
{
    const std::string str = "(900*  -    0.3^(    2V 4)+4)/5";
    const std::string result = "900 0 0.3 - 2 4 V ^ * 4 + 5 / ";
    EXPECT_EQ(toRPN(str), result);
}

TEST(RPT, colculate)
{
    const std::string str = "(900*  -    0.3^(    2V 4)+4)/5";
    EXPECT_EQ(colculate(toRPN(str)), 17);
}
