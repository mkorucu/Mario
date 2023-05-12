#pragma once
#include "main.h"
#include "Object.h"
class Turtle : public Object
{
private:
	float	_vx;
	float	_vy;
public:
	Turtle(sf::RenderWindow* window);
	void	move();
	void	jump(bool down);
	void	fall(void);
};