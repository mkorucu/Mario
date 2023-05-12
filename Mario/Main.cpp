#include "main.h"

int main()
{  
    sf::err().rdbuf(NULL);
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Mario");
    Game    game(window);
    Object* objects = new Mario(&window);
    Object* turtle = new Turtle(&window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear();
        turtle->move();
        game.drawBackground(window);
        objects->move(game.onFloor(objects));
        objects->jump(game.onFloor(objects));
        turtle->jump(game.onFloor(turtle));
        window.display();
        sf::sleep(sf::milliseconds(10));
    }
    return 0;
}
