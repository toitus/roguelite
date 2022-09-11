#pragma once

#include <SFML/Graphics.hpp>

class Player {

    public:

        void events(sf::Event event);
        void update();
        void draw(sf::RenderWindow* window);

        void set_position(sf::Vector2f p) { position = p; sprite.setPosition(p.x*size, p.y*size); }
        void set_texture(sf::Texture* t) { sprite.setTexture(*t); sprite.setTextureRect(idle); }

    private:

        sf::Vector2f position = sf::Vector2f(0, 0);
        int size = 24;


        sf::IntRect idle = sf::IntRect(0, 0, size, size);
        sf::Sprite sprite;

};