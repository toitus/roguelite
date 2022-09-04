#pragma once

#include <SFML/Graphics.hpp>

class Tile {

    public:
        void set_position(int r, int c) { row = r; column = c; text.setPosition(row*size, column*size); }
        void set_font(sf::Font* f) { text.setFont(*f); text.setCharacterSize(16); text.setFillColor(sf::Color::Green); }
        void set_id(int i) { id = i; if (id == 1) {text.setString("X");} else {text.setString(" ");}}
        void set_cavern(int c) { cavern = c; }
        void set_text(std::string s) { text.setString(s); }

        int get_row() { return row; }
        int get_column() { return column; }
        int get_cavern() { return cavern; }

        void draw(sf::RenderWindow* w) { w->draw(text); }

    private:

        int row;
        int column;
        int size = 16;
        int id = 0;
        int cavern = -1;

        sf::Text text;

};