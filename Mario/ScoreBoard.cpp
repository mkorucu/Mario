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
	this->text.setFont(this->font);
}

void ScoreBoard::setScore(int score)
{
	int newScore = std::stoi(this->score);
	newScore += score;
	this->score = std::to_string(newScore);
	this->score = std::string(6 - this->score.length(), '0') + this->score;
	this->text.setString(this->score);
	this->text.setCharacterSize(24);
	this->text.setPosition(50, 50);
	this->_window->draw(text);
}

void ScoreBoard::setLives(int lives)
{
}

int ScoreBoard::getLives(void)
{
	return 0;
}
