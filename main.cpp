#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "game.hpp"

int main() {

    srand(time(NULL));
    
    sf::RenderWindow window(sf::VideoMode(1024, 768, sf::VideoMode::getDesktopMode().bitsPerPixel), "roguelite");

    Game roguelite(&window);
    roguelite.run();

    return 0;

}