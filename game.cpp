#include "game.hpp"

Game::Game(sf::RenderWindow* w) {
    window = w;
    center = sf::Vector2f(50.f*24.f, 50.f*24.f);
    size = sf::Vector2f(window->getSize().x, window->getSize().y);
    view = sf::View(center, size);
    if (!tilesheet.loadFromFile("content/tilesheet.png")) { std::cout << "Tilemap's tilesheet failed to load!" << std::endl; }
    tilesheet.setSmooth(true);
    map.set_texture(tilesheet);
}

void Game::run() {
    while (window->isOpen()) {
        events();
        time_since_last_step += game_clock.restart();
        while (time_since_last_step >= target_time_per_step) {
            time_since_last_step -= target_time_per_step;
            events();
            update();
        }
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