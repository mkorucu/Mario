﻿#include "main.h"

int main()
{
    
    sf::err().rdbuf(NULL);
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Mario");
    Game    game(window);
    Object  *characher = new Mario(&window);
    
    game.drawBackground(window);
    return 0;
}
