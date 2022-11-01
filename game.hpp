#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

#include "tilemap.hpp"

class Game {

    public:

        Game(sf::RenderWindow* w);
        void run();

    private:

        sf::RenderWindow* window;
        sf::Event event;

        sf::View view;
        sf::Vector2f view_size, view_center;
        float zoom = 1.0f;

        sf::Clock step_clock;
        sf::Time time_since_last_step = sf::Time::Zero;
        sf::Time target_step_time = sf::seconds(1.f/60.f);

        sf::Font font;

        Tilemap tilemap;

        void events();
        void update();
        void draw();

        void camera_follow_player();

};