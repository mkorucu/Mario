#include "main.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Object.h"
Turtle::Turtle(sf::RenderWindow* window) : Object(window)									//	*****************************************
{
	this->_vx = 2.99f;
	this->_vy = 0;
	this->_pos.x = 110;
	this->_pos.y = (float)window->getSize().y / 4 - 156;
	this->_textures[0].loadFromFile("../assets/turtle1.png");								//	Default Turtle Constructor
	this->_textures[1].loadFromFile("../assets/turtle2.png");								//	it sets position, velocity, heading
	this->_textures[2].loadFromFile("../assets/turtle3.png");								//	dead condition, sprite and textures
	this->_textures[3].loadFromFile("../assets/turtle4.png");
	this->_textures[4].loadFromFile("../assets/turtle5.png");
	this->_sprite.setTexture(this->_textures[0]);
	this->_sprite.setPosition(this->_pos);
	this->_heading = RIGHT;
	this->isDead = false;
	this->walking = 0;																		//	*****************************************
}

void Turtle::move()
{	
	sf::RenderStates	states;																//When printing turtle to the screen, it was supposed to print behind the pipes. 
	states.blendMode = sf::BlendMode(sf::BlendMode::DstAlpha, sf::BlendMode::Zero);			//In this way, we were able to give the effect of getting inside the pipes. The BlendMode property was used for this.

	if (this->isDead != true)
	{
		if (this->_pos.x < 105 && this->_pos.y > 865)										//	*****************************************
		{
			this->_pos.x = (float)this->_window->getSize().x - 110;							
			this->_pos.y = this->_window->getSize().y / 4.0f - 156;
		}																					//This part is the part that allows the Turtles to be teleported to the above pipe again in case of entering the pipes at the bottom.
			
		if (this->_pos.x > (this->_window->getSize().x - 105) && this->_pos.y > 865)
		{
			this->_pos.x = 110;
			this->_pos.y = this->_window->getSize().y / 4.0f - 156;
		}																					//	*****************************************

		if (this->_vy == 0)																	//This part is going up to speed of turtle's wtih respect to time.
			this->_vx = 2.99f + ((walking / 1500.0f) * 0.25);

		if (this->_heading == RIGHT && this->_pos.x <= (this->_window->getSize().x))												//	*********************************************************************
		{
			this->_pos.x += this->_vx;
		}
		if (this->_heading == LEFT && this->_pos.x >= 0)
		{
			this->_pos.x -= this->_vx;
		}
		if (this->_heading == RIGHT && (this->_pos.x + this->_sprite.getGlobalBounds().width) >= (this->_window->getSize().x))		//This part allows the turtle to move according to its direction and 
		{																															//position and change direction when necessary.
			this->_sprite.scale(-1.f, 1.f);
			this->_heading = LEFT;
		}
		if (this->_heading == LEFT && (this->_pos.x - this->_sprite.getGlobalBounds().width) <= 0)
		{
			this->_sprite.scale(-1.f, 1.f);
			this->_heading = RIGHT;
		}																															//	*********************************************************************				
		if (this->_vx != 0)
			this->_sprite.setTexture(this->_textures[(this->walking++ % 15) / 5]);								//Walking effect and changing textures of turtle is applying this part.
		if (this->_vx == 0.02f)
			this->_sprite.setTexture(this->_textures[0]);
	}
	
	this->setPosition(this->_pos);
	this->_window->draw(this->_sprite, states);
}

void Turtle::jump(bool down)
{
	if (this->isDead == true)							//If it is dead, it just going downward to out of game board.
	{
		this->_pos.y += this->_vy;
		return;
	}

	if (down == false && this->_vy == 0)				//********************************************************
	{
		this->_vy += 2.51f;
		this->_pos.y += this->_vy;
	}
	else if (down == true && this->_vy > 0)
	{													// This part is going downward for edge of bricks.
		this->_pos.y -= this->_vy;
		this->_vy = 0;
	}
	else if (down == false && this->_vy > 0)
	{
		this->_pos.y += this->_vy;
		this->_vx = 0.02f;
	}													//********************************************************
}

void Turtle::fall(void)
{
	this->_sprite.setTexture(this->_textures[4]);
	this->_vy = 5.0f;
	this->isDead = true;								// Applying death of turtle. What a sad situation :D
	this->walking = 0;
}
