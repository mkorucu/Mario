#pragma once
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Mario.h"
#include "Object.h"
#include "ObjectNode.h"
#include "ScoreBoard.h"
#include "Turtle.h"

#define NONE	0
#define UP		0
#define DOWN	0
#define LEFT	-1
#define RIGHT	1

int	setKeys(sf::Event& event, int& select, int& state);
void	setTexts(sf::Font& font, sf::Text& title, sf::Text& option1, sf::Text& option2, sf::Text& option3, sf::Text& option4, sf::Window& window);