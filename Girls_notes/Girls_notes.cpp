#include "Girls_notes.h" 

std::string random_word(const uint32_t size)
{
    std::string result;
    std::random_device rd;
    std::mt19937 mersenne(rd());
    char symb = 0;

    for (uint32_t i = 0; i < size; ++i)
    {
        symb = rd()%27;
        symb ? symb += 'a' - 1 : symb = ' ';
        result.push_back(symb);
    }

    return result;
}

char generate_random_key()
{
    char key;
    std::random_device rd;
    std::mt19937 mersenne(rd());

    key = rd() % 256;

    return key;
}

std::string apply_key(const std::string &word, const char key)
{
    std::string result = word;

    for (uint32_t i = 0; i < result.size(); ++i)
    {
        result[i] ^= key;
    }

    return result;
}

bool verify_string(const std::string &str)
{
    for (uint32_t i = 0; i < str.size(); ++i)
    {
        if (!(islower(str[i]) || str[i] == ' '))
        {
            return false;
        }
    }

    return true;
}

std::vector<std::string> decrypt_possible_words(const std::string &word)
{
    std::vector<std::string> result;
    std::string temp;

    for (char i = std::numeric_limits<char>::min(); i < std::numeric_limits<char>::max(); ++i)
    {
        temp = apply_key(word, i);
        if (verify_string(temp))
        {
            result.push_back(temp);
        }
    }
	
    return result;
}
