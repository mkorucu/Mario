#pragma once
#include "main.h"
class Object
{
protected:
	sf::Texture _textures[8];
	sf::Sprite _sprite;
	sf::Vector2f _pos;
	sf::RenderWindow* _window;
	int	_heading;
	bool	isDead;
	int	walking;
public:
	Object(sf::RenderWindow* window);
	void	setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	sf::IntRect boundingBox();
	bool	getIsDead();
	virtual void move(void) = 0;
	virtual void fall(void) = 0;
	virtual void jump(bool down) = 0;
};

