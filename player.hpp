#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "subject.hpp"

class Player : public Subject {

    public:

        void initialize();

        void place(int r, int c);
        int row() { return current_row; }
        int column() { return current_column; }
        sf::Vector2f center();

        void update_view(float dt, sf::View* v);
        void listen_for_movement_input();
        void apply_queued_movement();
        void queue(sf::String movement);

        void events(sf::Event* e);
        void update(float dt, sf::View* v);
        void draw(sf::RenderWindow* w);

    private:

        int current_row;
        int current_column;
        int tilesize = 45;

        sf::Font player_font;
        sf::Text icon;
        sf::View view;

        int movement_frame_counter = 0;
        int movement_speed = 25;
        float frames_to_finish_movement;

        std::vector<sf::String> movement_queue;

};