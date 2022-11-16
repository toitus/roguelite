#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "subject.hpp"

class Player : public Tile_Subject {

    public:

        void initialize();

        void set_position(sf::Vector2i p);
        sf::Vector2i position() { return current_position; }
        sf::Vector2f sprite_position() { return icon.getPosition(); }

        void update_view(float dt, sf::View* v);
        void listen_for_movement_input();
        void apply_queued_movement();
        void queue(sf::Vector2i movement);

        bool moving() { return movement_queue.size() > 0; }

        void events(sf::Event* e);
        void update(float dt, sf::View* v);
        void draw(sf::RenderWindow* w);

    private:

        sf::Vector2i current_position = sf::Vector2i(-1, -1);

        int tilesize = 40;

        sf::Font player_font;
        sf::Text icon;
        sf::View view;

        sf::Vector2i up = sf::Vector2i(-1, 0);
        sf::Vector2i left = sf::Vector2i(0, -1);
        sf::Vector2i down = sf::Vector2i(1, 0);
        sf::Vector2i right = sf::Vector2i(0, 1);
        sf::Vector2i up_left = sf::Vector2i(-1, -1);
        sf::Vector2i up_right = sf::Vector2i(-1, 1);
        sf::Vector2i down_left = sf::Vector2i(1, -1);
        sf::Vector2i down_right = sf::Vector2i(1, 1);

        int movement_frame_counter = 0;
        int movement_speed = 25;
        float frames_to_finish_movement;

        std::vector<sf::Vector2i> movement_queue;

};