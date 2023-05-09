#pragma once
#include "main.h"

class Game
{
private:
	int	_speed;
	Object floor;
	Object brick;
	Object pipe;
	
public:
	void	drawBackground(sf::RenderWindow& window);
	//bool	onFloor(Object* obj);
	//bool	checkCollusion(Turtle* t, Mario* m, int& side);
};




