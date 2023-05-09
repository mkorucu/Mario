#include "main.h"

int main()
{
    
    sf::err().rdbuf(NULL);
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Mario");
    Game    game();
    game.drawBackground(window);
    
    return 0;
}
