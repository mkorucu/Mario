#pragma once
#include "main.h"

class Object
{
protected:
	sf::Texture _textures[8];
	sf::Sprite _sprite;
	sf::Vector2f _pos;
	sf::RenderWindow* _window;
	int	_state;
	int	_heading;
public:
	Object(sf::RenderWindow* window);
	void	setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	sf::IntRect boundingBox();
	virtual void move(bool down) = 0;
	//virtual void fall(void) = 0;
	virtual void jump(bool down) = 0;
};

