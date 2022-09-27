#pragma once

#ifndef INCL_CONTROLLERS_LINKEDLIST_CONTROLLER_SFML_HPP
#define INCL_CONTROLLERS_LINKEDLIST_CONTROLLER_SFML_HPP

#include "base_linkedlist_controller.hpp"

class linkedlist_controller_sfml : public mvc::base_linkedlist_controller
{
public:
    linkedlist_controller_sfml(mvc::base_linkedlist_view *view, container::linkedlist<int> *list)
        : mvc::base_linkedlist_controller(view, list)
    {
    }

    void notify(mvc::Event event) override
    {
        const auto _data = data();

        switch (event)
        {
        case mvc::Event::Add:
            list()->push_back(_data.index);
            break;

        case mvc::Event::Pop:
            list()->pop_back();
            break;

        case mvc::Event::Contains:
        {
            bool result = list()->contains(_data.item);
            std::cout << result << '\n';
        }
        break;

        case mvc::Event::Update:
            (*list())[_data.index] = _data.item;
            break;

        default:
            break;
        }

        send(*list());
    }
};

#endif // INCL_CONTROLLERS_LINKEDLIST_CONTROLLER_SFML_HPP