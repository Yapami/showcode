#include <cassert>
#include <iostream>

//#define  DEBUG

struct Node
{
    Node *next_node_ptr{};
    uint32_t field{};
};

class FORWARD_CYCLE_LIST
{
public:
    FORWARD_CYCLE_LIST()
        : head(nullptr)
    {
    }
    ~FORWARD_CYCLE_LIST()
    {
        if (head)
        {
            Node *temp_one = head->next_node_ptr;
            Node *temp_two;
            head->next_node_ptr = nullptr;

            for (; temp_one->next_node_ptr != nullptr;)
            {
                temp_two = temp_one->next_node_ptr;
                delete temp_one;
                temp_one = temp_two;
            }
            delete temp_one;
        }
    }
    void push_back(uint32_t value)
    {
        Node *temp = new Node;
        temp->field = value;
        if (!head)
        {
            temp->next_node_ptr = temp;
            head = temp;
        }
        else
        {
            Node *search_tail = head;
            for (; search_tail->next_node_ptr != head;)
            {
                search_tail = search_tail->next_node_ptr;
            }
            temp->next_node_ptr = head;
            search_tail->next_node_ptr = temp;
        }
    }
    Node *pop_next(Node *value)
    {
        Node *temp = nullptr;
        if (head == nullptr)
        {
            return value;
        }
        else if (head->next_node_ptr == head)
        {
            temp = value->next_node_ptr->next_node_ptr;
            delete value;
            head = nullptr;
            return nullptr;
        }
        else if (head->next_node_ptr != head && head != nullptr)
        {
            temp = value->next_node_ptr->next_node_ptr;
            if (value->next_node_ptr == head)
            {
                head = temp;
            }
            delete[] value->next_node_ptr;
            value->next_node_ptr = temp;
            return temp;
        }
        return nullptr;
    }
    Node *get_head()
    {
        return head;
    }

private:
    Node *head;
};

int solution_by_form(int number_of_soldiers, int dead_number)
{
    if (number_of_soldiers < 1 || dead_number < 1)
    {
        return -1;
    }
    if (number_of_soldiers == 1)
    {
        return 1;
    }
    else
    {
        return (solution_by_form(number_of_soldiers - 1, dead_number) + dead_number - 1) %
                   number_of_soldiers +
               1;
    }
}

int solution_by_list(int number_of_soldiers, int dead_number)
{
    if (number_of_soldiers < 1 || dead_number < 1)
    {
        return -1;
    }
    FORWARD_CYCLE_LIST soldiers;
    uint32_t counter = 1;

    for (uint32_t i = 0; i < number_of_soldiers; ++i)
    {
        soldiers.push_back(i + 1);
    }

    Node *it = soldiers.get_head();
    for (; it->next_node_ptr != it;)
    {
        if (counter == dead_number - 1)
        {
            it = soldiers.pop_next(it);
            counter = 1;
            continue;
        }
        it = it->next_node_ptr;
        ++counter;
    }
    return soldiers.get_head()->field;
}

#ifdef DEBUG
void Test()
{
    int number_of_soldiers, dead_number, result;

    number_of_soldiers = 10;
    dead_number = 3;
    result = 4;
    assert(solution_by_form(number_of_soldiers, dead_number) == result);
    assert(solution_by_list(number_of_soldiers, dead_number) == result);

    number_of_soldiers = 10;
    dead_number = -1;
    result = -1;
    assert(solution_by_form(number_of_soldiers, dead_number) == result);
    assert(solution_by_list(number_of_soldiers, dead_number) == result);

    number_of_soldiers = -1;
    dead_number = 3;
    result = -1;
    assert(solution_by_form(number_of_soldiers, dead_number) == result);
    assert(solution_by_list(number_of_soldiers, dead_number) == result);

    number_of_soldiers = -1;
    dead_number = -1;
    result = -1;
    assert(solution_by_form(number_of_soldiers, dead_number) == result);
    assert(solution_by_list(number_of_soldiers, dead_number) == result);

    number_of_soldiers = 10;
    dead_number = 0;
    result = -1;
    assert(solution_by_form(number_of_soldiers, dead_number) == result);
    assert(solution_by_list(number_of_soldiers, dead_number) == result);

    number_of_soldiers = 0;
    dead_number = 3;
    result = -1;
    assert(solution_by_form(number_of_soldiers, dead_number) == result);
    assert(solution_by_list(number_of_soldiers, dead_number) == result);

    number_of_soldiers = 0;
    dead_number = 0;
    result = -1;
    assert(solution_by_form(number_of_soldiers, dead_number) == result);
    assert(solution_by_list(number_of_soldiers, dead_number) == result);

    number_of_soldiers = 41;
    dead_number = 3;
    result = 31;
    assert(solution_by_form(number_of_soldiers, dead_number) == result);
    assert(solution_by_list(number_of_soldiers, dead_number) == result);
}
#endif

int main()
{
#ifdef DEBUG
    Test();
#endif

    uint32_t NUMBER_OF_SOLDIERS, DEAD_NUMBER;
    std::cout << "Enter the number of soldiers: ";
    std::cin >> NUMBER_OF_SOLDIERS;

    std::cout << "Enter which numbers will die: ";
    std::cin >> DEAD_NUMBER;

    int result_by_list = solution_by_list(NUMBER_OF_SOLDIERS, DEAD_NUMBER);
    int result_by_form = solution_by_form(NUMBER_OF_SOLDIERS, DEAD_NUMBER);

    if (result_by_list == result_by_form)
    {
        std::cout << "Solution found!" << std::endl;
    }
    else
    {
        std::cout << "No solution found!" << std::endl;
        return -1;
    }

    std::cout << "The soldier in position " << result_by_list << " will survive." << std::endl;

    return 0;
}
