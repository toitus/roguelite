#pragma once

#include <SFML/Graphics.hpp>

class Tile {

    public:
        Tile() {  }
        void set_texture(sf::Texture* t) { sprite.setTexture(*t); }
        void set_font(sf::Font* f) { text.setFont(*f); text.setCharacterSize(12); }
        void set_texture_rect(sf::IntRect r) { sprite.setTextureRect(r); }
        void set_sprite_position() { sprite.setPosition(sf::Vector2f(column*size, row*size)); text.setPosition(sf::Vector2f(column*size, row*size)); }
        void set_position(int r, int c) { row = r; column = c; text.setString(std::to_string(r) + " " + std::to_string(c)); }
        void set_id(int i) { id = i; /*text.setString(std::to_string(i));*/ }
        void set_cavern(int c) { cavern = c; }
        void set_empty() { empty = true; /*text.setString(" ");*/ }
        void set_occupied() { empty = false; /*text.setString("X");*/ }

        int get_row() { return row; }
        int get_column() { return column; }
        sf::Vector2f get_position() { return sprite.getPosition(); }
        int get_id() { return id; }
        int get_cavern() { return cavern; }
        bool is_empty() { return empty == true; }
        bool is_occupied() { return empty == false; }

        void draw(sf::RenderWindow* w) { w->draw(sprite); /*w->draw(text);*/ }

    private:

        int row;
        int column;
        int size = 24;
        int id = 0;
        int cavern = -1;

        bool empty = false;

        sf::Sprite sprite;
        sf::Text text;

};