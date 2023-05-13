#include "main.h"
#include "Game.h"

Game::Game(sf::RenderWindow& window)
{
	this->_speed = 10;
	this->setBackground(window);
}

void    Game::setBackground(sf::RenderWindow& window)
{
		
	if (!_floorTexture.loadFromFile("../assets/floor.png") || !_brickTexture.loadFromFile("../assets/brick.png")
		||  !_pipesBackground[0].loadFromFile("../assets/pipes.png") || !_pipesBackground[1].loadFromFile("../assets/pipe.png"))
		return;
	this->_floor.setTexture(_floorTexture);
	this->_floor.setPosition(0, (float)window.getSize().x - 93);
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
	this->_brick[6].setPosition((float)window.getSize().x - 360, (float)window.getSize().y * 3 / 4);
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

bool Game::onFloor(Object *obj)
{
    if (obj->boundingBox().intersects(static_cast<sf::IntRect>(this->_floor.getGlobalBounds())))
    {
        //std::cout << "intersects floor" << std::endl;
        return (true);
    }
    for(int i = 0; i < 7; i++)
        if (obj->boundingBox().intersects(static_cast<sf::IntRect>(this->_brick[i].getGlobalBounds())))
        {
            //std::cout << "intersects brick " << i << std::endl;
	        return true;
        }
    for(int i = 0; i < 4; i++)
        if (obj->boundingBox().intersects(static_cast<sf::IntRect>(this->_pipes[i].getGlobalBounds())))
        {
            if (obj->boundingBox().width == 68)     //turtle i pipe ile intersect engellemesini kaldir !
                return false;                       //turtle pipe a degmesi engellendi
            //std::cout << "intersects pipe " << i << std::endl;
            return true;
        }
    return (false);
}

void Game::drawBackground(sf::RenderWindow &window)
{
    sf::RenderStates    states;
    states.blendMode = sf::BlendMode(sf::BlendMode::SrcAlpha, sf::BlendMode::OneMinusSrcAlpha);

    for (int i = 0; i < 7; i++)
        window.draw(this->_brick[i]);
    for (int i = 0; i < 4; i++)
        window.draw(this->_pipes[i],states);
    window.draw(this->_floor);
}

bool Game::checkCollusion(Turtle* t, Mario* m, int& side)
{
    if (t->getIsDead() || m->getIsDead())
        return false;

    if (t->boundingBox().intersects(m->boundingBox()))
    {
        std::cout << "collision start" << std::endl;
        //((m->boundingBox().top + m->boundingBox().height) > t->boundingBox().top) && ((m->boundingBox().top + m->boundingBox().height) < ((t->boundingBox().top + t->boundingBox().height) / 2))
        if ((m->getPosition().y + 65 < (t->getPosition().y + (t->boundingBox().height / 2.0f)))) //&& (m->boundingBox().left > t->boundingBox().left) && ((m->boundingBox().left + m->boundingBox().width) < (t->boundingBox().left + t->boundingBox().width))
        {
            t->fall();
            return true;
        }
        else
        {
            m->fall();
            return true;
        }
    }
    return false;
}