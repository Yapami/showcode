#include "RPN.h"

#include <algorithm>
#include <math.h>
#include <stack>

std::string toRPN(std::string str)
{
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());

    for (int i = 0; i < str.size(); ++i)
    {
        if ((str[i] == '+' || str[i] == '-') &&
            (i == 0 || (issign(str[i - 1]) && str[i - 1] != ')')))
        {
            auto it = std::find_if(str.begin() + i + 1, str.end(),
                                   [](char const c) { return issign(c); });
            str.insert(it, ')');
            str.insert(i, "(0");
        }
    }

    std::string result;
    std::stack<char> st;

    for (uint32_t i = 0; i < str.size(); ++i)
    {
        char a = str[i];
        if (isdigit(str[i]))
        {
            std::string temp;
            while (((isdigit(str[i + 1]) || str[i + 1] == '.')) && (i + 1) <= str.size())
            {
                temp.push_back(str[i]);
                ++i;
            }
            temp.push_back(str[i]);
            result += temp + ' ';
        }
        else if (')' == str[i])
        {
            while (st.top() != '(')
            {
                result += st.top();
                result += ' ';
                st.pop();
            }
            st.pop();
        }
        else if ('(' == str[i] ||
                 (st.empty() || (sign_priority.at(st.top()) < sign_priority.at(str[i]))))
        {
            st.push(str[i]);
        }
        else
        {
            do
            {
                result += st.top();
                result += ' ';
                st.pop();
            } while (!(st.empty() || (sign_priority.at(st.top()) < sign_priority.at(str[i]))));
            st.push(str[i]);
        }
    }

    while (!st.empty())
    {
        result += st.top();
        result += ' ';
        st.pop();
    }

    return result;
}

bool issign(const char sign)
{
    return !(sign_priority.find(sign) == sign_priority.end());
}

double sign_action(const double first_member, const double second_member, const char sign)
{
    switch (sign)
    {
    case '-':
        return first_member - second_member;
    case '+':
        return first_member + second_member;
    case '*':
        return first_member * second_member;
    case '/':
        return first_member / second_member;
    case '^':
        return pow(first_member, second_member);
    case 'V':
        return pow(second_member, 1 / first_member);
    }
    return 0;
}

double colculate(const std::string &RPT_format_str)
{
    std::stack<double> st;
    std::string temp;

    for (uint32_t i = 0; i < RPT_format_str.size(); i++)
    {
        if (RPT_format_str[i] == ' ')
        {
            st.push(std::stod(temp));
            temp = "";
        }
        else if (issign(RPT_format_str[i]))
        {
            double second_number = st.top();
            st.pop();
            double first_number = st.top();
            st.pop();
            st.push(sign_action(first_number, second_number, RPT_format_str[i]));
            ++i;
        }
        else
        {
            temp += RPT_format_str[i];
        }
    }
    return st.top();
}