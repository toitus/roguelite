#include "tilemap.hpp"

Tilemap::Tilemap(int w, int h) {
    width = w;
    height = h;

    if (!font.loadFromFile("content/One Crayon.ttf")) { std::cout << "Font failed to load!" << std::endl; }
    if (!tilesheet.loadFromFile("content/tilesheet.png")) { std::cout << "Tilemap's tilesheet failed to load!" << std::endl; }
    tilesheet.setSmooth(true);

    cells = std::vector<std::vector<int>>(width, std::vector<int>(height, 1));
    old_cells = std::vector<std::vector<int>>(width, std::vector<int>(height, 1));

    tiles = std::vector<std::vector<Tile>>(width, std::vector<Tile>(height));

    generate_new_map();
}

void Tilemap::draw(sf::RenderWindow* w) {
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            tiles[row][column].draw(w);
        }
    }
}

void Tilemap::generate_new_map() {
    cavern_count = 1;
    caverns.clear();
    set_cells();
    int steps = 5;
    for (int i = 0; i < steps; ++i) {
        cellular_step();
    }
    identify_tiles();
    identify_inner_walls();
    identify_caverns();
    identify_tile_textures();
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

void Tilemap::identify_inner_walls() {
    for (int row = 1; row < height-1; ++row) {
        for (int column = 1; column < width-1; ++column) {
            if (tiles[row][column].get_id() != 0) {
                int count = 0;
                if (tiles[row-1][column].get_id() == 0) { count++; }
                if (tiles[row+1][column].get_id() == 0) { count++; }
                if (tiles[row][column-1].get_id() == 0) { count++; }
                if (tiles[row][column+1].get_id() == 0) { count++; }
                if (tiles[row-1][column-1].get_id() == 0) { count++; }
                if (tiles[row+1][column+1].get_id() == 0) { count++; }
                if (tiles[row+1][column-1].get_id() == 0) { count++; }
                if (tiles[row-1][column+1].get_id() == 0) { count++; }
                if (count == 0) { tiles[row][column].set_id(2); }
            }
        }
    }
}


void Tilemap::identify_tiles() {
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            tiles[row][column].set_position(row, column);
            tiles[row][column].set_id(cells[row][column]);
            if (cells[row][column] == 0) { tiles[row][column].set_cavern(0); }
        }
    }
}

void Tilemap::identify_caverns() {
    for (int row = 1; row < height-1; ++row) {
        for (int column = 1; column < width-1; ++column) {
            if (tiles[row][column].get_cavern() == 0) {
                caverns.push_back(fill_cavern(row, column));
            }
        }
    }
}

std::vector<sf::Vector2i> Tilemap::fill_cavern(int r, int c) {
    std::vector<sf::Vector2i> queue;
    std::vector<sf::Vector2i> cavern;

    queue.push_back(sf::Vector2i(r, c));
    while (queue.size() > 0) {
        sf::Vector2i temp = queue[0];
        queue.erase(queue.begin());
        if (tiles[temp.x][temp.y].get_cavern() == 0) {
            tiles[temp.x][temp.y].set_cavern(cavern_count);
            cavern.push_back(temp);
            if (tiles[temp.x-1][temp.y].get_cavern() == 0) { queue.push_back(sf::Vector2i(temp.x-1, temp.y)); }
            if (tiles[temp.x+1][temp.y].get_cavern() == 0) { queue.push_back(sf::Vector2i(temp.x+1, temp.y)); }
            if (tiles[temp.x][temp.y-1].get_cavern() == 0) { queue.push_back(sf::Vector2i(temp.x, temp.y-1)); }
            if (tiles[temp.x][temp.y+1].get_cavern() == 0) { queue.push_back(sf::Vector2i(temp.x, temp.y+1)); }
            if (tiles[temp.x-1][temp.y-1].get_cavern() == 0) { queue.push_back(sf::Vector2i(temp.x-1, temp.y-1)); }
            if (tiles[temp.x+1][temp.y+1].get_cavern() == 0) { queue.push_back(sf::Vector2i(temp.x+1, temp.y+1)); }
            if (tiles[temp.x+1][temp.y-1].get_cavern() == 0) { queue.push_back(sf::Vector2i(temp.x+1, temp.y-1)); }
            if (tiles[temp.x-1][temp.y+1].get_cavern() == 0) { queue.push_back(sf::Vector2i(temp.x-1, temp.y+1)); }
        }
    }
    cavern_count++;
    return cavern;
}

void Tilemap::identify_tile_textures() {
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            if (tiles[row][column].get_id() == 0) { tiles[row][column].set_texture(&tilesheet, floor); }
            if (tiles[row][column].get_id() == 1) { tiles[row][column].set_texture(&tilesheet, outer_wall); }
            if (tiles[row][column].get_id() == 2) { tiles[row][column].set_texture(&tilesheet, inner_wall); }
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