#pragma once
#include "main.h"
#include "Object.h"
class Mario : public Object
{
private:
	float	_vx;
	float	_vy;
public:
	Mario(sf::RenderWindow* window);
	void	CornerChecks();
	void	move();
	void	jump(bool down);
	void	fall(void);
};

