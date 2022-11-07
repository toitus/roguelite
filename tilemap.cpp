#include "tilemap.hpp"

Tilemap::Tilemap() {
    tiles = std::vector<std::vector<std::pair<sf::Text, bool>>>(map_rows, std::vector<std::pair<sf::Text, bool>>(map_columns));
    cavern_ids = std::vector<std::vector<int>>(map_rows, std::vector<int>(map_columns));
}

void Tilemap::initialize() {
    if (tilemap_font.loadFromFile("content/tilemap_font.ttf")) { 
        for (int r = 0; r < map_rows; ++r) {
            for (int c = 0; c < map_columns; ++c) {
                tiles[r][c].first.setFont(tilemap_font);
                tiles[r][c].first.setCharacterSize(tilesize);
                tiles[r][c].second = false;
            }  
        }
    } else { std::cout << "tilemap font failed to load" << std::endl; }
}

void Tilemap::events(sf::Event* e) {
    if (e->type == sf::Event::KeyPressed) { 
        if (e->key.code == sf::Keyboard::F) { fog_enabled = !fog_enabled; } //for testing
    }
}

void Tilemap::update(sf::Vector2f player_center) {
    fog_center = player_center;
}

void Tilemap::draw(sf::RenderWindow* w) {
    for (int r = 0; r < map_rows; ++r) {
        for (int c = 0; c < map_columns; ++c) {
            if (fog_enabled) {
                sf::Vector2f tile_center = tiles[r][c].first.getPosition();
                sf::Vector2f difference = fog_center - tile_center;
                float length = sqrt(pow(difference.x, 2) + pow(difference.y, 2));
                if (length < fog_radius) { w->draw(tiles[r][c].first); }
            } else { w->draw(tiles[r][c].first); }
        }
    }
}

void Tilemap::occupy(int r, int c) {
    tiles[r][c].second = false;
    //std::cout << "occupying " << r << " " << c << std::endl;
}

void Tilemap::evacuate(int r, int c) {
    tiles[r][c].second = true;
    //std::cout << "evacuating " << r << " " << c << std::endl;
}

bool Tilemap::is_walkable(int r, int c) {
    return tiles[r][c].second;
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
                tiles[r][c].first.setString(" ");
                tiles[r][c].second = true;
                cavern_ids[r][c] = 0;
            }

            if (cells[r][c] == 1) {
                cavern_ids[r][c] = -1;
                tiles[r][c].second = false;
                if (r == 0 || r == map_rows-1 || c == 0 || c == map_columns-1) {
                    tiles[r][c].first.setString("#");
                    tiles[r][c].first.setStyle(sf::Text::Bold);
                    tiles[r][c].first.setFillColor(sf::Color(189, 154, 122));
                } else { 
                    if (cells[r-1][c-1] == 0 || cells[r-1][c] == 0 || cells[r-1][c+1] == 0 || cells[r][c-1] == 0 || 
                        cells[r][c+1] == 0 || cells[r+1][c-1] == 0 || cells[r+1][c] == 0 || cells[r+1][c+1] == 0 ) {
                        tiles[r][c].first.setString("#");
                        tiles[r][c].first.setFillColor(sf::Color(189, 154, 122));
                    } else {
                        tiles[r][c].first.setString("#");
                        tiles[r][c].first.setFillColor(sf::Color(103, 71, 54));
                    }
                }
            }

            //centers text inside its tile
            sf::Vector2f half_text_size = sf::Vector2f(
                tiles[r][c].first.getGlobalBounds().width/2, tiles[r][c].first.getGlobalBounds().height/2
            );

            sf::Vector2f local_text_position = sf::Vector2f(
                tiles[r][c].first.getLocalBounds().left, tiles[r][c].first.getLocalBounds().top
            );

            tiles[r][c].first.setOrigin(half_text_size + local_text_position);

            tiles[r][c].first.setPosition(c*tilesize + tilesize/2, r*tilesize + tilesize/2);

        }
    }

    //flood flill caverns to populate caverns vector
    for (int r = 1; r < map_rows-1; ++r) {
        for (int c = 1; c < map_columns; ++c) {
            if (cavern_ids[r][c] == 0) {
                caverns.push_back(flood_cavern(r, c));
            }
        }
    }

}

//flood fill algorithm for identifying unconnected cavern sections of the map
std::vector<sf::Vector2i> Tilemap::flood_cavern(int r, int c) {
    std::vector<sf::Vector2i> queue;
    std::vector<sf::Vector2i> cavern;

    queue.push_back(sf::Vector2i(r, c));
    while (queue.size() > 0) {
        sf::Vector2i temp = queue[0];
        queue.erase(queue.begin());
        if (cavern_ids[temp.x][temp.y] == 0) {
            cavern_ids[temp.x][temp.y] = map_caverns;
            cavern.push_back(temp);
            if (cavern_ids[temp.x-1][temp.y] == 0) { queue.push_back(sf::Vector2i(temp.x-1, temp.y)); }
            if (cavern_ids[temp.x+1][temp.y] == 0) { queue.push_back(sf::Vector2i(temp.x+1, temp.y)); }
            if (cavern_ids[temp.x][temp.y-1] == 0) { queue.push_back(sf::Vector2i(temp.x, temp.y-1)); }
            if (cavern_ids[temp.x][temp.y+1] == 0) { queue.push_back(sf::Vector2i(temp.x, temp.y+1)); }
            if (cavern_ids[temp.x-1][temp.y-1] == 0) { queue.push_back(sf::Vector2i(temp.x-1, temp.y-1)); }
            if (cavern_ids[temp.x+1][temp.y+1] == 0) { queue.push_back(sf::Vector2i(temp.x+1, temp.y+1)); }
            if (cavern_ids[temp.x+1][temp.y-1] == 0) { queue.push_back(sf::Vector2i(temp.x+1, temp.y-1)); }
            if (cavern_ids[temp.x-1][temp.y+1] == 0) { queue.push_back(sf::Vector2i(temp.x-1, temp.y+1)); }
        }
    }
    map_caverns++;
    return cavern;
}
