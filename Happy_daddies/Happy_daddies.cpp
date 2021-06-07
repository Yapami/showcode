#include "Happy_daddies.h"

double ratio_form(unsigned int numb_of_fam)
{
    double girls = 0;
    unsigned int pow = 2;
    while (round((double)numb_of_fam / (double)pow) > 0.1)
    {
        girls += 1. / (double)pow * (double)numb_of_fam;
        pow <<= 1;
    }

    return (double)numb_of_fam / girls;
}

double ratio_practice(unsigned int numb_of_fam)
{
    std::random_device rd;
    std::mt19937 mersenne(rd());

    uint32_t girls = 0;

    for (uint32_t i = 0; i < numb_of_fam; i++)
    {
        bool human;
        do
        {
            human = rd() % 2;
            if (human)
            {
                break;
            }
            else
            {
                ++girls;
            }

        } while (!human);

    }
    return (double)numb_of_fam / girls;
}
