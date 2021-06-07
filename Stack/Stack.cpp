#include "Stack.h"

Stack::Stack(size_t stack_size)
{
    stack.reserve(stack_size);
    stack.resize(stack_size, 0);
    stack_front = stack.begin();
    stack_back = stack.rbegin();
}

void Stack::push(unsigned int value, Id id)
{
    if (stack_front == stack_back.base())
    {
        throw std::overflow_error("Stack Overflow");
    }

    if (id == Id::FRONT)
    {
        *stack_front = value;
        ++stack_front;
    }
    else
    {
        *stack_back = value;
        ++stack_back;
    }
}

uint32_t Stack::pop(Id id)
{
    uint32_t value;
    if (id == Id::FRONT)
    {
        if (stack_front == stack.begin())
        {
            throw std::out_of_range("Range Error");
        }

        --stack_front;
        value = *stack_front;
    }
    else
    {
        if (stack_back == stack.rbegin())
        {
            throw std::out_of_range("Range Error");
        }

        --stack_back;
        value = *stack_back;
    }
    return value;
}

unsigned int Stack::top(Id id)
{

    if (id == Id::FRONT)
    {
        if (stack_front == stack.begin())
        {
            throw std::out_of_range("Stack is empty");
        }
        return *(stack_front - 1);
    }
    else
    {
        if (stack_back == stack.rbegin())
        {
            throw std::out_of_range("Stack is empty");
        }
        return *(stack_back - 1);
    }
}

void Stack::clear(Id id)
{

    if (id == Id::FRONT)
    {
        stack_front = stack.begin();
    }
    else
    {
        stack_back = stack.rbegin();
    }
}

unsigned int Stack::size(Id id)
{

    if (id == Id::FRONT)
    {
        return std::distance(stack.begin(), stack_front);
    }
    else
    {
        return std::distance(stack.rbegin(), stack_back);
    }
}

unsigned int Stack::capacity()
{
    return stack.capacity();
}

