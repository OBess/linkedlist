#include <type_traits>

#include <gtest/gtest.h>

#include <linkedlist.hpp>

TEST(linkedlist, empty)
{
    container::linkedlist<int> list;

    EXPECT_TRUE(list.empty());

    list.push_back(0);

    EXPECT_FALSE(list.empty());
}

TEST(linkedlist, initializer_list)
{
    container::linkedlist<int> list{1, 2, 3, 4, 5};

    EXPECT_EQ(list.size(), 5);
    EXPECT_FALSE(list.empty());
}

TEST(linkedlist, CTAD)
{
    container::linkedlist list{1, 2, 3, 4, 5};

    EXPECT_EQ(list.size(), 5);
    EXPECT_FALSE(list.empty());
}

TEST(linkedlist, push_back)
{
    container::linkedlist<int> list;

    const auto vars = {1, 2, 3, 4, 5};

    for (const auto i : vars)
    {
        list.push_back(i);
    }

    EXPECT_EQ(list.size(), 5);
    EXPECT_FALSE(list.empty());

    for (size_t i = 0; i < list.size(); ++i)
    {
        EXPECT_EQ(list[i], *(vars.begin() + i));
    }
}

TEST(linkedlist, push_front)
{
    container::linkedlist<int> list;

    const auto vars1 = {1, 2, 3, 4, 5};
    const auto vars2 = {5, 4, 3, 2, 1};

    for (const auto i : vars1)
    {
        list.push_front(i);
    }

    EXPECT_EQ(list.size(), 5);
    EXPECT_FALSE(list.empty());

    for (size_t i = 0; i < list.size(); ++i)
    {
        EXPECT_EQ(list[i], *(vars2.begin() + i));
    }
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}