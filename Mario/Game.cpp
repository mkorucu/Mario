#include "main.h"
#include "Game.h"

int Game::GetSpeed()
{
	return this->_speed;
}

Game::Game(sf::RenderWindow& window) : _scoreBoard(new ScoreBoard(&window))
{
    this->_head = 0;
	this->_speed = 10;
	this->setBackground(window);
}

void    Game::setBackground(sf::RenderWindow& window)
{																																	
	if (!_floorTexture.loadFromFile("../assets/floor.png") || !_brickTexture.loadFromFile("../assets/brick.png")					//************************************************************
		||  !_pipesBackground[0].loadFromFile("../assets/pipes.png") || !_pipesBackground[1].loadFromFile("../assets/pipe.png"))
		return;
	this->_floor.setTexture(_floorTexture);
	this->_floor.setPosition(0, (float)window.getSize().x - this->_floor.getLocalBounds().height * 3 / 2);
	for (int i = 0; i < 7; i++)
	{
		this->_brick[i].setTexture(_brickTexture);
		this->_brickTexture.setRepeated(true);
	}
	this->_brick[0].setPosition(0, (float)window.getSize().y / 4);
	this->_brick[0].setTextureRect(sf::IntRect(0, 0, 420, 34));
	this->_brick[1].setPosition((float)window.getSize().x - 420, (float)window.getSize().y / 4);
	this->_brick[1].setTextureRect(sf::IntRect(0, 0, 420, 34));																// This section is a bit crowded, but in general, his job is simple. 
	this->_brick[3].setPosition((float)window.getSize().x / 2 - 240, (float)window.getSize().y / 2 - 34);					//All the background bricks of the game, the textures of the floor and pipes are adjusted in this part and assigned to the sprites.
	this->_brick[3].setTextureRect(sf::IntRect(0, 0, 480, 34));
	this->_brick[2].setPosition(0, (float)window.getSize().y / 2);
	this->_brick[2].setTextureRect(sf::IntRect(0, 0, 120, 34));
	this->_brick[4].setPosition((float)window.getSize().x - 120, (float)window.getSize().y / 2);
	this->_brick[4].setTextureRect(sf::IntRect(0, 0, 420, 34));
	this->_brick[5].setPosition(0, (float)window.getSize().y * 3 / 4);
	this->_brick[5].setTextureRect(sf::IntRect(0, 0, 360, 34));
	this->_brick[6].setPosition((float)window.getSize().x - 360, (float)window.getSize().y * 3 / 4);
	this->_brick[6].setTextureRect(sf::IntRect(0, 0, 360, 34));


	this->_pipes[0].setTexture(this->_pipesBackground[0]);
	this->_pipes[0].setPosition(0, (float)window.getSize().y / 4 - 156);
	this->_pipes[1].setTexture(this->_pipesBackground[0]);
	this->_pipes[1].scale(-1.f, 1.f);
	this->_pipes[1].setPosition((float)window.getSize().x, (float)window.getSize().y / 4 - 156);
	this->_pipes[2].setTexture(this->_pipesBackground[1]);
	this->_pipes[2].scale(-1.f, 1.f);
	this->_pipes[2].setPosition(130, (float)window.getSize().y - 166);
	this->_pipes[3].setTexture(this->_pipesBackground[1]);
	this->_pipes[3].setPosition((float)window.getSize().x - 130, (float)window.getSize().y - 166);									//************************************************************
}

bool Game::onFloor(Object *obj)																					//**************************************************************************
{
    if (obj->boundingBox().intersects(static_cast<sf::IntRect>(this->_floor.getGlobalBounds())))
    {
        return (true);
    }
    for(int i = 0; i < 7; i++)
		if (obj->boundingBox().intersects(static_cast<sf::IntRect>(this->_brick[i].getGlobalBounds())))			//In this part, we check the case of the turtle or Mario colliding with bricks, floor or pipes and restrict its movement.
        {																										// The point to be considered here was to show that if the object is turtle, it does not conflict with the pipe. 
	        return true;																						//For this, we made a distinction according to the pixels by using the boundryBox property of the object.
        }																											
    for(int i = 0; i < 4; i++)
        if (obj->boundingBox().intersects(static_cast<sf::IntRect>(this->_pipes[i].getGlobalBounds())))
        {
            if (obj->boundingBox().width == 68)     
                return false;                       
            return true;
        }
    return (false);
}																												//**************************************************************************

void Game::drawBackground(sf::RenderWindow &window)														//**************************************************************************
{
    sf::RenderStates    states;
    states.blendMode = sf::BlendMode(sf::BlendMode::SrcAlpha, sf::BlendMode::OneMinusSrcAlpha);

    for (int i = 0; i < 7; i++)
        window.draw(this->_brick[i]);																	//Here, the sprites we set earlier are printed on the screen. 
    for (int i = 0; i < 4; i++)																			//It should be noted that the pipes are pressed in front of the screen. 
        window.draw(this->_pipes[i],states);															//For the Turtles!
    window.draw(this->_floor);
}																										//**************************************************************************

bool Game::checkCollusion(Turtle* t, Mario* m, int& side)												//**************************************************************************
{
    if (t->getIsDead() || m->getIsDead())																// If already one of them is dead, collision is not happend.
        return false;

    if (t->boundingBox().intersects(m->boundingBox()))
    {
        std::cout << "collision start" << std::endl;
        if ((m->getPosition().y + 65 < (t->getPosition().y + (t->boundingBox().height / 2.0f))))		//The collision status of Mario and Turtles is checked here. Mario dies in all collisions, except for one.
        {
            t->fall();
            return true;
        }
        else
        {
            m->fall();
            return true;
        }
    }
    return false;
}																										//**************************************************************************

bool Game::checkTurtleCollusion(Turtle* t1, Turtle* t2)													//**************************************************************************
{
	if (t1->getIsDead() || t2->getIsDead())
		return false;
																										// This part is about bonus part, which is collision of turtles
	if (t1->boundingBox().intersects(t2->boundingBox()))												// but we don't have time to develop this feature :/
	{
		std::cout << "turtle collision start" << std::endl;
	}
	return false;
}																										//**************************************************************************

void    Game::AddObject(Object *obj)																	//**************************************************************************
{
	ObjectNode *newNode = new ObjectNode(obj);
	if (this->_head == nullptr)
		this->_head = newNode;
	else if (obj->boundingBox().width == 68)
	{
		ObjectNode *curr = this->_head;																	// This part is adding new object to link list
		while(curr->_next != nullptr)
			curr = curr->_next;
		curr->_next = newNode;
	}
	else if(obj->boundingBox().width == 66)
	{
		newNode->_next = this->_head;
		this->_head = newNode;
	}
}

void Game::DeleteObject(Object *obj)
{
	ObjectNode *curr;
	ObjectNode *curr2;
	if (obj->boundingBox().width == 66)
	{
		curr = this->_head;
		_head = _head->_next;																			// This part is delete the object from link list
		delete curr->_obj;
		delete curr;
	}
	else if (obj->boundingBox().width == 68)
	{
		curr = this->_head;
		while (curr->_next != nullptr && curr->_next->_obj != obj)
		{
			curr = curr->_next;
		}
		curr2 = curr->_next;
		if (curr2 != nullptr && curr->_next->_obj == curr2->_obj)
		{
			curr->_next = curr->_next->_next;
			delete curr2->_obj;
			delete curr2;
		}	
	}
}

Object *Game::getObject(int i)
{
	ObjectNode *curr = this->_head;
	for (int x = 0; x < i; x++)
	{																									// Find the object in List
		if (curr == nullptr)
			return (NULL);
		curr = curr->_next;
	}
	return curr->_obj;
}

ScoreBoard* Game::getScoreBoard()
{
	return this->_scoreBoard;																			// Get scoreboard.
}
