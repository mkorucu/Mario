#include "main.h"
#include "ObjectNode.h"

ObjectNode::ObjectNode(Object *obj) 
{
	this->_obj = obj;
	this->_next = nullptr;
}