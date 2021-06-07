#pragma once

#include <vector>

class Buffer
{
public:
    Buffer(size_t size);

    void add_element(unsigned int element);

    const std::vector<unsigned int>::iterator begin();

    const std::vector<unsigned int>::iterator end();

    unsigned int capacity();

    unsigned int size();

private:
    std::vector<unsigned int> container;
};
