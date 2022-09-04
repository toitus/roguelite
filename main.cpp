#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "tilemap.hpp"

int main() {

    sf::RenderWindow window(sf::VideoMode(1280, 720), "roguelite");

    srand(time(NULL));

    Tilemap map(100, 100);

    sf::Vector2f center = sf::Vector2f(0.f, 0.f);
    sf::Vector2f size = sf::Vector2f(window.getSize().x, window.getSize().y);
    sf::View view(center, size);

    float zoom = 1.0f;

    while (window.isOpen()) {

        //events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { window.close(); }

            if (event.type == sf::Event::Resized) { 
                size = sf::Vector2f(window.getSize().x, window.getSize().y); 
                window.setView(view);
            }

            if (event.type == sf::Event::MouseWheelMoved) {
                if (event.mouseWheel.delta < 0) { 
                    zoom = zoom + 0.1f;
                    view.setSize(size);
                    view.zoom(zoom);
                } else if (event.mouseWheel.delta > 0) {
                    zoom = zoom - 0.1f;
                    if (zoom < 1.0f) { zoom = 1.0f; }
                    view.setSize(size);
                    view.zoom(zoom);
                }
            }
            
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) { map.generate_new_map(); }
            }
        }

        //update
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { view.move(-5.f, 0.f); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { view.move(5.f, 0.f); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { view.move(0.f, -5.f); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { view.move(0.f, 5.f); }

        //draw
        window.clear();
            window.setView(view);
            map.draw(&window);
        window.display();
    }

    return 0;
}