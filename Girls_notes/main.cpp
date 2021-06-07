#include "Girls_notes.h" 
#include <iostream>

int main()
{
    std::string word = random_word(word_size);
    char key = generate_random_key();

    std::cout << word << std::endl <<"Key: "<< (int)key << std::endl;

    std::vector<std::string> encrypt_word = decrypt_possible_words(word);

    for (uint32_t i = 0; i < encrypt_word.size(); ++i)
    {
        std::cout << encrypt_word[i] << std::endl;
    }
    
    return 0;
}
