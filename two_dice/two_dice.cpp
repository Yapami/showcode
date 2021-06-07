#include "two_dice.h" 


std::vector<uint32_t> all_sum()
{
    std::vector<uint32_t> numb_of_each_sum(numb_of_possible_sum, 0);

    for (uint32_t i = 0; i < 6; i++)
    {
        for (uint32_t j = 0; j < 6; j++)
        {
            ++numb_of_each_sum[i + j];
        }
    }
    return numb_of_each_sum;
}

void calculate(int& biggest_probability_sum, double& probability)
{
    biggest_probability_sum = probability = 0;

    std::vector<uint32_t> numb_of_each_sum = all_sum();

    double max_amount_of_sum = *(std::max_element(numb_of_each_sum.begin(), numb_of_each_sum.end()));
   
    for (uint32_t i = 0; i < numb_of_possible_sum; i++)
    {
        if (numb_of_each_sum[i]>biggest_probability_sum)
        {
            biggest_probability_sum = i;
        }
    }
    biggest_probability_sum += 2;
    
    probability = max_amount_of_sum / numb_possible_values;
}

uint32_t random_sum()
{
    std::random_device rd;
    std::mt19937 mersenne(rd());
    uint32_t temp = ((rd() % 6) + 1) + ((rd() % 6) + 1);
    return temp;
}

double practice_probability(uint32_t numb_of_iter, uint32_t expected_value)
{
    uint32_t frequency = 0;
    for (uint32_t i = 0; i < numb_of_iter; ++i)
    {
        if (random_sum() == expected_value)
        {
            ++frequency;
        }
    }
    return (double)frequency/numb_of_iter;
}
