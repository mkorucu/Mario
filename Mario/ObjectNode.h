#pragma once
#include "main.h"

class ObjectNode
{
public:
	ObjectNode(Object *obj);
	Object *_obj;
	ObjectNode *_next;
};

