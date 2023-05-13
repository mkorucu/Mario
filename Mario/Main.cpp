#include "main.h"
#include <SFML/Graphics.hpp>
#include <iostream>


void	setTexts(sf::Font &font, sf::Text &title, sf::Text &option1, sf::Text &option2, sf::Window &window)
{
	if (!font.loadFromFile("../assets/font.ttf"))
		return ;
	title.setFont(font);
	title.setCharacterSize(64);
    title.setString("Menu");
    title.setPosition(window.getSize().x / 2 - option1.getLocalBounds().width / 2, 50);

    option1.setFont(font);
    option1.setCharacterSize(48);
    option1.setString("Continue game");
    option1.setPosition(window.getSize().x / 2 - option1.getLocalBounds().width / 2, 150);

    option2.setFont(font);
    option2.setCharacterSize(48);
    option2.setString("Exit");
    option2.setPosition(window.getSize().x / 2 - option2.getLocalBounds().width / 2, 200);
}

int	setKeys(sf::Event &event, int &select, int &state)
{
	switch (event.key.code)
	{
		case sf::Keyboard::Up:
			select = 1;
			std::cout << "up" << std::endl;
			break;

		case sf::Keyboard::Down:
			select = 2;
			std::cout << "down" << std::endl;
			break;
		case sf::Keyboard::Escape:
			state = 0;
			break;
		case sf::Keyboard::Return:
			switch (select)
			{
				case 1:
					std::cout << "New Game Selected" << std::endl;
					state = 1;
					break;
				case 2:
					state = 2;
					std::cout << "Exit selected" << std::endl;
					return (1);
					break;
			}
	}
	return (0);
}
int main()
{
	sf::err().rdbuf(NULL);
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "Mario");
	sf::Font	font;
	sf::Text	title, option1, option2;
	int	select = 1, state = 0;
	Game    game(window);
	Object* objects = new Mario(&window);
	Object* turtle = new Turtle(&window);

	setTexts(font, title, option1, option2, window);
	
	while (window.isOpen())
	{
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
            case 1:
                option1.setFillColor(sf::Color::Yellow);
                option2.setFillColor(sf::Color::White);
                break;

            case 2:
                option1.setFillColor(sf::Color::White);
                option2.setFillColor(sf::Color::Yellow);
                break;
        }
		if (state == 0)
		{
			window.draw(title);
			window.draw(option1);
			window.draw(option2);
		}
		else if (state == 1)
		{
			turtle->move();
			game.drawBackground(window);
			objects->move();
			objects->jump(game.onFloor(objects));
			turtle->jump(game.onFloor(turtle));
		}
		window.display();
		sf::sleep(sf::milliseconds(10));
	}
	return 0;
}
