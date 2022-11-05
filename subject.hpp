#pragma once

#include "observer.hpp"

#include <vector>

class Tile_Subject {

    public:

        void set_tilemap(Tile_Observer* obs) { tilemap = obs; }
        void occupy(int r, int c) { tilemap->occupy(r, c); }
        void evacuate(int r, int c) { tilemap->evacuate(r, c); }
        bool is_walkable(int r, int c) { return tilemap->is_walkable(r, c); }

    private:

        Tile_Observer* tilemap;

};