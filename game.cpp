#include "game.hpp"

Game::Game(sf::RenderWindow* w) {
    window = w;
    window->setFramerateLimit(60);

    tilemap.initialize();

    view_center = tilemap.player_center();
    view_size = sf::Vector2f(window->getSize().x, window->getSize().y);
    view = sf::View(view_center, view_size);

}

void Game::run() {
    while (window->isOpen()) {
        events();
        time_since_last_step += step_clock.restart();
        while (time_since_last_step >= target_step_time) {
            time_since_last_step -= target_step_time;
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
            if (zoom < 1.0f) zoom = 1.0f;
            view.zoom(zoom);
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                tilemap.generate_cellular_cave();
            }
        }

        tilemap.events(&event);

    }
}

void Game::update() {

    camera_follow_player();
    tilemap.update();

}

void Game::draw() {
    window->clear(sf::Color::Black);
    window->setView(view);
    tilemap.draw(window);
    window->display();
}

void Game::camera_follow_player() {
    sf::Vector2f player = tilemap.player_center();
    sf::Vector2f center = view.getCenter();
    sf::Vector2f difference = player - center;
    float length = sqrt(pow(difference.x, 2) + pow(difference.y, 2));
    float speed = 5;
    if (length < 25 && tilemap.no_movement_input()) speed = 8;
    if (length > 8) {
        sf::Vector2f camera_move = difference * target_step_time.asSeconds() * speed;
        view.move(camera_move);
    }
}