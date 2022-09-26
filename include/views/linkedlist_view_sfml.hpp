#pragma once

#ifndef INCL_VIEWS_LINKEDLIST_VIEW_SFML_HPP
#define INCL_VIEWS_LINKEDLIST_VIEW_SFML_HPP

#include <vector>

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

    void init()
    {
        _rec_width = _window.getSize().x / _nodes_size - _merge;
        _nodes.reserve(_window.getSize().y / _rec_width * _nodes_size);
    }

    void show() override
    {
        sf::Clock deltaClock;
        while (_window.isOpen())
        {
            sf::Event event;
            while (_window.pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(event);

                if (event.type == sf::Event::Closed)
                {
                    _window.close();
                }
            }

            ImGui::SFML::Update(_window, deltaClock.restart());

            _window.clear(sf::Color::White);

            draw_nodes();

            ImGui::SFML::Render(_window);
            _window.display();
        }
    }

private:
    void draw_nodes()
    {
        for (const auto &node : _nodes)
        {
            _window.draw(node);
        }
    }

    void update(const container::linkedlist<int> &list) override
    {
        _nodes.clear();

        size_t i = 0;
        for (const auto &item : list)
        {
            sf::RectangleShape bg(sf::Vector2f(_rec_width, _rec_width));
            bg.setPosition(sf::Vector2f(_rec_width * i + _merge, _rec_width * (i / _nodes_size) + _merge));

            sf::RectangleShape tail;
            sf::Text number;

            _nodes.emplace_back(std::move(bg), std::move(tail), std::move(number));

            ++i;
        }
    }

    sf::RenderWindow _window;

    struct Node final : sf::Drawable
    {
        sf::RectangleShape bg;
        sf::RectangleShape tail;
        sf::Text number;

        Node(sf::RectangleShape bg, sf::RectangleShape tail, sf::Text number)
            : bg{std::move(bg)}, tail{std::move(tail)}, number{std::move(number)} {}

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(bg, states);
            target.draw(tail, states);
            target.draw(number, states);
        }
    };

    const unsigned _nodes_size = 10;
    const unsigned _merge = 5;
    unsigned _rec_width = 0;
    std::vector<Node> _nodes;
};

#endif // INCL_VIEWS_LINKEDLIST_VIEW_SFML_HPP