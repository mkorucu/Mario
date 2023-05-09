#include "Object.h"

Object::Object(sf::RenderWindow* window)
{
	this->_window = window;
}

void	Object::setSpriteTexture(char* texture)
{
	int i = 0;
	sf::Texture* curr;
	curr = _textures;
	while (curr != NULL)
		curr++;
	if (!curr->loadFromFile(texture))
		return ;
	this->_sprite.setTexture(*curr);

}