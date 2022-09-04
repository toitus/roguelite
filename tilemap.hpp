#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <stdlib.h>

class Tilemap {

    public:

        Tilemap(int w, int h);
        void draw(sf::RenderWindow* window);
        void generate_new_map();

    private:

        int tilesize = 16;
        int width;
        int height;
        sf::Font font;

        struct tile {
            int x;
            int y;
            int id = 0;
            int cavern = -1;
            sf::Text text;
            void set_text() {
                text.setCharacterSize(16);
                text.setFillColor(sf::Color::Green);
                if (id == 1) { text.setString("X"); }
                if (id == 0) { text.setString(" "); }
                text.setPosition(x, y);
            };
            void set_font(sf::Font* f) { text.setFont(*f); }
        };
        std::vector<std::vector<tile>> tiles;
        void set_tiles();

        std::vector<std::vector<int>> cells;
        std::vector<std::vector<int>> old_cells;
        void set_cells();
        void cellular_step();
        int count_living_neighbors(int r, int c);

};