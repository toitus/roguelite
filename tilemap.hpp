#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "observer.hpp"

class Tilemap : public Tile_Observer {

    public:

        Tilemap();

        void initialize();
        void events(sf::Event* e);
        void update(sf::Vector2i player_pos);
        void draw(sf::RenderWindow* w);

        void occupy(int r, int c);
        void evacuate(int r, int c);
        bool is_tile_walkable(int r, int c);

        int rows() { return map_rows; }
        int columns() { return map_columns; }
        int height() { return map_rows * tilesize; }
        int width() { return map_columns * tilesize; }

        sf::Vector2i entrance() { return map_entrance; }
        sf::Vector2i exit() { return map_exit; }

        void generate_cellular_cave();

    private:

        int tilesize = 40;
        int map_rows = 60;
        int map_columns = 60;
        int map_caverns = 1;

        sf::Font tilemap_font;

        bool fog_enabled = true; //testing

        sf::Vector2i player_position;
        float fog_radius = 121;

        struct Tile {
            sf::Text string;
            bool walkable;
            int cavern;
        };

        std::vector<std::vector<Tile>> tiles;

        std::vector<std::vector<sf::Vector2i>> caverns;

        std::vector<sf::Vector2i> flood_cavern(int r, int c);

        void center_tile_text(int r, int c);

        void randomize_entrance_and_exit();
        sf::Vector2i map_entrance;
        sf::Vector2i map_exit;

};