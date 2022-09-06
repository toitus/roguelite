#pragma once

#include <SFML/Graphics.hpp>

class Tile {

    public:
        void set_position(int r, int c) { row = r; column = c; sprite.setPosition(row*size, column*size); }
        void set_id(int i) { id = i; }
        void set_cavern(int c) { cavern = c; }
        void set_texture(sf::Texture* s, sf::IntRect r) { sprite.setTexture(*s); sprite.setOrigin(size/2, size/2); sprite.setTextureRect(r); }

        int get_row() { return row; }
        int get_column() { return column; }
        sf::Vector2i get_position() { return sf::Vector2i(row*size, column*size); }
        int get_id() { return id; }
        int get_cavern() { return cavern; }

        void draw(sf::RenderWindow* w) { w->draw(sprite); }

    private:

        int row;
        int column;
        int size = 16;
        int id = 0;
        int cavern = -1;

        sf::Sprite sprite;

};