#include "tilemap.hpp"

Tilemap::Tilemap(int w, int h) {
    width = w;
    height = h;

    tiles = std::vector<std::vector<tile>>(width, std::vector<tile>(height));
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            tiles[row][col].x = col * tilesize;
            tiles[row][col].y = row * tilesize;
        }
    }
}

void Tilemap::draw() {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            std::cout << tiles[row][col].id;
        }
        std::cout << "\n";
    }
}