#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Tilemap {

    public:

        Tilemap(int w, int h);
        void draw(sf::RenderWindow* window);

    private:

        int tilesize = 16;
        int width;
        int height;
        sf::Font font;

        struct tile {
            int x;
            int y;
            int id = 0;
            int cavern = 0;
            sf::Text text;
            sf::Text set_text() {
                text.setCharacterSize(16);
                text.setFillColor(sf::Color::Green);
                text.setString(std::to_string(id));
                text.setPosition(x, y);
            };
            void set_font(sf::Font* f) { text.setFont(*f); }
        };

        std::vector<std::vector<tile>> tiles;

};