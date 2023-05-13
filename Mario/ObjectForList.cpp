#include "main.h"
#include "ObjectForList.h"

ObjectForList::ObjectForList()
{
	this->_head = NULL;
}

void	ObjectForList::AddObject(Object *obj)
{
	ObjectNode *newNode = new ObjectNode(obj);
	if (this->_head == NULL)
	{
		this->_head = newNode;
	}
	else
	{
		ObjectNode *curr = this->_head;
		while(curr->_next != nullptr)
			curr = curr->_next;
		curr->_next = newNode;
	}
}
Object *ObjectForList::getObject(int i)
{
	ObjectNode *curr = this->_head;
	for(int x = 0; x < i; x++)
		curr = curr->_next;
	return curr->_obj;
}
// void	DeleteObject(Object *obj);
// void	Display();