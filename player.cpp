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
    place(5, 5);
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

void Player::place(int r, int c) {
    current_row = r;
    current_column = c; 
    icon.setPosition(
        c*tilesize + tilesize/2,
        r*tilesize + tilesize/2
    );
}

void Player::listen_for_movement_input() {
    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::X);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    bool up_left = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    bool up_right = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
    bool down_left = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    bool down_right = sf::Keyboard::isKeyPressed(sf::Keyboard::C);

    int r = current_row;
    int c = current_column;

    if (up && is_walkable(r-1, c)) { queue("up"); }
    if (left && is_walkable(r, c-1)) { queue("left"); }
    if (down && is_walkable(r+1, c)) { queue("down"); }
    if (right && is_walkable(r, c+1)) { queue("right"); }
    if (up_left && is_walkable(r-1, c-1)) { queue("up left"); }
    if (up_right && is_walkable(r-1, c+1)) { queue("up right"); }
    if (down_left && is_walkable(r+1, c-1)) { queue("down left"); }
    if (down_right && is_walkable(r+1, c+1)) { queue("down right"); }
}

void Player::apply_queued_movement() {
    if (movement_queue.size() > 0) {
        sf::String front = movement_queue.front();
        frames_to_finish_movement = movement_speed;
        if (front == "up") { icon.move(0, -tilesize/frames_to_finish_movement); }
        if (front == "left") { icon.move(-tilesize/frames_to_finish_movement, 0); }
        if (front == "down") { icon.move(0, tilesize/frames_to_finish_movement); }
        if (front == "right") { icon.move(tilesize/frames_to_finish_movement, 0); }

        if (front == "up left") { 
            frames_to_finish_movement = ceil(movement_speed*sqrt(2)); 
            icon.move(-tilesize/frames_to_finish_movement, -tilesize/frames_to_finish_movement);
        }
        if (front == "up right") { 
            frames_to_finish_movement = ceil(movement_speed*sqrt(2)); 
            icon.move(tilesize/frames_to_finish_movement, -tilesize/frames_to_finish_movement);
        }
        if (front == "down left") { 
            frames_to_finish_movement = ceil(movement_speed*sqrt(2)); 
            icon.move(-tilesize/frames_to_finish_movement, tilesize/frames_to_finish_movement);
        }
        if (front == "down right") { 
            frames_to_finish_movement = ceil(movement_speed*sqrt(2)); 
            icon.move(tilesize/frames_to_finish_movement, tilesize/frames_to_finish_movement);
        }

        movement_frame_counter++;
        if (movement_frame_counter == frames_to_finish_movement) {
            movement_queue.erase(movement_queue.begin());
            movement_frame_counter = 0;
        }
    }
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

void Player::queue(sf::String movement) {
    bool movement_queued = false;

    if (movement_queue.size() == 1) {
        sf::String front = movement_queue.front();
        if (movement == "up" && front != "up") {
            movement_queue.push_back(movement);
            evacuate(current_row, current_column);
            current_row--;
            movement_queued = true;
        }
        if (movement == "left" && front != "left") {
            movement_queue.push_back(movement);
            evacuate(current_row, current_column);
            current_column--;
            movement_queued = true;
        }
        if (movement == "down" && front != "down") {
            movement_queue.push_back(movement);
            evacuate(current_row, current_column);
            current_row++;
            movement_queued = true;
        }
        if (movement == "right" && front != "right") {
            movement_queue.push_back(movement);
            evacuate(current_row, current_column);
            current_column++;
            movement_queued = true;
        }
        if (movement == "up left" && front != "up left") {
            movement_queue.push_back(movement);
            evacuate(current_row, current_column);
            current_row--;
            current_column--;
            movement_queued = true;
        }
        if (movement == "up right" && front != "up right") {
            movement_queue.push_back(movement);
            evacuate(current_row, current_column);
            current_row--;
            current_column++;
            movement_queued = true;
        }
        if (movement == "down left" && front != "down left") {
            movement_queue.push_back(movement);
            evacuate(current_row, current_column);
            current_row++;
            current_column--;
            movement_queued = true;
        }
        if (movement == "down right" && front != "down right") {
            movement_queue.push_back(movement);
            evacuate(current_row, current_column);
            current_row++;
            current_column++;
            movement_queued = true;
        }
    } else if (movement_queue.empty()) {
        movement_queue.push_back(movement);
        if (movement == "up") {
            evacuate(current_row, current_column);
            current_row--;
            movement_queued = true;
        }
        if (movement == "left") {
            evacuate(current_row, current_column);
            current_column--;
            movement_queued = true;
        }
        if (movement == "down") {
            evacuate(current_row, current_column);
            current_row++;
            movement_queued = true;
        }
        if (movement == "right") {
            evacuate(current_row, current_column);
            current_column++;
            movement_queued = true;
        }
        if (movement == "up left") {
            evacuate(current_row, current_column);
            current_row--;
            current_column--;
            movement_queued = true;
        }
        if (movement == "up right") {
            evacuate(current_row, current_column);
            current_row--;
            current_column++;
            movement_queued = true;
        }
        if (movement == "down left") {
            evacuate(current_row, current_column);
            current_row++;
            current_column--;
            movement_queued = true;
        }
        if (movement == "down right") {
            evacuate(current_row, current_column);
            current_row++;
            current_column++;
            movement_queued = true;
        }
    }

    if (movement_queued) {
        occupy(current_row, current_column);
    }
}

sf::Vector2f Player::center() {
    return icon.getPosition();
}