#include "Girls_notes.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(Girls_notes, random_generation)
{
    std::string word = random_word(word_size);

    EXPECT_EQ(word.size(), word_size);
    EXPECT_TRUE(verify_string(word));
}

TEST(Girls_notes, correct_work)
{
    std::string word = random_word(word_size);
    char key = generate_random_key();
    std::string enc_word = apply_key(word, key);
    std::vector<std::string> vect_of_poss_words = decrypt_possible_words(enc_word);

    EXPECT_THAT(vect_of_poss_words, testing::Contains(word));
    EXPECT_NE(word, enc_word);
}

TEST(Girls_notes, verify_verify_string)
{
    std::string word = "1234567890_+*-";
    std::string word2 = "dsrfgdfrjddf  fyjfesdr ";

    EXPECT_FALSE(verify_string(word));
    EXPECT_TRUE(verify_string(word2));
}
