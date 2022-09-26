#include "game.hpp"

Game::Game(sf::RenderWindow* w) {
    window = w;
    view_center = sf::Vector2f((map_columns/2)*map.get_tilesize(), (map_rows/2)*map.get_tilesize());
    view_size = sf::Vector2f(window->getSize().x, window->getSize().y);
    view = sf::View(view_center, view_size);

    if (!font.loadFromFile("content/font.ttf")) { std::cout << "content/font.ttf failed to load!" << std::endl; }

    if (!tilesheet.loadFromFile("content/tilesheet.png")) { std::cout << "content/tilesheet.png failed to load!" << std::endl; }
    tilesheet.setSmooth(true);

    map.set_texture(&tilesheet, &font);
    player.set_texture(&tilesheet);
    map.generate_new_map(); 
    player.set_row_column(map.get_random_row_column());
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

        player.events(&event);

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) { 
                map.generate_new_map(); 
                player.set_row_column(map.get_random_row_column()); 
            }

            if (event.key.code == sf::Keyboard::W) { //move up
                if (map.is_tile_empty(player.get_row()-1, player.get_column())) { }
            }
            if (event.key.code == sf::Keyboard::A) { //move left
                if (map.is_tile_empty(player.get_row(), player.get_column()-1)) { }
            }
            if (event.key.code == sf::Keyboard::S) { //move down
                if (map.is_tile_empty(player.get_row()+1, player.get_column())) { } 
            }
            if (event.key.code == sf::Keyboard::D) { //move right
                if (map.is_tile_empty(player.get_row(), player.get_column()+1)) { }
            }
        }
    }
}

void Game::update() {
    //view.setCenter(player.get_sprite_position_center());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { view.move(-15.f, 0.f); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { view.move(15.f, 0.f); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { view.move(0.f, -15.f); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { view.move(0.f, 15.f); }
    player.update();
}

void Game::draw() {
    window->clear();
        window->setView(view);
        map.draw(window);
        player.draw(window);
    window->display();
}