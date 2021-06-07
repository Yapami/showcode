#include "List_in_file.h"
#include "StringList.h"
#include <filesystem>

MyStringList::MyStringList(std::string file_name)
{
    if (!std::filesystem::exists(file_name.c_str()))
    {
        open_file(file_name.c_str());
        set_head(PTR_TO_HEAD, type_of_list::MAIN);
        set_head(PTR_TO_REMOVE_HEAD, type_of_list::REMOVE);
        return;
    }

    open_file(file_name.c_str());
}

uint32_t MyStringList::choise_list(type_of_list type)
{
    if (type == type_of_list::MAIN)
    {
        return PTR_TO_HEAD;
    }
    else
    {
        return PTR_TO_REMOVE_HEAD;
    }
}

uint32_t MyStringList::get_head(type_of_list type)
{
    uint32_t list_type = choise_list(type);

    uint32_t head;

    ios.seekg(list_type);
    ios.read(reinterpret_cast<char *>(&head), sizeof(head));

    return head;
}

void MyStringList::set_head(uint32_t address, type_of_list type)
{
    uint32_t list_type = choise_list(type);

    ios.seekp(list_type);
    ios.write(reinterpret_cast<char *>(&address), sizeof(uint32_t));
    ios.seekp(PTR_TO_HEAD);
}

bool MyStringList::insert(const std::string &s, uint32_t pos)
{
    Node new_node;
    new_node.value = s;
    uint32_t suitable_address = search_suitable_place(s.size());

    if (pos == 0)
    {
        new_node.next_ptr = get_head(type_of_list::MAIN);

        set_head(suitable_address, type_of_list::MAIN);

        ios.seekp(suitable_address);

        write(new_node);

        return true;
    }

    uint32_t ad_previous_node;
    uint32_t ad_current_node;
    uint32_t ad_next_node = get_head(type_of_list::MAIN);
    for (uint32_t i = 0; i < pos && ad_next_node != PTR_TO_HEAD; ++i)
    {
        search(ad_next_node);
    }
    ad_previous_node = static_cast<uint32_t>(ios.tellg()) - sizeof(ad_next_node);

    new_node.next_ptr = ad_next_node;

    ios.seekp(suitable_address);

    ad_current_node = ios.tellp();

    write(new_node);

    ios.seekp(ad_previous_node);
    ios.write(reinterpret_cast<char *>(&ad_current_node), sizeof(ad_current_node));
    ios.seekp(PTR_TO_HEAD);

    return true;
}

bool MyStringList::remove(uint32_t pos)
{
    if (get_head(type_of_list::MAIN) == PTR_TO_HEAD)
    {
        return false;
    }

    if (pos == 0)
    {
        uint32_t head;
        ios.seekg(get_head(type_of_list::MAIN));
        ios.read(reinterpret_cast<char *>(&head), sizeof(head));
        add_remove(get_head(type_of_list::MAIN));
        set_head(head, type_of_list::MAIN);

        return true;
    }

    uint32_t ad_previous_node;
    uint32_t ad_current_node;
    uint32_t ad_next_node = get_head(type_of_list::MAIN);
    for (uint32_t i = 0; i < pos; ++i)
    {
        search(ad_next_node);
        if (ad_next_node == PTR_TO_HEAD)
        {
            return false;
        }
    }

    ad_current_node = ad_next_node;

    ad_previous_node = static_cast<uint32_t>(ios.tellg()) - sizeof(ad_next_node);

    ios.seekg(ad_next_node);
    ios.read(reinterpret_cast<char *>(&ad_next_node), sizeof(ad_next_node));

    ios.seekp(ad_previous_node);
    ios.write(reinterpret_cast<char *>(&ad_next_node), sizeof(ad_next_node));

    add_remove(ad_current_node);

    ios.seekp(PTR_TO_HEAD);

    return true;
}

void MyStringList::add_remove(uint32_t address)
{
    uint32_t current_position = ios.tellg();
    if (get_head(type_of_list::REMOVE) == PTR_TO_REMOVE_HEAD)
    {
        set_head(address, type_of_list::REMOVE);

        ios.seekp(address);
        ios.write(reinterpret_cast<const char *>(&PTR_TO_REMOVE_HEAD), sizeof(PTR_TO_REMOVE_HEAD));
        ios.seekp(PTR_TO_REMOVE_HEAD);
    }

    uint32_t address_last = get_head(type_of_list::REMOVE);
    while (address_last != PTR_TO_REMOVE_HEAD)
    {
        ios.seekg(address_last);
        ios.read(reinterpret_cast<char *>(&address_last), sizeof(address_last));
    }
    address_last = static_cast<uint32_t>(ios.tellg()) - sizeof(address_last);

    ios.seekp(address_last);
    ios.write(reinterpret_cast<char *>(&address), sizeof(address));

    ios.seekp(address);
    ios.write(reinterpret_cast<const char *>(&PTR_TO_REMOVE_HEAD), sizeof(PTR_TO_REMOVE_HEAD));
    ios.seekg(PTR_TO_REMOVE_HEAD);
    ios.seekg(current_position);
}

void MyStringList::remove_remove(uint32_t address)
{
    uint32_t ad_previous;
    uint32_t ad_next = get_head(type_of_list::REMOVE);
    while (ad_next != address)
    {
        ios.seekg(ad_next);
        ios.read(reinterpret_cast<char *>(&ad_next), sizeof(ad_next));
    }
    ad_previous = static_cast<uint32_t>(ios.tellg()) - sizeof(ad_next);
    ios.seekg(ad_next);
    ios.read(reinterpret_cast<char *>(&ad_next), sizeof(ad_next));

    ios.seekp(ad_previous);
    ios.write(reinterpret_cast<const char *>(&ad_next), sizeof(ad_next));
    ios.seekp(PTR_TO_REMOVE_HEAD);
}

uint32_t MyStringList::search_suitable_place(uint32_t str_size)
{
    uint32_t address = 0;
    std::string str_temp;
    uint32_t suitable_place = get_head(type_of_list::REMOVE);
    if (suitable_place == PTR_TO_REMOVE_HEAD)
    {
        ios.seekg(0, ios.end);
        address = ios.tellg();
        return address;
    }

    while (suitable_place != PTR_TO_REMOVE_HEAD)
    {
        ios.seekg(suitable_place);
        address = suitable_place;
        ios.read(reinterpret_cast<char *>(&suitable_place), sizeof(suitable_place));
        std::getline(ios, str_temp, '\0');
        if (str_temp.size() >= str_size)
        {
            remove_remove(address);
            return address;
        }
    }
    ios.seekg(0, ios.end);
    address = ios.tellg();
    return address;
}

void MyStringList::clear(std::string file_name)
{
    ios.close();
    ios.open(file_name.c_str(), std::ios::out | std::ios::in | std::ios::binary | std::ios::trunc);
    if (!ios.is_open())
    {
        return;
    }

    set_head(PTR_TO_HEAD, type_of_list::MAIN);
    set_head(PTR_TO_REMOVE_HEAD, type_of_list::REMOVE);
}

const std::string MyStringList::string(uint32_t pos)
{
    std::string result;
    uint32_t address = get_head(type_of_list::MAIN);

    if (address == PTR_TO_HEAD)
    {
        return "";
    }

    for (uint32_t i = 0; i <= pos; ++i)
    {
        ios.seekg(address);
        ios.read(reinterpret_cast<char *>(&address), sizeof(address));
        if (address == PTR_TO_HEAD && i < pos)
        {
            return "";
        }
    }
    std::getline(ios, result, '\0');

    return result;
}

void MyStringList::write(Node &element)
{
    ios.write(reinterpret_cast<char *>(&element.next_ptr), sizeof(element.next_ptr));
    ios.write(element.value.c_str(), element.value.size() + 1);
    ios.seekp(PTR_TO_HEAD);
}

void MyStringList::search(uint32_t &address)
{
    ios.seekg(address);
    ios.read(reinterpret_cast<char *>(&address), sizeof(address));
}

void MyStringList::open_file(std::string file_name)
{
    ios.open(file_name.c_str(), std::ios::out | std::ios::in | std::ios::binary | std::ios::app);
    if (!ios.is_open())
    {
        return;
    }
}

bool MyStringList::end_of_list(uint32_t last_str_size)
{
    uint32_t ptr_pos = static_cast<uint32_t>(ios.tellg());

    if (get_head(type_of_list::MAIN) == 0)
    {
        ios.seekg(ptr_pos);
        return false;
    }
    ios.seekg(ptr_pos);

    uint32_t ad_of_last_read =
        static_cast<uint32_t>(ios.tellg()) - (last_str_size + 1) - sizeof(uint32_t);

    ios.seekg(ad_of_last_read);
    ios.read(reinterpret_cast<char *>(&ad_of_last_read), sizeof(ad_of_last_read));
    if (ad_of_last_read == PTR_TO_HEAD)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MyStringList::list_is_empty()
{
    if (get_head(type_of_list::MAIN) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
