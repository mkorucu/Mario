#pragma once
#include "main.h"

class ObjectNode
{
public:
	Object *_obj;
	ObjectNode *_next;
	ObjectNode(Object *obj);
};

