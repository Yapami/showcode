#include "Gamblerss_fallacy.h"

std::random_device rd;
std::mt19937 mersenne(rd());

unsigned int necessary_iterations_form(unsigned int numb_of_true)
{
    return pow(2, numb_of_true);
}

unsigned int necessary_iterations_experiment(unsigned int numb_of_true)
{
    uint32_t temp = 0;
    uint32_t iter = 1;
    uint32_t expected = rd() % 2;

    for (;temp < numb_of_true; ++iter)
    {
        uint32_t coin = rd() % 2;
        if (coin == expected)
        {
            ++temp;
        }
        else
        {
            temp = 1;
        }
        expected = coin;
    }
    return iter;
}
