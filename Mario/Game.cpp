#include "Game.h"

Game::Game(sf::RenderWindow& window)
{
    this->_speed = 10;
    
    if (!_floorTexture.loadFromFile("../assets/floor.png") || !_brickTexture.loadFromFile("../assets/brick.png")
        ||  !_pipesBackground[0].loadFromFile("../assets/pipes.png") || !_pipesBackground[1].loadFromFile("../assets/pipe.png"))
        return;
    this->_floor.setTexture(_floorTexture);
    this->_floor.setPosition(0, (float)window.getSize().x - 92);


    for (int i = 0; i < 7; i++)
    {
        this->_brick[i].setTexture(_brickTexture);
        this->_brickTexture.setRepeated(true);
    }
    this->_brick[0].setPosition(0, (float)window.getSize().y / 4);
    this->_brick[0].setTextureRect(sf::IntRect(0, 0, 420, 34));
    this->_brick[1].setPosition((float)window.getSize().x - 420, (float)window.getSize().y / 4);
    this->_brick[1].setTextureRect(sf::IntRect(0, 0, 420, 34));
    this->_brick[3].setPosition((float)window.getSize().x / 2 - 240, (float)window.getSize().y / 2 - 34);
    this->_brick[3].setTextureRect(sf::IntRect(0, 0, 480, 34));
    this->_brick[2].setPosition(0, (float)window.getSize().y / 2);
    this->_brick[2].setTextureRect(sf::IntRect(0, 0, 120, 34));
    this->_brick[4].setPosition((float)window.getSize().x - 120, (float)window.getSize().y / 2);
    this->_brick[4].setTextureRect(sf::IntRect(0, 0, 420, 34));
    this->_brick[5].setPosition(0, (float)window.getSize().y * 3 / 4);
    this->_brick[5].setTextureRect(sf::IntRect(0, 0, 360, 34));
    this->_brick[6].setPosition((float)window.getSize().x - 360, window.getSize().y * 3 / 4);
    this->_brick[6].setTextureRect(sf::IntRect(0, 0, 360, 34));


    this->_pipes[0].setTexture(this->_pipesBackground[0]);
    this->_pipes[0].setPosition(0, (float)window.getSize().y / 4 - 156);
    this->_pipes[1].setTexture(this->_pipesBackground[0]);
    this->_pipes[1].scale(-1.f, 1.f);
    this->_pipes[1].setPosition((float)window.getSize().x, (float)window.getSize().y / 4 - 156);
    this->_pipes[2].setTexture(this->_pipesBackground[1]);
    this->_pipes[2].scale(-1.f, 1.f);
    this->_pipes[2].setPosition(130, (float)window.getSize().y - 166);
    this->_pipes[3].setTexture(this->_pipesBackground[1]);
    this->_pipes[3].setPosition((float)window.getSize().x - 130, (float)window.getSize().y - 166);
}

void	Game::drawBackground(sf::RenderWindow& window)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int i = 0; i < 7; i++)
            window.draw(this->_brick[i]);
        for (int i = 0; i < 4; i++)
            window.draw(this->_pipes[i]);
        window.draw(this->_floor);
        window.display();
    }
}