#include "main.h"

int main()
{  
    sf::err().rdbuf(NULL);
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Mario");
    Game    game(window);
    Object* objects = new Mario(&window);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear();
        game.drawBackground(window);
        objects->move();
        objects->jump(game.onFloor(objects));
        window.display();
        sf::sleep(sf::milliseconds(10));
    }
    return 0;
}
