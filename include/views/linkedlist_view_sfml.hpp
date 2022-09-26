#pragma once

#ifndef INCL_VIEWS_LINKEDLIST_VIEW_SFML_HPP
#define INCL_VIEWS_LINKEDLIST_VIEW_SFML_HPP

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "base_linkedlist_view.hpp"

class linkedlist_view_sfml : public mvc::base_linkedlist_view
{
public:
    linkedlist_view_sfml(uint32_t width, uint32_t height, std::string_view title)
        : _window(sf::VideoMode(width, height),
                  title.data(), sf::Style::None | sf::Style::Close | sf::Style::Titlebar,
                  sf::ContextSettings{0, 0, 8})
    {
        _window.setVerticalSyncEnabled(true);
        _window.setFramerateLimit(60);
        _window.resetGLStates();

        ImGui::SFML::Init(_window);
        init();
    }

    ~linkedlist_view_sfml()
    {
        ImGui::SFML::Shutdown();
    }

    void init() {}

    void show() override {}

private:
    sf::RenderWindow _window;
};

#endif // INCL_VIEWS_LINKEDLIST_VIEW_SFML_HPP