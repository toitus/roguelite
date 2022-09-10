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

        bool can_move_left(int r, int c) { return tiles[r][c-1].is_occupied(); }
        bool can_move_right(int r, int c) { return tiles[r][c+1].is_occupied(); }
        bool can_move_up(int r, int c) { return tiles[r-1][c].is_occupied(); }
        bool can_move_down(int r, int c) { return tiles[r+1][c].is_occupied(); }
        bool can_move_up_left(int r, int c) { return tiles[r-1][c-1].is_occupied(); }
        bool can_move_up_right(int r, int c) { return tiles[r-1][c+1].is_occupied(); }
        bool can_move_down_left(int r, int c) { return tiles[r+1][c-1].is_occupied(); } 
        bool can_move_down_right(int r, int c) { return tiles[r+1][c+1].is_occupied(); }

        void set_texture(sf::Texture t) { tilesheet = t; }

    private:

        int width;
        int height;
        int tilesize = 24;
        int cavern_count = 1;

        sf::Texture tilesheet;

        sf::IntRect floor = sf::IntRect(0, tilesize, tilesize, tilesize);
        sf::IntRect outer_wall = sf::IntRect(tilesize, 0, tilesize, tilesize);
        sf::IntRect inner_wall = sf::IntRect(tilesize, tilesize, tilesize, tilesize);

        std::vector<std::vector<Tile>> tiles;
        void identify_tiles();
        void identify_tile_textures();

        std::vector<std::vector<int>> cells;
        std::vector<std::vector<int>> old_cells;
        void set_cells();
        void cellular_step();
        int count_living_neighbors(int r, int c);

        std::vector<std::vector<sf::Vector2i>> caverns;
        void identify_caverns();
        std::vector<sf::Vector2i> fill_cavern(int r, int c);

        void identify_inner_walls();

};