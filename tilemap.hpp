#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <stdlib.h>

#include "tile.hpp"

class Tilemap {

    public:

        Tilemap(int w, int h);
        void draw(sf::RenderWindow* w);
        void generate_new_map();

    private:

        int width;
        int height;
        int cavern_count = 1;
        sf::Font font;

        std::vector<std::vector<Tile>> tiles;
        void set_tiles();

        std::vector<std::vector<int>> cells;
        std::vector<std::vector<int>> old_cells;
        void set_cells();
        void cellular_step();
        int count_living_neighbors(int r, int c);

        std::vector<std::vector<sf::Vector2i>> caverns;
        void identify_caverns();
        std::vector<sf::Vector2i> fill_cavern(int r, int c);

};