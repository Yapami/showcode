#pragma once

#include <random>
#include <string>
#include <vector>

const uint32_t word_size = 60;

std::string random_word(const uint32_t);
char generate_random_key();
std::string apply_key(const std::string &, const char);
bool verify_string(const std::string &);
std::vector<std::string> decrypt_possible_words(const std::string &);
