#include "main.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Object.h"
Turtle::Turtle(sf::RenderWindow* window) : Object(window)
{
	this->_vx = 2.99f;
	this->_vy = 0;
	this->_pos.x = 110;
	this->_pos.y = (float)window->getSize().y / 4 - 156;
	this->_textures[0].loadFromFile("../assets/turtle1.png");
	this->_textures[1].loadFromFile("../assets/turtle2.png");
	this->_textures[2].loadFromFile("../assets/turtle3.png");
	this->_textures[3].loadFromFile("../assets/turtle4.png");
	this->_textures[4].loadFromFile("../assets/turtle5.png");
	this->_sprite.setTexture(this->_textures[0]);
	this->_sprite.setPosition(this->_pos);
	this->_heading = RIGHT;
}

void Turtle::move()
{
	static	int	walking = 0;

	if (this->_heading == RIGHT && this->_pos.x < this->_window->getSize().x)
	{
		this->_pos.x += this->_vx;
	}
	if (this->_heading == LEFT && this->_pos.x > 0)
	{
		this->_pos.x -= this->_vx;
	}
	if (this->_heading == RIGHT && this->_pos.x >= this->_window->getSize().x)
	{
		this->_sprite.scale(-1.f, 1.f);
		this->_pos.x -= this->_sprite.getGlobalBounds().width;
		this->_heading = LEFT;
	}
	if (this->_heading == LEFT && this->_pos.x <= 0)
	{
		this->_sprite.scale(-1.f, 1.f);
		this->_pos.x += this->_sprite.getGlobalBounds().width;
		this->_heading = RIGHT;
	}
	if (this->_vy == 0)
		this->_sprite.setTexture(this->_textures[(walking++ % 15) / 5]);
	
	this->setPosition(this->_pos);
	this->_window->draw(this->_sprite);
}

void Turtle::jump(bool down)
{
}
