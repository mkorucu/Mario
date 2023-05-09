#include "Mario.h"

Mario::Mario(sf::RenderWindow *window) : Object(window)
{
	sf::Vector2f pos;
	pos.x = 0;
	pos.y = (float)window->getSize().x - 180;
	this->_vx = 5.0f;
	this->_vy = 5.0f;
	this->_textures[0].loadFromFile("../assets/mario1.png");
	this->_textures[1].loadFromFile("../assets/mario2.png");
	this->_textures[2].loadFromFile("../assets/mario3.png");
	this->_textures[3].loadFromFile("../assets/mario4.png");
	this->_textures[4].loadFromFile("../assets/mario5.png");
	this->_textures[5].loadFromFile("../assets/mario6.png");
	this->_textures[6].loadFromFile("../assets/mario7.png");
	this->_sprite.setTexture(this->_textures[0]);
	this->setPosition(pos);
}

void	Mario::move()
{
	sf::Vector2f pos = this->_pos;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		
        pos.x -= this->_vx;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		pos.x += this->_vx;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		pos.y -= this->_vy;
}