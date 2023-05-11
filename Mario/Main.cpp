#include "main.h"

int main()
{
    
    sf::err().rdbuf(NULL);
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Mario");
    Game    game(window);
    Mario mario(&window);
    Object* objects = &mario;
         while (window.isOpen())
     {
         sf::Event event;
         while (window.pollEvent(event))
             if (event.type == sf::Event::Closed)
                 window.close();
        window.clear(); 
        
        game.drawBackground(window);
     }
    return 0;
}
