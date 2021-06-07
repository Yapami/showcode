#pragma once

#include <algorithm>
#include <random>
#include <vector>

const double numb_possible_values = 6 * 6;
const uint32_t numb_of_possible_sum = 11;

std::vector<uint32_t> all_sum();
void calculate(int &biggest_probability_sum, double &probability);
uint32_t random_sum();
double practice_probability(uint32_t numb_of_iter, uint32_t expected_value);
