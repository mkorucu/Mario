#include "main.h"
#include "Object.h"

Object::Object(sf::RenderWindow* window)        //  ***************************************************************
{
	this->_window = window;                     //Object Constuctor sets window pointer and death control variable
	this->isDead = false;
}                                               //  ***************************************************************

void	Object::setPosition(sf::Vector2f pos)	//	***************************************************************
{
	this->_pos = pos;							//	This method sets position of the object to the given argument 
	this->_sprite.setPosition(pos);
}												//	***************************************************************

sf::Vector2f Object::getPosition()				//	A get function for position
{
	return (this->_pos);
}

sf::IntRect Object::boundingBox()				//	Returns global bounding box of the sprite as integer rectangle
{
	sf::IntRect bounds;
	sf::FloatRect localBounds = this->_sprite.getGlobalBounds();    
	bounds.left = static_cast<int>(localBounds.left);
	bounds.top = static_cast<int>(localBounds.top);
	bounds.width = static_cast<int>(localBounds.width);
	bounds.height = static_cast<int>(localBounds.height);
	return bounds;
}

bool Object::getIsDead()
{
	return this->isDead;
}


