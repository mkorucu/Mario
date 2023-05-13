#include "main.h"
#include <SFML/Graphics.hpp>
#include <iostream>


void	setTexts(sf::Font &font, sf::Text &title, sf::Text &option1, sf::Text &option2, sf::Text &option3, sf::Window &window)
{
	if (!font.loadFromFile("../assets/font.ttf"))
		return ;
	title.setFont(font);
	title.setCharacterSize(64);
    title.setString("Menu");
    title.setPosition(window.getSize().x / 2 - option1.getLocalBounds().width / 2, 50);

    option1.setFont(font);
    option1.setCharacterSize(48);
    option1.setString("Continue Game");
    option1.setPosition(window.getSize().x / 2 - option1.getLocalBounds().width / 2, 150);

	option2.setFont(font);
    option2.setCharacterSize(48);
    option2.setString("New Game");
    option2.setPosition(window.getSize().x / 2 - option2.getLocalBounds().width / 2, 250);

    option3.setFont(font);
    option3.setCharacterSize(48);
    option3.setString("Exit");
    option3.setPosition(window.getSize().x / 2 - option2.getLocalBounds().width / 2, 350);
}

int	setKeys(sf::Event &event, int &select, int &state)
{
	switch (event.key.code)
	{
		case sf::Keyboard::Up:
			if (--select < 0)
				select = 2;
			std::cout << "up" << std::endl;
			break;

		case sf::Keyboard::Down:
			if (++select > 2)
				select = 0;
			std::cout << "down" << std::endl;
			break;
		case sf::Keyboard::Escape:
			state = 0;
			break;
		case sf::Keyboard::Return:
			switch (select)
			{
				case 0:
					std::cout << "Continue Game Selected" << std::endl;
					state = 1;
					break;
				case 1:
					state = 2;
					std::cout << "New selected" << std::endl;
					return (0);
					break;
				case 2:
					state = 0;
					return (1);
					break;
			}
			break;
	}
	return (0);
}
int main()
{
	int	turtleCount = 1, sayac = 0;
	sf::err().rdbuf(NULL);
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "Mario");
	sf::Font	font;
	sf::Text	title, option1, option2, option3;
	int	select = 1, state = 0, test = 0;
	Game    game(window);
	game.AddObject(new Mario(&window));
    game.AddObject(new Turtle(&window));
	ScoreBoard board(&window);

	setTexts(font, title, option1, option2, option3, window);
	
	while (window.isOpen())
	{
		if (sayac % 500 == 0)
		{
			sayac = 0;
			turtleCount++;
			game.AddObject(new Turtle(&window));
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (setKeys(event, select, state))
					return (1);
		}
		window.clear();
		switch (select)
        {
            case 0:
                option1.setFillColor(sf::Color::Yellow);
                option2.setFillColor(sf::Color::White);
				option3.setFillColor(sf::Color::White);
                break;
            case 1:
                option1.setFillColor(sf::Color::White);
                option2.setFillColor(sf::Color::Yellow);
				option3.setFillColor(sf::Color::White);
                break;
			case 2:
				option1.setFillColor(sf::Color::White);
                option2.setFillColor(sf::Color::White);
				option3.setFillColor(sf::Color::Yellow);
                break;
        }
		if (state == 0)
		{
			window.draw(title);
			window.draw(option1);
			window.draw(option2);
			window.draw(option3);
		}
		else if (state == 1)
		{
			if (game.getObject(0)->getIsDead() == true && game.getObject(0)->getPosition().y > 1150 && board.getLives() > 0)
			{
				board.setLives(1);
				delete game.getObject(0);
				game.AddObject(new Mario(&window));
			}
			else if (game.getObject(0)->getIsDead() == true && board.getLives() == 0)
			{
				std::cout << "GAME OVER !" << std::endl;
				state = 0;
			}
			game.drawBackground(window);
			game.getObject(0)->move();
			game.getObject(0)->jump(game.onFloor(game.getObject(0)));
			for (int i = 1; i < turtleCount; i++)
			{
				game.getObject(i)->move();
				game.getObject(i)->jump(game.onFloor(game.getObject(i)));
				game.checkCollusion(static_cast<Turtle*>(game.getObject(i)), static_cast<Mario*>(game.getObject(0)), test);
				if (game.getObject(i)->getIsDead() == true && game.getObject(i)->getPosition().y > 1150)
				{
					test = 100;
					game.DeleteObject(game.getObject(i));
					game.AddObject(new Turtle(&window));
				}
			}
			board.setScore(test);
			test = 0;
		}
		window.display();
		sf::sleep(sf::milliseconds(10));
		sayac++;
	}
	return 0;
}
