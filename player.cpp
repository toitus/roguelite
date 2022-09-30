#include "player.hpp"

Player::Player() {

}

void Player::events(sf::Event* event) {
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::P) {
            std::cout << row_column.x << " " << row_column.y << std::endl;
        }
    }
}

void Player::update() {
    apply_movement();
}

void Player::draw(sf::RenderWindow* window) {
    window->draw(sprite);
}

void Player::apply_movement() {
    if (movement_queue.size() > 0) {
        if (movement_queue.at(0) == "up") {
            sprite.move(0, -size/frames_to_finish_movement);
        } else if (movement_queue.at(0) == "left") {
            sprite.move(-size/frames_to_finish_movement, 0);
        } else if (movement_queue.at(0) == "down") {
            sprite.move(0, size/frames_to_finish_movement);
        } else if (movement_queue.at(0) == "right") {
            sprite.move(size/frames_to_finish_movement, 0);
        }
        movement_frame_counter++;
        if (movement_frame_counter == frames_to_finish_movement) { 
            movement_queue.erase(movement_queue.begin());
            movement_frame_counter = 0;
        }
    }
}

void Player::queue_movement(std::string d) {
    if (movement_queue.size() == 0 || (movement_queue.size() < 2 && movement_queue.at(0) != d)) {
        movement_queue.push_back(d);
        if (d == "up") row_column.x--;
        if (d == "left") row_column.y--;
        if (d == "down") row_column.x++;
        if (d == "right") row_column.y++;
    }
}