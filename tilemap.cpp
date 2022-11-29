#include "tilemap.hpp"

Tilemap::Tilemap() {
    tiles = std::vector<std::vector<Tile>>(map_rows, std::vector<Tile>(map_columns));
}

void Tilemap::initialize() {
    if (tilemap_font.loadFromFile("content/tilemap_font.ttf")) { 
        for (int r = 0; r < map_rows; ++r) {
            for (int c = 0; c < map_columns; ++c) {
                tiles[r][c].string.setFont(tilemap_font);
                tiles[r][c].string.setCharacterSize(tilesize);
            }  
        }
        generate_cellular_cave();
    } else { std::cout << "tilemap font failed to load" << std::endl; }
}

void Tilemap::events(sf::Event* e) {
    if (e->type == sf::Event::KeyPressed) { 
        if (e->key.code == sf::Keyboard::F) { fog_enabled = !fog_enabled; } //testing
    }
}

void Tilemap::update(sf::Vector2i player_pos) {
    player_position = player_pos;
}

void Tilemap::draw(sf::RenderWindow* w) {
    for (int r = 0; r < map_rows; ++r) {
        for (int c = 0; c < map_columns; ++c) {
            if (fog_enabled) {
                sf::Vector2i difference = player_position - sf::Vector2i(r, c);
                int length = (difference.x * difference.x) + (difference.y * difference.y);
                if (length < fog_radius) { w->draw(tiles[r][c].string); }
            } else { 
                w->draw(tiles[r][c].string); 
            }
        }
    }
}

void Tilemap::occupy(int r, int c) {
    tiles[r][c].walkable = false;
}

void Tilemap::evacuate(int r, int c) {
    tiles[r][c].walkable = true;
}

bool Tilemap::is_tile_walkable(int r, int c) {
    return tiles[r][c].walkable;
}

void Tilemap::generate_cellular_cave() {
    std::vector<std::vector<int>> cells(map_rows, std::vector<int>(map_columns, 1));
    std::vector<std::vector<int>> old_cells(map_rows, std::vector<int>(map_columns, 1));

    caverns.clear();
    map_caverns = 1;

    //initializing cells
    for (int r = 1; r < map_rows-1; ++r) {
        for (int c = 1; c < map_columns-1; ++c) {
            int death_chance = rand() % 100;
            if (death_chance < 43) {
                cells[r][c] = 0;
            }
        }
    }

    //cellular steps
    for (int s = 0; s < 5; ++s) {
        old_cells = cells;
        for (int r = 1; r < map_rows-1; ++r) {
            for (int c = 1; c < map_columns-1; ++c) {
                int living_neighbors = 0;
                if (old_cells[r-1][c] == 1) living_neighbors++;
                if (old_cells[r+1][c] == 1) living_neighbors++;
                if (old_cells[r][c-1] == 1) living_neighbors++;
                if (old_cells[r][c+1] == 1) living_neighbors++;
                if (old_cells[r-1][c-1] == 1) living_neighbors++;
                if (old_cells[r+1][c+1] == 1) living_neighbors++;
                if (old_cells[r+1][c-1] == 1) living_neighbors++;
                if (old_cells[r-1][c+1] == 1) living_neighbors++;
                if (living_neighbors > 4) cells[r][c] = 0;
                else cells[r][c] = 1;
            }
        }
    }

    //set tile text, position, and initial cavern id to prep flood fill process
    for (int r = 0; r < map_rows; ++r) {
        for (int c = 0; c < map_columns; ++c) {

            if (cells[r][c] == 0) {
                tiles[r][c].string.setString(" ");
                tiles[r][c].walkable = true;
                tiles[r][c].cavern = 0;
            }

            if (cells[r][c] == 1) {
                tiles[r][c].cavern = -1;
                tiles[r][c].walkable = false;
                if (r == 0 || r == map_rows-1 || c == 0 || c == map_columns-1) {
                    tiles[r][c].string.setString("#");
                    tiles[r][c].string.setStyle(sf::Text::Bold);
                    tiles[r][c].string.setFillColor(sf::Color(189, 154, 122));
                } else { 
                    if (cells[r-1][c-1] == 0 || cells[r-1][c] == 0 || cells[r-1][c+1] == 0 || cells[r][c-1] == 0 || 
                        cells[r][c+1] == 0 || cells[r+1][c-1] == 0 || cells[r+1][c] == 0 || cells[r+1][c+1] == 0 ) {
                        tiles[r][c].string.setString("#");
                        tiles[r][c].string.setFillColor(sf::Color(189, 154, 122));
                    } else {
                        tiles[r][c].string.setString("#");
                        tiles[r][c].string.setFillColor(sf::Color(103, 71, 54));
                    }
                }
            }

            center_tile_text(r, c);

        }
    }

    //flood flill caverns to populate caverns vector
    for (int r = 0; r < map_rows; ++r) {
        for (int c = 0; c < map_columns; ++c) {
            if (tiles[r][c].cavern == 0) {
                caverns.push_back(flood_cavern(r, c));
            }
        }
    }

    randomize_entrance_and_exit();

}

//flood fill algorithm for identifying unconnected cavern sections of the map
std::vector<sf::Vector2i> Tilemap::flood_cavern(int r, int c) {
    std::vector<sf::Vector2i> queue;
    std::vector<sf::Vector2i> cavern;

    queue.push_back(sf::Vector2i(r, c));
    while (queue.size() > 0) {
        sf::Vector2i temp = queue[0];
        queue.erase(queue.begin());
        if (tiles[temp.x][temp.y].cavern == 0) {
            tiles[temp.x][temp.y].cavern = map_caverns;
            cavern.push_back(temp);
            if (tiles[temp.x-1][temp.y].cavern == 0) { queue.push_back(sf::Vector2i(temp.x-1, temp.y)); }
            if (tiles[temp.x+1][temp.y].cavern == 0) { queue.push_back(sf::Vector2i(temp.x+1, temp.y)); }
            if (tiles[temp.x][temp.y-1].cavern == 0) { queue.push_back(sf::Vector2i(temp.x, temp.y-1)); }
            if (tiles[temp.x][temp.y+1].cavern == 0) { queue.push_back(sf::Vector2i(temp.x, temp.y+1)); }
            if (tiles[temp.x-1][temp.y-1].cavern == 0) { queue.push_back(sf::Vector2i(temp.x-1, temp.y-1)); }
            if (tiles[temp.x+1][temp.y+1].cavern == 0) { queue.push_back(sf::Vector2i(temp.x+1, temp.y+1)); }
            if (tiles[temp.x+1][temp.y-1].cavern == 0) { queue.push_back(sf::Vector2i(temp.x+1, temp.y-1)); }
            if (tiles[temp.x-1][temp.y+1].cavern == 0) { queue.push_back(sf::Vector2i(temp.x-1, temp.y+1)); }
        }
    }
    map_caverns++;
    return cavern;
}

//centers text inside its tile
void Tilemap::center_tile_text(int r, int c) { 

    sf::Vector2f half_text_size = sf::Vector2f(
        tiles[r][c].string.getGlobalBounds().width/2, tiles[r][c].string.getGlobalBounds().height/2
    );

    sf::Vector2f local_text_position = sf::Vector2f(
        tiles[r][c].string.getLocalBounds().left, tiles[r][c].string.getLocalBounds().top
    );

    tiles[r][c].string.setOrigin(half_text_size + local_text_position);
    tiles[r][c].string.setPosition(c*tilesize + tilesize/2, r*tilesize + tilesize/2);
}

void Tilemap::randomize_entrance_and_exit() {
    //the entrance and the exit of the cave will always be inside the largest cavern
    int largest_cavern_index = 0;
    for (int i = 0; i < caverns.size(); ++i) {
        int current_cavern_size = caverns[i].size();
        if (current_cavern_size > caverns[largest_cavern_index].size()) {
            largest_cavern_index = i;
        }
    }

    int random_entrance_index = rand() % caverns[largest_cavern_index].size();
    int random_exit_index = rand() % caverns[largest_cavern_index].size();
    map_entrance = caverns[largest_cavern_index][random_entrance_index];
    map_exit = caverns[largest_cavern_index][random_exit_index];

    tiles[map_exit.x][map_exit.y].string.setString("E");
    tiles[map_exit.x][map_exit.y].string.setCharacterSize(32);
    tiles[map_exit.x][map_exit.y].string.setFillColor(sf::Color::White);
    center_tile_text(map_exit.x, map_exit.y);
}