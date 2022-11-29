#include <SFML/Graphics.hpp>

#include <stdlib.h>
#include <time.h>

#include "game.hpp"

int main() {

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1600, 900, sf::VideoMode::getDesktopMode().bitsPerPixel), "Roguelite");

    Game game (&window);

    game.run();

    return 0;
}