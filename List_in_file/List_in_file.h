#pragma once

#include "StringList.h"
#include <fstream>

const uint32_t PTR_TO_HEAD = std::ios_base::beg;

const uint32_t PTR_TO_REMOVE_HEAD = std::ios_base::beg + sizeof(PTR_TO_HEAD);

enum class type_of_list
{
    MAIN,
    REMOVE,
};

struct Node
{
    uint32_t next_ptr;
    std::string value;
};

class MyStringList : public StringList
{
public:
    MyStringList(std::string file_name);

    bool insert(const std::string &s, uint32_t pos) override;

    bool remove(uint32_t pos) override;

    void clear(std::string file_name);

    const std::string string(uint32_t pos);

protected:
    bool end_of_list(uint32_t last_str_size);

    bool list_is_empty();

private:
    std::fstream ios;

    uint32_t get_head(type_of_list type);

    void set_head(uint32_t address, type_of_list type);

    void write(Node &element);

    void search(uint32_t &address);

    void open_file(std::string file_name);

    uint32_t choise_list(type_of_list type);

    void add_remove(uint32_t address);

    void remove_remove(uint32_t address);

    uint32_t search_suitable_place(uint32_t str_size);
};
