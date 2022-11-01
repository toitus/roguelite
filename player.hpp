#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "subject.hpp"

class Player : public Subject {

    public:

        void initialize(sf::Font* f);

        void place(int r, int c);
        void move();
        int row() { return current_row; }
        int column() { return current_column; }
        sf::Vector2f center();

        void queue(sf::String movement);

        void events(sf::Event* e);
        void update();
        void draw(sf::RenderWindow* w);

    private:

        int current_row;
        int current_column;
        int tilesize = 48;

        sf::Text icon;

        int movement_frame_counter = 0;
        int movement_speed = 15;
        float frames_to_finish_movement;

        std::vector<sf::String> movement_queue;

};