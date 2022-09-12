#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Player {

    public:

        void events(sf::Event event);
        void update();
        void draw(sf::RenderWindow* window);

        sf::Vector2f get_sprite_position_center() { return sprite.getPosition() + sf::Vector2f(size/2, size/2); }
        void set_position(sf::Vector2f p) { sprite.setPosition(p); }
        void set_texture(sf::Texture* t) { sprite.setTexture(*t); sprite.setTextureRect(idle); }

    private:

        int size = 24;

        sf::IntRect idle = sf::IntRect(0, 0, size, size);
        sf::Sprite sprite;

};