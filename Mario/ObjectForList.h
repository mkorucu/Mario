#pragma once
#include "main.h"



class ObjectForList
{
private:
	ObjectNode *_head;
public:
	ObjectForList();
	void	AddObject(Object *obj);
	Object *getObject(int i);
	//void	DeleteObject(Object *obj);
	//void	Display();
};