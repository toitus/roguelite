#pragma once

#include "observer.hpp"

#include <vector>

class Tile_Subject {

    public:

        void set_tilemap(Tile_Observer* obs) { tilemap = obs; }
        void occupy_tile(sf::Vector2i t) { tilemap->occupy(t.x, t.y); }
        void evacuate_tile(sf::Vector2i t) { tilemap->evacuate(t.x, t.y); }
        bool is_tile_walkable(sf::Vector2i t) { return tilemap->is_tile_walkable(t.x, t.y); }

    private:

        Tile_Observer* tilemap;

};