#include "Game.h"

Game::Game()
{
    this->_speed = 10;
}

void	Game::drawBackground(sf::RenderWindow& window)
{
    sf::Texture floorTexture, brickTexture, pipeTexture, pipesTexture;

    if (!floorTexture.loadFromFile("../assets/floor.png") || !brickTexture.loadFromFile("../assets/brick.png")) // Replace "texture.png" with your actual texture file path
        return ;
    sf::Sprite floorSprite(floorTexture);
    sf::Sprite brickSprite(brickTexture);
    floorSprite.setPosition(0, 768 - 62); // Set the position of the sprite at the bottom
    brickSprite.setPosition(0, 384);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(floorSprite);
        window.draw(brickSprite);
        window.display();
    }
}