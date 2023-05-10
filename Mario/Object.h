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
	virtual void draw(sf::RenderWindow& window);
	virtual void move(void);
	virtual void fall(void);
	virtual void jump(bool down);
};

