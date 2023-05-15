#include "main.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
Mario::Mario(sf::RenderWindow *window) : Object(window)																	//	*****************************************
{
	this->_pos.x = 330;
	this->_pos.y = (float)window->getSize().x - 180;
	this->_vx = 5.0f;
	this->_vy = 0;
	this->_textures[0].loadFromFile("../assets/mario1.png");
	this->_textures[1].loadFromFile("../assets/mario2.png");															//	Default Mario Constructor
	this->_textures[2].loadFromFile("../assets/mario3.png");															//	it sets position, velocity, heading
	this->_textures[3].loadFromFile("../assets/mario4.png");															//	dead condition, sprite and textures
	this->_textures[4].loadFromFile("../assets/mario5.png");
	this->_textures[5].loadFromFile("../assets/mario6.png");
	this->_textures[6].loadFromFile("../assets/mario7.png");
	this->_sprite.setTexture(this->_textures[0]);
	this->_sprite.setPosition(this->_pos);
	this->_heading = LEFT;
	this->isDead = false;
}																														//	*****************************************

void Mario::CornerChecks()																								//	*****************************************
{
	if (this->_pos.x > this->_window->getSize().x)
		this->_pos.x = this->_window->getSize().x;
	if (this->_pos.x <= 0)
		this->_pos.x = 0;
	if (this->_pos.y + this->boundingBox().height >= this->_window->getSize().y - 167)									//	This method checks if Mario goes outside
	{																													//	of the screen. Also checks if Mario
		if (this->_pos.x >= this->_window->getSize().x - 133)															//	goes through pipes
			this->_pos.x = this->_window->getSize().x - 135;
		else if (this->_pos.x <= 133)
			this->_pos.x = 135;
	}
	if (this->_pos.y >= this->_window->getSize().y / 4 - 156 && this->_pos.y <= this->_window->getSize().y / 4 - 80)
	{
		if (this->_pos.x >= this->_window->getSize().x - 197)
			this->_pos.x = this->_window->getSize().x - 200;
		else if (this->_pos.x <= 197)
			this->_pos.x = 200;
	}
}																														//	*****************************************

void	Mario::move()																									
{																								//			Mario Move Method
	static	int	walking = 0;																	//	creates walking effect													

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))				// if player presses only left arrow key:
	{
		this->_vx = 5;
		if (this->_heading == RIGHT)																					//	********************
		{
			this->_sprite.scale(-1.f, 1.f);
			this->_pos.x -= this->_sprite.getGlobalBounds().width;														// if mario faces right
			this->_heading = LEFT;
			return;
		}																												//	*********************
		else
			this->_pos.x -= this->_vx;															// if mario faces already left
		if (this->_vy == 0)
			this->_sprite.setTexture(this->_textures[(walking++ % 15) / 5 + 1]);				//	walking effect
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
	|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))))				//	if player presses both keys or neither keys
	{																									//*****************************
		this->_vx -= 0.5;
		this->_pos.x += this->_heading * this->_vx;														// creates sliding effect
		this->_sprite.setTexture(this->_textures[4]);
	}																									//*****************************
	if (this->_vx == 0 && this->_vy == 0)
		this->_sprite.setTexture(this->_textures[0]);													// standing still effect
	this->setPosition(this->_pos);
	this->_window->draw(this->_sprite);
}																															//	*****************************************


void	Mario::jump(bool down)
{
	float	a = 1.0f;

	if (this->isDead == true)															//	****************
	{																					//	checks if mario
		this->_pos.y += this->_vy;														//	is dead
		return;																			//	****************
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->_vy == 0)					//	****************
	{																					//	if player presses
		this->_sprite.setTexture(this->_textures[5]);	// jumping texture				//	up arrow key and
		this->_vy = -27.5f;								// vertical speed				//	no vertical speed
	}																					//	****************
	this->_vy += 1.0001f;								// decreasing horizontal speed
	if (down == false && this->_vy < 0)					
		this->_pos.y += this->_vy;
	else if (down == true && this->_vy < 0)				// if mario hits a brick above him
	{
		this->_pos.y -= this->_vy;							//	goes 1 step 1
		this->_vy = 0.0001f;								//	changes speed back to positive
	}
	else if (down == false && this->_vy > 0)			//	if mario doesnt hit any brick when jumping
		this->_pos.y += this->_vy;						//	keeps decreasing position
	else if (down == true && this->_vy > 0)				//	if mario hits a ground below him
	{
		this->_pos.y -= this->_vy;						//	goes 1 step back
		this->_vy = 0;									//	resets vertical speed
	}
	else if (down == false && this->_vy == 0)			//	if mario free fall from a brick
	{
		this->_vy += 1.01f;
		this->_pos.y += this->_vy;
	}
	this->CornerChecks();								//	checks corners

}

void Mario::fall(void)									// mario falls when he dies
{
	this->_sprite.setTexture(this->_textures[6]);
	this->_vy = 5.0f;
	this->isDead = true;
}
