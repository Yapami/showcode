#include "Bit_count.h"

unsigned short set_bits(const int value)
{
    unsigned short result = 0;
    for (int i = max_bit_count; i >= 0; --i)
    {
        if (value & (1 << i))
        {
            ++result;
        }
    }
    return result;
}
