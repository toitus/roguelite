#include "game.hpp"

Game::Game(sf::RenderWindow* w) {
    window = w;
    center = sf::Vector2f(50.f*16.f, 50.f*16.f);
    size = sf::Vector2f(window->getSize().x, window->getSize().y);
    view = sf::View(center, size);
}

void Game::run() {
    while (window->isOpen()) {
        events();
        update();
        draw();
    }
}

void Game::events() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) { window->close(); }

        if (event.type == sf::Event::Resized) { 
            view.setSize(event.size.width, event.size.height);
            view.zoom(zoom);
            window->setView(view);
        }

        if (event.type == sf::Event::MouseWheelMoved) {
            sf::Vector2u size = window->getSize();
            view.setSize(size.x, size.y);
            zoom -= 0.3f * event.mouseWheel.delta;
            if (zoom < 1.0f) { zoom = 1.0f; }
            view.zoom(zoom);
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) { map.generate_new_map(); }
        }
    }
}

void Game::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { view.move(-5.f, 0.f); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { view.move(5.f, 0.f); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { view.move(0.f, -5.f); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { view.move(0.f, 5.f); }
}

void Game::draw() {
    window->clear();
        window->setView(view);
        map.draw(window);
    window->display();
}