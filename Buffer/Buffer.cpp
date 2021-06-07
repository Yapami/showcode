#include "Buffer.h"

void Buffer::add_element(unsigned int element)
{
    container.push_back(element);
    if (container.size() == container.capacity())
    {
        container.erase(container.begin(), container.begin() + (container.capacity() / 2));
    }
}

Buffer::Buffer(size_t size)
{
    container.reserve(size);
}

const std::vector<unsigned int>::iterator Buffer::begin()
{
    return container.begin();
}

const std::vector<unsigned int>::iterator Buffer::end()
{
    return container.end();
}

unsigned int Buffer::capacity()
{
    return container.capacity();
}

unsigned int Buffer::size()
{
    return container.size();
}
