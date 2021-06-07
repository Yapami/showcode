#include "Word_pack.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(Word_pack, random_word)
{
    std::string word = random_word();

    EXPECT_EQ(word.size(), 6);
    EXPECT_THAT(word, testing::Each(testing::Ge('a')));
    EXPECT_THAT(word, testing::Each(testing::Le('z')));
}

TEST(Word_pack, empty_string)
{
    std::string word;
    uint32_t digit_word = word_pack(word);

    EXPECT_EQ(digit_word, 0);

    word = word_unpack(digit_word);

    EXPECT_EQ(word, "aaaaaa");
}

TEST(Word_pack, correct_word)
{
    std::string word = random_word();
    uint32_t digit_word = word_pack(word);
    std::string result = word_unpack(digit_word);

    EXPECT_EQ(word, result);
}
