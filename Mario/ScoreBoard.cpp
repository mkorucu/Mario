#include "main.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(sf::RenderWindow* window)						//***********************************************
{
	this->_window = window;
	this->score = "000000";
	this->lives = 2;													//While constructing the scoreboard in this section, the score is set to 0 and 
	this->font.loadFromFile("../assets/font.ttf");						//the required font and Mario's life icon are added to the screen as sprites.
	this->_headTextures.loadFromFile("../assets/mariohead.png");
	this->_headTextures.setRepeated(true);
	this->_headSprite.setTexture(this->_headTextures);
	this->text.setFont(this->font);
}																		//***********************************************

void ScoreBoard::setScore(int score)													//***********************************************			
{
	if (score == -1)
	{
		this->score = "000000";
		return;
	}

	int newScore = std::stoi(this->score);												//If the game restarts or there is a situation where we
	newScore += score;																	//need to reset the score, it will be enough to send -1
	this->score = std::to_string(newScore);												//into the function. Apart from that, the value we send
	this->score = std::string(6 - this->score.length(), '0') + this->score;				//will be reflected in the score as plus points.
	this->text.setString(this->score);
	this->text.setCharacterSize(42);
	this->text.setPosition(70, 50);
	this->_headSprite.setPosition(260, 65);
	this->_headSprite.setTextureRect(sf::IntRect(0, 0, (this->lives + 1) * 34, 26));
	this->_window->draw(_headSprite);
	this->_window->draw(text);
}																						//***********************************************

void ScoreBoard::setLives(int lives)
{
	this->lives = this->lives - lives;													// when this function is called, we reduce one live from mario.
}

int ScoreBoard::getLives(void)
{
	return this->lives;						
}

int ScoreBoard::getScore(void)
{
	return std::stoi(this->score);
}
