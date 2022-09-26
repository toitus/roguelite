#pragma once

#include <SFML/Graphics.hpp>

#include "tilemap.hpp"
#include "player.hpp"

class Game {

    public:

        Game(sf::RenderWindow* w);
        void run();

    private:

        void events();
        void update();
        void draw();

        sf::Event event;
        sf::RenderWindow* window;

        sf::Texture tilesheet;
        sf::Font font;

        sf::Clock game_clock;
        sf::Time time_since_last_step = sf::Time::Zero;
        sf::Time target_time_per_step = sf::seconds(1.f/60.f);

        sf::View view;
        sf::Vector2f view_size, view_center;
        float zoom = 1.0f;

        Player player;
        int map_rows = 100;
        int map_columns = 100;
        Tilemap map = Tilemap(map_rows, map_columns);

};