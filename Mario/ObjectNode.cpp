#include "main.h"
#include "ObjectNode.h"

ObjectNode::ObjectNode(Object *obj)				//sets its argument to its attribute
{
	this->_obj = obj;
	this->_next = nullptr;
}