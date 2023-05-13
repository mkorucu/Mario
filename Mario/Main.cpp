#include "main.h"

int main()
{  
    sf::err().rdbuf(NULL);
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Mario");
    Game    game(window);
    ScoreBoard board(&window);
    Mario* objects = new Mario(&window);
    Turtle* turtle = new Turtle(&window);
    int test = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear();
        turtle->move();
        game.drawBackground(window);
        board.setScore(test);
        objects->move();
        objects->jump(game.onFloor(objects));
        turtle->jump(game.onFloor(turtle));
        game.checkCollusion(turtle, objects, test);
        window.display();
        sf::sleep(sf::milliseconds(10));
    }
    return 0;
}
