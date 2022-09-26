#pragma once

#ifndef INCL_CONTROLLERS_LINKEDLIST_CONTROLLER_SFML_HPP
#define INCL_CONTROLLERS_LINKEDLIST_CONTROLLER_SFML_HPP

#include "base_linkedlist_controller.hpp"

class linkedlist_controller_sfml : public mvc::base_linkedlist_controller
{
public:
    linkedlist_controller_sfml(mvc::base_linkedlist_view &view, container::linkedlist<int> &list)
        : mvc::base_linkedlist_controller(view, list) {}

    void notify(mvc::Event event) override
    {
        switch (event)
        {
        case mvc::Event::Add:
            /* code */
            break;

        case mvc::Event::Remove:
            /* code */
            break;

        case mvc::Event::Find:
            /* code */
            break;

        case mvc::Event::Update:
            /* code */
            break;

        default:
            break;
        }

        send(*list());
    }
};

#endif // INCL_CONTROLLERS_LINKEDLIST_CONTROLLER_SFML_HPP