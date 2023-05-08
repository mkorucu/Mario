#pragma once
#include "main.h"
class Object
{
private:
	sf::Texture textures[8];
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::RenderWindow* window;
	int	state;
	int	heading;
public:
	Object(sf::RenderWindow* window);
	void	setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	sf::IntRect boundingBox();
	virtual void move(void);
	virtual void fall(void);
	virtual void jump(bool down);
};

