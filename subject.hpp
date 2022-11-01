#pragma once

#include "observer.hpp"

#include <vector>

class Subject {

    public:

        void set_tilemap(Observer* obs) { tilemap = obs; }
        void occupy(int r, int c) { tilemap->occupy(r, c); }
        void evacuate(int r, int c) { tilemap->evacuate(r, c); }

    private:

        Observer* tilemap;

};