#pragma once

#include <string>
#include <map>

//'V' - root, '^' - power, '*' - multiply, '/' - divide, '+' - plus, '-' - minus
const std::map<char, size_t> sign_priority{{'V', 3}, {'^', 3}, {'*', 2}, {'/', 2}, 
                                     {'+', 1}, {'-', 1}, {'(', 0}};

bool issign(const char sign);
std::string toRPN(std::string str);
double sign_action(const double first_member, const double second_member, const char sign);
double colculate(const std::string &RPN_format_str);