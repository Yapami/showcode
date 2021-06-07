#include "Word_pack.h"
#include <random>

std::string random_word()
{
    std::string word;
    std::random_device rd;
    std::mt19937 mersenne(rd());

    for (uint32_t i = 0; i < 6; ++i)
    {
        word += rd() % 26 + 'a';
    }
    return word;
}

uint32_t word_pack(const std::string &word)
{
    uint32_t result = 0;

    for (uint32_t i = 0; i < word.size(); ++i)
    {
        result |= static_cast<uint32_t>(word[i] - 'a') << (i * 5);
    }
    return result;
}

std::string word_unpack(uint32_t value)
{
    std::string result;

    for (size_t i = 0; i < 6; ++i)
    {
        result += (static_cast<char>((value >> (i * 5)) & 0b11111) + 'a');
    }
    return result;
}
