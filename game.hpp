#pragma once

#include <SFML/Graphics.hpp>

#include "tilemap.hpp"

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

        sf::Clock game_clock;
        sf::Time time_since_last_step = sf::Time::Zero;
        sf::Time target_time_per_step = sf::seconds(1.f/60.f);

        sf::Vector2f size, center;
        sf::View view;
        float zoom = 1.0f;

        Tilemap map = Tilemap(100, 100);

};