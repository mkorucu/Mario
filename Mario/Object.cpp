#include "main.h"
#include "Object.h"

Object::Object(sf::RenderWindow* window)
{
	this->_window = window;
    this->isDead = false;
}

void	Object::setPosition(sf::Vector2f pos)
{
	this->_pos = pos;
    this->_sprite.setPosition(pos);
}

sf::Vector2f Object::getPosition()
{
	return (this->_pos);
}

sf::IntRect Object::boundingBox()
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


