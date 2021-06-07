#include "two_dice.h"
#include <iostream>

int main()
{
    int a;
    double b;
    calculate(a ,b);
    double c = practice_probability(10000, a);
    std::cout << b << "\t" << c << std::endl;
    return 0;
}
