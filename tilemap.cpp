#include "tilemap.hpp"

Tilemap::Tilemap(int w, int h) {
    width = w;
    height = h;

    if (!font.loadFromFile("content/One Crayon.ttf")) {std::cout << "Font failed to load!" << std::endl;}

    cells = std::vector<std::vector<int>>(width, std::vector<int>(height, 1));
    old_cells = std::vector<std::vector<int>>(width, std::vector<int>(height, 1));

    tiles = std::vector<std::vector<tile>>(width, std::vector<tile>(height));

    generate_new_map();
}

void Tilemap::draw(sf::RenderWindow* window) {
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            window->draw(tiles[row][column].text);
        }
    }
}

void Tilemap::generate_new_map() {
    set_cells();
    int steps = 5;
    for (int i = 0; i < steps; ++i) {
        cellular_step();
    }
    set_tiles();
}

void Tilemap::set_tiles() {
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            tiles[row][column].x = column * tilesize;
            tiles[row][column].y = row * tilesize;
            tiles[row][column].id = cells[row][column];
            if (cells[row][column] == 0) { tiles[row][column].cavern = 0; }
            tiles[row][column].set_font(&font);
            tiles[row][column].set_text();
        }
    }
}

void Tilemap::set_cells() {
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            if (row != 0 && row != height-1 && column != 0 && column != width-1) {
                cells[row][column] = 1;
                int chance_to_die = rand() % 100 + 1;
                if (chance_to_die < 44) { cells[row][column] = 0; }
            }
        }
    }
}

void Tilemap::cellular_step() {
    old_cells = cells;
    for (int row = 1; row < height-1; ++row) {
        for (int column = 1; column < width-1; ++column) {
            int living_neighbors = count_living_neighbors(row, column);
            if (living_neighbors > 4) { cells[row][column] = 0; } else { cells[row][column] = 1; }
        }
    }
}

int Tilemap::count_living_neighbors(int r, int c) {
    int living_neighbors = 0;
    if (old_cells[r-1][c] == 1) { living_neighbors++; }
    if (old_cells[r+1][c] == 1) { living_neighbors++; }
    if (old_cells[r][c-1] == 1) { living_neighbors++; }
    if (old_cells[r][c+1] == 1) { living_neighbors++; }
    if (old_cells[r-1][c-1] == 1) { living_neighbors++; }
    if (old_cells[r+1][c+1] == 1) { living_neighbors++; }
    if (old_cells[r+1][c-1] == 1) { living_neighbors++; }
    if (old_cells[r-1][c+1] == 1) { living_neighbors++; }
    return living_neighbors;
}