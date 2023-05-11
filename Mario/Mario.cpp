#include "main.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
Mario::Mario(sf::RenderWindow *window) : Object(window)
{
	this->_pos.x = 330;
	this->_pos.y = (float)window->getSize().x - 180;
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
	this->_sprite.setPosition(this->_pos);
	this->_heading = LEFT;
}

void	Mario::move()
{
	float	a = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (this->_heading == RIGHT)
		{
			this->_sprite.scale(-1.f, 1.f);
			this->_pos.x -= this->_sprite.getGlobalBounds().width;
			this->_heading = LEFT;
		}
		else
			this->_pos.x -= this->_vx;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (this->_heading == LEFT)
		{
			this->_sprite.scale(-1.f, 1.f);
			this->_pos.x += this->_sprite.getGlobalBounds().width;
			this->_heading = RIGHT;
		}
		else
			this->_pos.x += this->_vx;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->_pos.y -= this->_vy;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->_pos.y += this->_vy;
	this->setPosition(this->_pos);
	this->_window->draw(this->_sprite);
}