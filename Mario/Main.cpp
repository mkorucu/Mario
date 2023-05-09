#include "main.h"




int main()
{
    sf::err().rdbuf(NULL);
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML Window");
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/floor.png")) // Replace "texture.png" with your actual texture file path
        return -1;
    sf::Sprite sprite(texture);
    sprite.setPosition(0, 768 - 62); // Set the position of the sprite at the bottom

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
