#include <iostream>

#include <controllers/linkedlist_controller_sfml.hpp>
#include <models/linkedlist.hpp>
#include <views/linkedlist_view_sfml.hpp>

int main(int /*argc*/, char const * /*argv*/[])
{
    linkedlist_view_sfml view(720, 640, "Lab 5. MVC");

    container::linkedlist<int> list;

    linkedlist_controller_sfml controller(&view, list);

    view.show();

    return 0;
}
