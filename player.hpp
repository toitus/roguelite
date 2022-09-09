#pragma once

#include <SFML/Graphics.hpp>

class Player {

    public:

        void events(sf::Event* event);
        void update();
        void draw(sf::RenderWindow* window);

    private:

        int row;
        int column;
        int size = 24;

};