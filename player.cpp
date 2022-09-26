#include "player.hpp"

void Player::events(sf::Event* event) {
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::P) {
            std::cout << row_column.x << " " << row_column.y << std::endl;
        }
    }
}

void Player::update() {

}

void Player::draw(sf::RenderWindow* window) {
    window->draw(sprite);
}