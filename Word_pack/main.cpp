#include "Word_pack.h" 
#include <iostream>

int main()
{
    std::string a;
    a = random_word();
    uint32_t t = word_pack(a);
    std::cout << a << "\t\t"<< t << std::endl<<"--------------------------"<< std::endl;
    a = word_unpack(t);     
    std::cout << a << "\t\t" << t << std::endl << "--------------------------" << std::endl;
}
 
