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
    player.set_row_column(map.get_random_row_column(true));
    player.set_sprite_position(sf::Vector2f(player.get_column()*map.get_tilesize(), player.get_row()*map.get_tilesize()));
}

void Game::run() {
    while (window->isOpen()) {
        events();
        time_since_last_step += game_clock.restart();
        while (time_since_last_step >= target_time_per_step) {
            time_since_last_step -= target_time_per_step;
            //events();
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
                player.set_row_column(map.get_random_row_column(true)); 
                player.set_sprite_position(sf::Vector2f(player.get_column()*map.get_tilesize(), player.get_row()*map.get_tilesize()));
            }
        }
    }
}

void Game::update() {
    view.setCenter(player.get_sprite_position_center());

    oversee_player_movement_queue();

    player.update();
}

void Game::draw() {
    window->clear();
        window->setView(view);
        map.draw(window);
        player.draw(window);
    window->display();
}

void Game::oversee_player_movement_queue() {
    bool w = sf::Keyboard::isKeyPressed(sf::Keyboard::W); //up
    bool a = sf::Keyboard::isKeyPressed(sf::Keyboard::A); //left
    bool s = sf::Keyboard::isKeyPressed(sf::Keyboard::S); //down
    bool d = sf::Keyboard::isKeyPressed(sf::Keyboard::D); //right
    bool q = sf::Keyboard::isKeyPressed(sf::Keyboard::Q); //up left
    bool e = sf::Keyboard::isKeyPressed(sf::Keyboard::E); //up right
    bool z = sf::Keyboard::isKeyPressed(sf::Keyboard::Z); //down left
    bool c = sf::Keyboard::isKeyPressed(sf::Keyboard::C); //down right
    bool x = sf::Keyboard::isKeyPressed(sf::Keyboard::X); //down

    if (w) { if (map.is_tile_empty(player.get_row()-1, player.get_column())) { player.queue_movement("up"); } }
    if (a) { if (map.is_tile_empty(player.get_row(), player.get_column()-1)) { player.queue_movement("left"); } }
    if (s || x) { if (map.is_tile_empty(player.get_row()+1, player.get_column())) { player.queue_movement("down"); } }
    if (d) { if (map.is_tile_empty(player.get_row(), player.get_column()+1)) { player.queue_movement("right"); } }
    if (q) { if (map.is_tile_empty(player.get_row()-1, player.get_column()-1)) { player.queue_movement("upleft"); } }
    if (e) { if (map.is_tile_empty(player.get_row()-1, player.get_column()+1)) { player.queue_movement("upright"); } }
    if (z) { if (map.is_tile_empty(player.get_row()+1, player.get_column()-1)) { player.queue_movement("downleft"); } }
    if (c) { if (map.is_tile_empty(player.get_row()+1, player.get_column()+1)) { player.queue_movement("downright"); } }
}