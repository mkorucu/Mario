#include "main.h"
#include <SFML/Graphics.hpp>
#include <iostream>


void	setTexts(sf::Font &font, sf::Text &title, sf::Text &option1, sf::Text &option2, sf::Text &option3, sf::Text& option4, sf::Window &window)	//***********************
{
	if (!font.loadFromFile("../assets/font.ttf"))
		return ;
	title.setFont(font);
	title.setCharacterSize(64);
    title.setString("Menu");
	title.setPosition((window.getSize().x / 2) - (title.getLocalBounds().width / 2), 50);

    option1.setFont(font);
    option1.setCharacterSize(48);
    option1.setString("Continue Game");															//												This function sets Texts 
	option1.setPosition((window.getSize().x / 2) - (option1.getLocalBounds().width / 2), 150);//												of the game:
																								//												MENU
	option2.setFont(font);																		//												Continue Game
    option2.setCharacterSize(48);																//												New Game
    option2.setString("New Game");																//												Exit
	option2.setPosition((window.getSize().x / 2) - (option2.getLocalBounds().width / 2), 250);	//												YOU WIN

    option3.setFont(font);
    option3.setCharacterSize(48);
    option3.setString("Exit");
	option3.setPosition((window.getSize().x / 2) - (option3.getLocalBounds().width / 2), 350);

	option4.setFont(font);
	option4.setCharacterSize(70);
	option4.setString("YOU WIN!!!");
	option4.setPosition((window.getSize().x / 2) - (option4.getLocalBounds().width / 2), window.getSize().y / 2);
	option4.setFillColor(sf::Color::Red);
}//																																				*****************************

int	setKeys(sf::Event &event, int &select, int &state)															//							*****************************
{
	switch (event.key.code)
	{
		case sf::Keyboard::Up:
			if (--select < 0)
				select = 2;
			break;

		case sf::Keyboard::Down:
			if (++select > 2)																					//							This function is for Menu
				select = 0;																						//							state hold the game progress:
			break;																								//							state 0 -> main menu
		case sf::Keyboard::Escape:																				//							state 1 -> continue game
			state = 0;																							//							state 2 -> new game
			break;																								
		case sf::Keyboard::Return:																				//							Select is for menu navigations
			if (select == 1 && state == 1)
				break;
			switch (select)
			{
				case 0:
					state = 1;
					break;
				case 1:
					state = 2;
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
}																												//							********************************
int main()
{
	int	turtleCount = 1, sayac = 1, select = 0, state = 0, score = 0, totalTurtle = 0;
	sf::err().rdbuf(NULL);																		//this line is for hiding terminal error messages
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "Mario");								//starts screen as 1024,1024
	sf::Font	font;
	sf::Text	title, option1, option2, option3, option4;										// Game texts: MENU, NEW GAME, GAME OVER, EXIT, CONTINUE GAME
	Game    game(window);																		//Game constructor
	game.AddObject(new Mario(&window));
    game.AddObject(new Turtle(&window));
	setTexts(font, title, option1, option2, option3, option4, window);							// this function explained above
	
	while (window.isOpen())
	{
		if (sayac % 500 == 0 && turtleCount < 5 && totalTurtle <= 4)							// whenever sayac hits 500, new turtle appears
		{
			sayac = 1;
			turtleCount++;
			game.AddObject(new Turtle(&window));
			totalTurtle++;
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (setKeys(event, select, state))												//	*************************************
				{																				//	This if statement returns true when
					for (int i = turtleCount; i >= 0; i--)										//	player selects exit in the menu window
						game.DeleteObject(game.getObject(i));
					delete (game.getScoreBoard());												//	loop deletes all the turtles and mario
					return (0);																	//	also deletes scoreboard and return (0)
				}																				//	*************************************
		}
		window.clear();
		switch (select)																			//	************************************
        {
            case 0:																				//	sets continue game text to yellow and
                option1.setFillColor(sf::Color::Yellow);										//	others to white
                option2.setFillColor(sf::Color::White);	
				option3.setFillColor(sf::Color::White);
                break;
            case 1:																				//	sets new game text to yellow and
                option1.setFillColor(sf::Color::White);											// and others to white
                option2.setFillColor(sf::Color::Yellow);
				option3.setFillColor(sf::Color::White);
                break;
			case 2:																				//	sets exit text to yellow and
				option1.setFillColor(sf::Color::White);											// and others to white
                option2.setFillColor(sf::Color::White);	
				option3.setFillColor(sf::Color::Yellow);
                break;
        }																						//	************************************
		if (state == 0)																			//	************************************
		{
			window.draw(title);	
			window.draw(option1);																//	state 0: draws menu texts
			window.draw(option2);
			window.draw(option3);
		}																						//	************************************
		if (state == 3)																			//	************************************
		{
			window.clear();
			window.draw(option4);
			window.display();																	// state 4: draws YOU WIN screen
			game.getScoreBoard()->setScore(-1);
			sf::sleep(sf::milliseconds(2000));
			state = 0;
		}																						//	************************************
		if (state == 2)																			//	************************************
		{
			for (int i = turtleCount; i >= 0; i--)
				game.DeleteObject(game.getObject(i));
			game.AddObject(new Mario(&window));													//	STATE 2: New Game state
			game.getScoreBoard()->setLives(game.getScoreBoard()->getLives() - 2);
			turtleCount = 0;																	//	deletes all turtles and mario
			totalTurtle = 0;																	// resets other variables
			game.getScoreBoard()->setScore(-1);
			state = 1;
			sayac = 1;
		}																						//	************************************
		if (state == 1)
		{
			if (game.getObject(0)->getIsDead() == true && game.getObject(0)->getPosition().y > 1150 && game.getScoreBoard()->getLives() > 0)//	********************************
			{																																//	if mario is dead and his body
				game.getScoreBoard()->setLives(1);																							//	lefts screen, it will delete
				game.DeleteObject(game.getObject(0));																						//  Mario and create new one.
				game.AddObject(new Mario(&window));																							//  Also substract 1 heal point
			}																																//	********************************
			else if (game.getObject(0)->getIsDead() == true && game.getScoreBoard()->getLives() == 0)					//	GAME OVER STATE
				state = 0;																								//	goes to main menu
			game.getObject(0)->move();																					//	Mario move method
			game.getObject(0)->jump(game.onFloor(game.getObject(0)));													//	Mario jump method
			for (int i = 1; i <= turtleCount; i++)																							//	********************************
			{																																//	
				game.getObject(i)->move();																									//	Turtle loop
				game.getObject(i)->jump(game.onFloor(game.getObject(i)));																	//	loop will sets all turtles
				game.checkCollusion(static_cast<Turtle*>(game.getObject(i)), static_cast<Mario*>(game.getObject(0)), state);				//	also checks collution with mario
				if (game.getObject(i)->getIsDead() == true && game.getObject(i)->getPosition().y > 1150)									//	if a turtle is dead and his
				{																															//	body fall and disappear from
					game.DeleteObject(game.getObject(i));																					//	screen, it will increase score
					score = 100;																											//	delete the dead turtle and
					--turtleCount;																											//	increase the score
				}	
			}																																//	********************************
			game.drawBackground(window);																				//	first, draws background
			game.getScoreBoard()->setScore(score);																		//	sets and prints score
			score = 0;																									//	resets score variable
		}
		window.display();																								//	displays the screen
		sf::sleep(sf::milliseconds(game.GetSpeed()));																	//	getspeed = 10 for a better gaming experience
		sayac++;																										//	when it hits 500, new turtle appears
		if (game.getScoreBoard()->getScore() == 500)																	//	Winning game condition
			state = 3;
	}
	return 0;
}
