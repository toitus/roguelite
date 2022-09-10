#pragma once

#include <SFML/Graphics.hpp>

class Player {

    public:

        Player();

        void events(sf::Event event);
        void update();
        void draw(sf::RenderWindow* window);

        void set_sprite(sf::Texture* t);

    private:

        int row;
        int column;
        int size = 24;


        sf::IntRect idle = sf::IntRect(0, 0, size, size);
        sf::Sprite sprite;

};