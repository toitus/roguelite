#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Player {

    public:

        void events(sf::Event* event);
        void update();
        void draw(sf::RenderWindow* window);

        sf::Vector2f get_sprite_position_center() { return sprite.getPosition() + sf::Vector2f(size/2, size/2); }
        int get_row() { return row_column.x; }
        int get_column() { return row_column.y; }
        void set_position(sf::Vector2f v) { sprite.setPosition(v); }
        void set_row_column(sf::Vector2i v) { row_column = v; sprite.setPosition(v.y*size, v.x*size); }
        void set_texture(sf::Texture* t) { sprite.setTexture(*t); sprite.setTextureRect(idle); }

    private:

        int size = 24;

        sf::Vector2i row_column;

        sf::IntRect idle = sf::IntRect(0, 0, size, size);
        sf::Sprite sprite;

};