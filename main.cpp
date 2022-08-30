#include <SFML/Graphics.hpp>
#include <iostream>

#include "tilemap.hpp"

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "roguelite");

    Tilemap map(50, 50);

    map.draw();

    while (window.isOpen()) {

        //events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        //update

        //draw
        window.clear();

        window.display();
    }

    return 0;
}