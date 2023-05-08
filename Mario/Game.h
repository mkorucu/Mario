#pragma once
#include "main.h"

class Game
{
private:
	int	_speed;
	Object	_floor;
	Object	_pipe;
	Object	_pipes;
	Object	_brick;
public:
	void	drawBackground(sf::RenderWindow& window);
	//bool	onFloor(Object* obj);
	//bool	checkCollusion(Turtle* t, Mario* m, int& side);
};




