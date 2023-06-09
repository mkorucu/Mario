#pragma once
#include "main.h"

class ScoreBoard
{
private:
	sf::Texture _headTextures;
	sf::Sprite _headSprite;
	sf::Font font;
	sf::Text text;
	sf::RenderWindow* _window;
	std::string	score;
	int	lives;
public:
	ScoreBoard(sf::RenderWindow* window);
	void	setScore(int score);
	void	setLives(int lives);
	int		getLives(void);
	int		getScore(void);
};