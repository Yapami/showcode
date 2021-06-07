#pragma once

#include <vector>
#include <stdexcept>

enum class Id
{
    FRONT,
    BACK,
};

class Stack
{
public:
    Stack(size_t stack_size);
    void push(unsigned int value, Id id);
    unsigned int pop(Id id);
    unsigned int top(Id id);
    void clear(Id id);
    unsigned int size(Id id);
    unsigned int capacity();

private:
    std::vector<unsigned int>::iterator stack_front;
    std::vector<unsigned int>::reverse_iterator stack_back;
    std::vector<unsigned int> stack;
};
