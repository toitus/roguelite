#include "game.hpp"

Game::Game(sf::RenderWindow* w) {
    window = w;
    window->setFramerateLimit(120);

    //if (!game_font.loadFromFile(" ")) { std::cout << " failed to load" << std::endl; }

    tilemap.initialize();
    player.initialize();
    player.set_tilemap(&tilemap);

    view_center = player.center();
    view_size = sf::Vector2f(window->getSize().x, window->getSize().y);
    view = sf::View(view_center, view_size);
    view.zoom(zoom);

}

void Game::run() {
    while (window->isOpen()) {
        if (window->hasFocus()) events();
        time_since_last_step += step_clock.restart();
        while (time_since_last_step >= target_step_time) {
            time_since_last_step -= target_step_time;
            if (window->hasFocus()) update();            
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
            zoom -= 0.25f * event.mouseWheel.delta;
            if (zoom < 1.25f) zoom = 1.25f;
            view.zoom(zoom);
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                tilemap.generate_cellular_cave();
            }
        }

        player.events(&event);
        tilemap.events(&event);

    }
}

void Game::update() {
    tilemap.update(player.center());
    player.update(target_step_time.asSeconds(), &view);
}

void Game::draw() {
    window->clear(sf::Color::Black);
    window->setView(view);
    tilemap.draw(window);
    player.draw(window);
    window->display();
}