#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Tilemap {

    public:

        Tilemap(int w, int h);
        void draw();

    private:

        int tilesize = 16;
        int width;
        int height;

        struct tile {
            int x;
            int y;
            int id = 0;
            int cavern = 0;
        };

        std::vector<std::vector<tile>> tiles;

};