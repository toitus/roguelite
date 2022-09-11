#pragma once

#include <SFML/Graphics.hpp>

class Tile {

    public:
        Tile() {  }
        void set_texture(sf::Texture* t) { sprite.setTexture(*t); }
        void set_texture_rect(sf::IntRect r) { sprite.setTextureRect(r); }
        void set_sprite_position() { sprite.setPosition(sf::Vector2f(row*size, column*size)); }
        void set_position(int r, int c) { row = r; column = c; }
        void set_id(int i) { id = i; }
        void set_cavern(int c) { cavern = c; }
        void set_occupied(bool o) { occupied = o; }

        int get_row() { return row; }
        int get_column() { return column; }
        sf::Vector2f get_position() { return sprite.getPosition(); }
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