#include <iostream>

#include "include/linkedlist.hpp"

int main(int /*argc*/, char const * /*argv*/[])
{
    container::linkedlist<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    std::cout << list[0] << '\n';
    std::cout << list[1] << '\n';
    std::cout << list[2] << '\n';
    std::cout << list[3] << '\n';

    try
    {
        std::cout << list[4] << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    for (auto it = std::begin(list); it; ++it)
    {
        std::cout << *it << ", ";
    }

    return 0;
}
