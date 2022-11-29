#pragma once

#include <SFML/Graphics.hpp>

#include "subject.hpp"

class Enemy : public Tile_Subject {

    public:

        virtual void initialize() = 0;
        void set_position(sf::Vector2i p);

    private:

        sf::Font font;
        sf::Text icon;

        sf::Vector2i current_position = sf::Vector2i(-1, -1);

        sf::Vector2i up = sf::Vector2i(-1, 0);
        sf::Vector2i left = sf::Vector2i(0, -1);
        sf::Vector2i down = sf::Vector2i(1, 0);
        sf::Vector2i right = sf::Vector2i(0, 1);
        sf::Vector2i up_left = sf::Vector2i(-1, -1);
        sf::Vector2i up_right = sf::Vector2i(-1, 1);
        sf::Vector2i down_left = sf::Vector2i(1, -1);
        sf::Vector2i down_right = sf::Vector2i(1, 1);

};