#pragma once

#include <SFML/Graphics.hpp>

class Tile {

    public:
        void set_position(int r, int c) { row = r; column = c; sprite.setPosition(row*size, column*size); }
        void set_id(int i) { id = i; }
        void set_cavern(int c) { cavern = c; }
        void set_occupied(bool o) { occupied = o; }
        void set_texture(sf::Texture* s) { sprite.setTexture(*s); }
        void set_texture_rect(sf::IntRect r) { sprite.setTextureRect(r); }
        void set_origin_to_center() { sprite.setOrigin(size/2, size/2); }

        int get_row() { return row; }
        int get_column() { return column; }
        sf::Vector2i get_position() { return sf::Vector2i(row*size + size/2, column*size + size/2); }
        int get_id() { return id; }
        int get_cavern() { return cavern; }
        bool is_occupied() { return occupied; }

        void draw(sf::RenderWindow* w) { w->draw(sprite); }

    private:

        int row;
        int column;
        int size = 24;
        int id = 0;
        int cavern = -1;

        bool occupied = true;

        sf::Sprite sprite;

};