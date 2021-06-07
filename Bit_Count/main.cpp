#include "Bit_count.h"
#include <iostream>

int main()
{
    int value = 0;

    std::cout << "Enter the number: ";
    std::cin >> value;

    std::cout << "The number of set bits is " << set_bits(value) << std::endl;

    return 0;
}
