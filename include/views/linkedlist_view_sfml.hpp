#pragma once

#ifndef INCL_VIEWS_LINKEDLIST_VIEW_SFML_HPP
#define INCL_VIEWS_LINKEDLIST_VIEW_SFML_HPP

#include "base_linkedlist_view.hpp"

class linkedlist_view_sfml : public mvc::base_linkedlist_view
{
public:
    linkedlist_view_sfml() = default;

    void show() override {}
};

#endif // INCL_VIEWS_LINKEDLIST_VIEW_SFML_HPP