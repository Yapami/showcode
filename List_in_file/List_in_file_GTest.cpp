#include "List_in_file.h"
#include <gtest/gtest.h>
#include <list>

const std::string FILE_NAME = "list.bin";

class MyTest : public MyStringList
{
public:
    MyTest(std::string file_name)
        : MyStringList(file_name)
    {
    }

    std::list<std::string> get_list_of_values()
    {
        std::list<std::string> list;
        if (list_is_empty())
        {
            return list;
        }
        
        for (uint32_t i = 0;; ++i)
        {
            std::string str = string(i);

            list.push_back(str);

            if (end_of_list(str.size()))
            {
                break;
            }
        }
        return list;
    }
};

TEST(List_in_file, insert)
{
    const uint32_t list_size = 10;
    MyTest test(FILE_NAME);
    test.clear(FILE_NAME);
    std::list<std::string> expected_values;

    for (int i = 0; i < list_size; ++i)
    {
        EXPECT_TRUE(test.insert(std::to_string(i), i));
        expected_values.push_back(std::to_string(i));
    }
    std::list<std::string> list_from_file = test.get_list_of_values();

    EXPECT_EQ(list_from_file, expected_values);

    expected_values.clear();
    test.clear(FILE_NAME);

    EXPECT_TRUE(test.insert("0", 0));
    EXPECT_TRUE(test.insert("2", 1));
    EXPECT_TRUE(test.insert("1", 1));
    list_from_file = test.get_list_of_values();
    for (uint32_t i = 0; i < 3; ++i)
    {
        expected_values.push_back(std::to_string(i));
    }

    EXPECT_EQ(list_from_file, expected_values);

    EXPECT_TRUE(test.insert("12345", 12345));
}

TEST(List_in_file, remove)
{
    const uint32_t list_size = 10;
    MyTest test(FILE_NAME);
    test.clear(FILE_NAME);

    EXPECT_FALSE(test.remove(0));

    std::list<std::string> expected_values;

    for (int i = 0; i < list_size; ++i)
    {
        test.insert(std::to_string(i), i);
        expected_values.push_back(std::to_string(i));
    }

    test.remove(list_size - 1);
    std::list<std::string> list_from_file = test.get_list_of_values();
    expected_values.pop_back();

    EXPECT_EQ(list_from_file, expected_values);

    test.remove(0);
    list_from_file = test.get_list_of_values();
    expected_values.remove("0");

    EXPECT_EQ(list_from_file, expected_values);

    EXPECT_FALSE(test.remove(list_size));
    list_from_file = test.get_list_of_values();

    EXPECT_EQ(list_from_file, expected_values);

    test.clear(FILE_NAME);
    expected_values.clear();

    for (int i = 0; i < list_size; ++i)
    {
        test.insert(std::to_string(i), i);
        expected_values.push_back(std::to_string(i));
    }

    for (int i = 0; i < list_size; ++i)
    {
        test.remove(0);
        expected_values.remove(std::to_string(i));
    }
    list_from_file = test.get_list_of_values();

    EXPECT_EQ(list_from_file, expected_values);

    // your test:
    test.clear(FILE_NAME);

    for (int i = 0; i < list_size; ++i)
    {
        EXPECT_TRUE(test.insert(std::to_string(i), 0));
        expected_values.push_front(std::to_string(i));
    }

    for (int i = 0; i < list_size; ++i)
    {
        EXPECT_TRUE(test.remove(0));
        list_from_file = test.get_list_of_values();
        expected_values.pop_front();
        EXPECT_EQ(list_from_file, expected_values);
    }

    EXPECT_FALSE(test.remove(12345));
}

TEST(List_in_file, string)
{
    const uint32_t list_size = 10;
    MyTest test(FILE_NAME);
    test.clear(FILE_NAME);

    for (int i = 0; i < list_size; ++i)
    {
        test.insert(std::to_string(i), i);
    }

    EXPECT_EQ(test.string(5), "5");
    EXPECT_EQ(test.string(0), "0");
    EXPECT_EQ(test.string(9), "9");
    EXPECT_EQ(test.string(list_size), "");
}

TEST(List_in_file, equal)
{
    const uint32_t list_size = 10;
    MyTest test_1(FILE_NAME);
    test_1.clear(FILE_NAME);

    for (int i = 0; i < list_size; ++i)
    {
        test_1.insert(std::to_string(i), i);
    }

    MyTest test_2(FILE_NAME);

    EXPECT_EQ(test_1.get_list_of_values(), test_2.get_list_of_values());
}

TEST(List_in_file, main_and_remove_lists)
{
    const uint32_t list_size = 10;
    MyTest test(FILE_NAME);
    std::list<std::string> expected_values;
    test.clear(FILE_NAME);

    for (int i = 0; i < list_size; ++i)
    {
        test.insert(std::to_string(i), i);
        expected_values.push_back(std::to_string(i));
    }

    std::list<std::string>::iterator it = expected_values.begin();
    std::advance(it, 3);
    for (int i = 0; i < 3; ++i)
    {
        test.remove(3);
        it = expected_values.erase(it);
    }

    it = expected_values.begin();
    for (int i = 0; i < 3; ++i)
    {
        test.insert(std::to_string(i + 5), i);
        expected_values.insert(it, std::to_string(i + 5));
    }

    std::list<std::string> list_from_file = test.get_list_of_values();

    EXPECT_EQ(list_from_file, expected_values);
}
