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

namespace detail
{

    struct Node final : sf::Drawable
    {
        sf::RectangleShape bg;
        sf::RectangleShape tail;
        sf::Text number, index;

        Node(sf::RectangleShape bg, sf::RectangleShape tail, sf::Text number, sf::Text index)
            : bg{std::move(bg)}, tail{std::move(tail)}, number{std::move(number)}, index{std::move(index)} {}

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(tail, states);
            target.draw(bg, states);
            target.draw(number, states);
            target.draw(index, states);
        }
    };

} // namespace detail

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
        _rec_width = _window.getSize().x / _nodes_size;
        _nodes.reserve(_window.getSize().y / _rec_width * _nodes_size);

        ImGui::GetIO().Fonts->Clear();
        ImGui::GetIO().Fonts->AddFontFromFileTTF(_fontPath.data(), 24.f);
        ImGui::SFML::UpdateFontTexture();
    }

    void show() override
    {
        sf::Vector2f oldPos;
        bool moving = false;

        float zoom = 1;

        sf::View view = _window.getDefaultView();

        sf::Clock deltaClock;
        while (_window.isOpen())
        {
            sf::Event event;
            while (_window.pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(event);

                switch (event.type)
                {
                case sf::Event::Closed:
                    _window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == 0)
                    {
                        moving = true;
                        oldPos = _window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == 0)
                    {
                        moving = false;
                    }
                    break;
                case sf::Event::MouseMoved:
                {
                    if (!moving)
                        break;
                    const sf::Vector2f newPos = _window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                    const sf::Vector2f deltaPos = oldPos - newPos;

                    view.setCenter(view.getCenter() + deltaPos);
                    _window.setView(view);

                    oldPos = _window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                    break;
                }
                case sf::Event::MouseWheelScrolled:
                    if (moving)
                        break;

                    if (event.mouseWheelScroll.delta <= -1)
                        zoom = std::min(2.f, zoom + .1f);
                    else if (event.mouseWheelScroll.delta >= 1)
                        zoom = std::max(.5f, zoom - .1f);

                    view.setSize(_window.getDefaultView().getSize());
                    view.zoom(zoom);
                    _window.setView(view);
                    break;
                }
            }

            ImGui::SFML::Update(_window, deltaClock.restart());

#pragma region ImGui
            ImGui::Begin("Play with linkedlist<int>");

            ImGui::InputInt("Item to add/contains", &_item);
            ImGui::InputInt("Index (orange number) to update", &_index);

            if (ImGui::Button("Add"))
                controller()->notify(mvc::Event::Add);

            if (ImGui::Button("Pop"))
                controller()->notify(mvc::Event::Pop);

            if (ImGui::Button("Contains"))
                controller()->notify(mvc::Event::Contains);

            if (ImGui::Button("Update"))
                controller()->notify(mvc::Event::Update);

            ImGui::End();
#pragma endregion

            _window.clear(sf::Color::White);

            for (const auto &node : _nodes)
            {
                _window.draw(node);
            }

            ImGui::SFML::Render(_window);
            _window.display();
        }
    }

private:
    void update(const container::linkedlist<int> &list) override
    {
        _nodes.clear();

        for (size_t i = 0; i < list.size(); ++i)
        {
            const uint32_t pos_x = (_rec_width + _merge) * i + 8;
            const uint32_t pos_y = _window.getSize().y / 2 - _rec_width / 2;

#pragma region Backgound
            sf::RectangleShape bg;
            bg.setSize(sf::Vector2f(_rec_width, _rec_width));
            bg.setPosition(sf::Vector2f(pos_x, pos_y));

            if (i % 2)
                bg.setFillColor(sf::Color(50, 60, 168));
            else
                bg.setFillColor(sf::Color(25, 100, 140));
#pragma endregion

#pragma region Tail
            sf::RectangleShape tail;

            if (i < list.size() - 1)
            {
                tail.setSize(sf::Vector2f(_merge, _merge));
                tail.setPosition(sf::Vector2f(pos_x + _rec_width, pos_y + _rec_width / 2));
                tail.setFillColor(sf::Color(115, 25, 140));
            }

#pragma endregion

            static const sf::Font font = std::invoke([fp = _fontPath]()
                                                     {
                sf::Font font;
                font.loadFromFile(fp.data());
                return font; });

#pragma region Text
            sf::Text number;
            number.setString(std::to_string(list[i]));
            number.setFont(font);
            number.setCharacterSize(_font_size);
            number.setStyle(sf::Text::Italic | sf::Text::Bold | sf::Text::Underlined);
            number.setFillColor(sf::Color::White);
            number.setPosition(sf::Vector2f(pos_x + _rec_width / 2 - _font_size / 2, pos_y + _rec_width / 2));
#pragma endregion

#pragma region Index
            sf::Text index;
            index.setString(std::to_string(i));
            index.setFont(font);
            index.setCharacterSize(_font_size);
            index.setStyle(sf::Text::Italic | sf::Text::Bold | sf::Text::Underlined);
            index.setFillColor(sf::Color(252, 94, 3));
            index.setPosition(sf::Vector2f(pos_x, pos_y));
#pragma endregion

            _nodes.emplace_back(std::move(bg), std::move(tail), std::move(number), std::move(index));
        }
    }

    mvc::detail::Data get_data() const override
    {
        return {_item, _index};
    }

private:
    sf::RenderWindow _window;

    const uint32_t _nodes_size = 10;

    const uint32_t _merge = 20;

    uint32_t _rec_width = 0;

    const uint32_t _font_size = 40;

    std::vector<detail::Node> _nodes;

    int _item{}, _index{};

    const std::string_view _fontPath = "C:/My/Projects/cpp/linkedlist/resources/fonts/Lato-Italic.ttf";
};

#endif // INCL_VIEWS_LINKEDLIST_VIEW_SFML_HPP