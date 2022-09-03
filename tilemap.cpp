#include "tilemap.hpp"

Tilemap::Tilemap(int w, int h) {
    width = w;
    height = h;

    if (!font.loadFromFile("content/One Crayon.ttf")) {std::cout << "Font failed to load!" << std::endl;}

    tiles = std::vector<std::vector<tile>>(width, std::vector<tile>(height));
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            tiles[row][column].x = column * tilesize;
            tiles[row][column].y = row * tilesize;
            tiles[row][column].set_text();
            tiles[row][column].set_font(&font);
        }
    }
}

void Tilemap::draw(sf::RenderWindow* window) {
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            window->draw(tiles[row][column].text);
        }
        std::cout << "\n";
    }
}