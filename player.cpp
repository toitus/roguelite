#include "player.hpp"

void Player::initialize() {
    if (player_font.loadFromFile("content/player_font.otf")) {
        icon.setFont(player_font);
        icon.setString("*");
        icon.setCharacterSize(tilesize);
        sf::Vector2f half_text_size = sf::Vector2f(icon.getGlobalBounds().width/2, icon.getGlobalBounds().height/2);
        sf::Vector2f local_text_position = sf::Vector2f(icon.getLocalBounds().left, icon.getLocalBounds().top);
        icon.setOrigin(half_text_size + local_text_position);
        icon.setFillColor(sf::Color::White);
    } else { std::cout << "player font failed to load" << std::endl; }
}

void Player::events(sf::Event* e) {
    if (e->type == sf::Event::KeyPressed) { }
}

void Player::update(float dt, sf::View* v) {
    listen_for_movement_input(); 
    apply_queued_movement();
    update_view(dt, v);
}

void Player::draw(sf::RenderWindow* w) {
    w->draw(icon);
}

void Player::listen_for_movement_input() {
    bool w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool s = sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::X);
    bool d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    bool q = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    bool e = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
    bool z = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    bool c = sf::Keyboard::isKeyPressed(sf::Keyboard::C);

    if (w && is_tile_walkable(current_position + up)) { queue(up); }
    if (a && is_tile_walkable(current_position + left)) { queue(left); }
    if (s && is_tile_walkable(current_position + down)) { queue(down); }
    if (d && is_tile_walkable(current_position + right)) { queue(right); }
    if (q && is_tile_walkable(current_position + up_left)) { queue(up_left); }
    if (e && is_tile_walkable(current_position + up_right)) { queue(up_right); }
    if (z && is_tile_walkable(current_position + down_left)) { queue(down_left); }
    if (c && is_tile_walkable(current_position + down_right)) { queue(down_right); }
}

void Player::apply_queued_movement() {
    if (movement_queue.size() > 0) {
        //is_moving = true;
        sf::Vector2i front = movement_queue.front();
        frames_to_finish_movement = movement_speed;
        if (front == up) { icon.move(0, -tilesize/frames_to_finish_movement); }
        if (front == left) { icon.move(-tilesize/frames_to_finish_movement, 0); }
        if (front == down) { icon.move(0, tilesize/frames_to_finish_movement); }
        if (front == right) { icon.move(tilesize/frames_to_finish_movement, 0); }

        if (front == up_left) { 
            frames_to_finish_movement = ceil(movement_speed*sqrt(2)); 
            icon.move(-tilesize/frames_to_finish_movement, -tilesize/frames_to_finish_movement);
        }
        if (front == up_right) { 
            frames_to_finish_movement = ceil(movement_speed*sqrt(2)); 
            icon.move(tilesize/frames_to_finish_movement, -tilesize/frames_to_finish_movement);
        }
        if (front == down_left) { 
            frames_to_finish_movement = ceil(movement_speed*sqrt(2)); 
            icon.move(-tilesize/frames_to_finish_movement, tilesize/frames_to_finish_movement);
        }
        if (front == down_right) { 
            frames_to_finish_movement = ceil(movement_speed*sqrt(2)); 
            icon.move(tilesize/frames_to_finish_movement, tilesize/frames_to_finish_movement);
        }

        movement_frame_counter++;
        if (movement_frame_counter == frames_to_finish_movement) {
            movement_queue.erase(movement_queue.begin());
            movement_frame_counter = 0;
        }
    } //else { is_moving = false; }
}

void Player::update_view(float dt, sf::View* v) {
    sf::Vector2f player = icon.getPosition();
    sf::Vector2f center = v->getCenter();
    sf::Vector2f difference = player - center;
    float length = sqrt(pow(difference.x, 2) + pow(difference.y, 2));
    float speed = 5;
    if (length < 25 && movement_queue.size() == 0) speed = 8;
    if (length > 8) {
        sf::Vector2f camera_move = difference * dt * speed;
        v->move(camera_move);
    }
}

void Player::queue(sf::Vector2i movement) {
    if (movement_queue.empty() || (movement_queue.size() == 1 && movement_queue.front() != movement)) {
        movement_queue.push_back(movement);
        evacuate_tile(current_position);
        current_position += movement;
        occupy_tile(current_position);
        std::cout << "occupying: " << current_position.x << " " << current_position.y << std::endl;
    }
}

void Player::set_position(sf::Vector2i p) {
    current_position = p;
    icon.setPosition(current_position.y*tilesize + tilesize/2, current_position.x*tilesize + tilesize/2);
    occupy_tile(current_position);
}