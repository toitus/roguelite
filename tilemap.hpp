#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "observer.hpp"
#include "player.hpp"

class Tilemap : public Observer {

    public:

        Tilemap();

        void initialize();
        void events(sf::Event* e);
        void update();
        void draw(sf::RenderWindow* w);

        void occupy(int r, int c);
        void evacuate(int r, int c);

        int rows() { return map_rows; }
        int columns() { return map_columns; }
        int height() { return map_rows * tilesize; }
        int width() { return map_columns * tilesize; }

        sf::Vector2f player_center();
        bool no_movement_input() { return no_movement_inputs; }
        void player_movement_input();

        void generate_cellular_cave();

    private:

        int tilesize = 48;
        int map_rows = 100;
        int map_columns = 100;
        int map_caverns = 1;

        bool no_movement_inputs;

        sf::Font font;

        //bool determines if a tile is walkable
        std::vector<std::vector<std::pair<sf::Text, bool>>> tiles;

        std::vector<std::vector<int>> cavern_ids;
        std::vector<std::vector<sf::Vector2i>> caverns;

        std::vector<sf::Vector2i> flood_cavern(int r, int c);

        Player player;

};