#include "main.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(sf::RenderWindow* window)
{
	this->_window = window;
	this->score = "000000";
	this->lives = 3;
	this->font.loadFromFile("../assets/font.ttf");
	this->_headTextures.loadFromFile("../assets/mariohead.png");
	this->_headTextures.setRepeated(true);
	this->_headSprite.setTexture(this->_headTextures);
	this->text.setFont(this->font);
}

void ScoreBoard::setScore(int score)
{
	int newScore = std::stoi(this->score);
	newScore += score;
	this->score = std::to_string(newScore);
	this->score = std::string(6 - this->score.length(), '0') + this->score;
	this->text.setString(this->score);
	this->text.setCharacterSize(42);
	this->text.setPosition(70, 50);
	this->_headSprite.setPosition(260, 65);
	this->_headSprite.setTextureRect(sf::IntRect(0, 0, this->lives * 34, 26));
	this->_window->draw(_headSprite);
	this->_window->draw(text);
}

void ScoreBoard::setLives(int lives)
{
	this->lives = this->lives - lives;
}

int ScoreBoard::getLives(void)
{
	return this->lives;
}
