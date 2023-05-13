#include "main.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
Mario::Mario(sf::RenderWindow *window) : Object(window)
{
	this->_pos.x = 330;
	this->_pos.y = (float)window->getSize().x - 180;
	this->_vx = 5.0f;
	this->_vy = 0;
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
	static	int	walking = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->_vx = 5;
		if (this->_heading == RIGHT)
		{
			this->_sprite.scale(-1.f, 1.f);
			this->_pos.x -= this->_sprite.getGlobalBounds().width;
			this->_heading = LEFT;
			return;
		}
		else
			this->_pos.x -= this->_vx;
		if (this->_pos.x <= 0)
			this->_pos.x = 0;
		if (this->_vy == 0)
			this->_sprite.setTexture(this->_textures[(walking++ % 15) / 5 + 1]);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->_vx = 5;
		if (this->_heading == LEFT)
		{
			this->_sprite.scale(-1.f, 1.f);
			this->_pos.x += this->_sprite.getGlobalBounds().width;
			this->_heading = RIGHT;
			return ;
		}
		else
			this->_pos.x += this->_vx;
		if (this->_vy == 0)
			this->_sprite.setTexture(this->_textures[(walking++ % 15) / 5 + 1]);
	}
	if (this->_vy == 0  && this->_vx != 0 && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))))
	{
		this->_vx -= 0.5;
		this->_pos.x += this->_heading * this->_vx;
		this->_sprite.setTexture(this->_textures[4]);
	}
	if (this->_vx == 0 && this->_vy == 0)
		this->_sprite.setTexture(this->_textures[0]);
	if (this->_pos.x > this->_window->getSize().x)
		this->_pos.x = this->_window->getSize().x;
	if (this->_pos.x <= 0)
		this->_pos.x = 0;
	this->setPosition(this->_pos);
}


void	Mario::jump(bool down)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->_vy == 0)
	{
		this->_sprite.setTexture(this->_textures[5]);
		this->_vy = -25.0f;
	}
	if (down == true && this->_vy == -25) // yerde, yükselecek;
		this->_pos.y += this->_vy;
	else if (down == false && this->_vy < 0) //havada, yükseliyor
		this->_pos.y += this->_vy;
	else if (down == true && this->_vy < 0) // havada, yükseliyor, çarptı
	{
		this->_pos.x -= this->_vx * this->_heading;
		this->_pos.y -= this->_vy;
		this->_vy = 0.0001f;
	}
	else if (down == false && this->_vy > 0)
		this->_pos.y += this->_vy;
	else if (down == true && this->_vy > 0)
	{
		this->_pos.y -= this->_vy;
		this->_vy = 0;
	}
	else if (down == false && this->_vy == 0)
	{
		this->_vy += 1.01f;
		this->_pos.y += this->_vy;
	}
	if (this->_vy != 0)
		this->_vy += 1.0001f;
}
