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
	this->isDead = false;
}

void Turtle::move()
{
	static	int	walking = 0;
	sf::RenderStates	states;				//turtle i yazdirirken pipelarin arkasina saklamak icin kullandim
	states.blendMode = sf::BlendMode(sf::BlendMode::DstAlpha, sf::BlendMode::Zero);

	if (this->isDead != true)
	{
		if (this->_pos.x < 105 && this->_pos.y > 865)
		{
			this->_pos.x = (float)this->_window->getSize().x - 110;
			this->_pos.y = this->_window->getSize().y / 4.0f - 156;
		}

		if (this->_pos.x > (this->_window->getSize().x - 105) && this->_pos.y > 865)
		{
			this->_pos.x = 110;
			this->_pos.y = this->_window->getSize().y / 4.0f - 156;
		}

		if (this->_vy == 0)
			this->_vx = 2.99f + ((walking / 1500.0f) * 0.25);

		if (this->_heading == RIGHT && this->_pos.x <= (this->_window->getSize().x))
		{
			this->_pos.x += this->_vx;
		}
		if (this->_heading == LEFT && this->_pos.x >= 0)
		{
			this->_pos.x -= this->_vx;
		}
		if (this->_heading == RIGHT && (this->_pos.x + this->_sprite.getGlobalBounds().width) >= (this->_window->getSize().x))
		{
			this->_sprite.scale(-1.f, 1.f);
			//this->_pos.x -= this->_sprite.getGlobalBounds().width;
			this->_heading = LEFT;
		}
		if (this->_heading == LEFT && (this->_pos.x - this->_sprite.getGlobalBounds().width) <= 0)
		{
			this->_sprite.scale(-1.f, 1.f);
			//this->_pos.x += this->_sprite.getGlobalBounds().width;
			this->_heading = RIGHT;
		}
		if (this->_vx != 0)
			this->_sprite.setTexture(this->_textures[(walking++ % 15) / 5]);
		if (this->_vx == 0.02f)
			this->_sprite.setTexture(this->_textures[0]);
	}
	
	this->setPosition(this->_pos);
	//std::cout << this->_pos.x << " " << this->_pos.y << "\n";
	this->_window->draw(this->_sprite, states);
}

void Turtle::jump(bool down)
{
	if (this->isDead == true)
	{
		this->_pos.y += this->_vy;
		return;
	}

	if (down == false && this->_vy == 0)
	{
		this->_vy += 2.51f;
		this->_pos.y += this->_vy;
	}
	else if (down == true && this->_vy > 0)
	{
		this->_pos.y -= this->_vy;
		this->_vy = 0;
	}
	else if (down == false && this->_vy > 0)
	{
		this->_pos.y += this->_vy;
		this->_vx = 0.02f;
	}
}

void Turtle::fall(void)
{
	this->_sprite.setTexture(this->_textures[4]);
	this->_vy = 5.0f;
	this->isDead = true;
}
