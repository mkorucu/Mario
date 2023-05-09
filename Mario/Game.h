#pragma once
#include "main.h"

class Game
{
private:
	int	_speed;
	sf::Texture _floorTexture;
	sf::Texture _brickTexture;
	sf::Texture	_pipesBackground[2];
	sf::Sprite _floor;
	sf::Sprite _brick[7];
	sf::Sprite _pipes[4];

public:
	Game(sf::RenderWindow &window);
	void	drawBackground(sf::RenderWindow& window);
	//bool	onFloor(Object* obj);
	//bool	checkCollusion(Turtle* t, Mario* m, int& side);
};




