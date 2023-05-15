#pragma once
#include "main.h"
#include "Object.h"
#include "Turtle.h"
#include "Mario.h"
#include "ObjectNode.h"
class Game
{
private:
	int	_speed;
	unsigned long	time;
	ObjectNode	*_head;
	sf::Texture _floorTexture;
	sf::Texture _brickTexture;
	sf::Texture	_pipesBackground[2];
	sf::Sprite _floor;
	sf::Sprite _brick[7];
	sf::Sprite _pipes[4];

public:
	int		GetSpeed();
	Game(sf::RenderWindow &window);
	void	drawBackground(sf::RenderWindow& window);
	void	setBackground(sf::RenderWindow& window);
	bool	onFloor(Object *obj);
	bool	checkCollusion(Turtle* t, Mario* m, int& side);
	bool	checkTurtleCollusion(Turtle* t1, Turtle* t2);
	void	AddObject(Object *obj);
	void	DeleteObject(Object *obj);
	Object *getObject(int i);
	int		ObjectCount();
};




