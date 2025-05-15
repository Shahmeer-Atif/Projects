#include<iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "SFML/Graphics/Image.hpp"
#include <ctime>
#include"Game.h"
#include"Menu.h"
#include"ScoreBoard.h"
using namespace sf;
using namespace std;
//Shahmeer Atif 23i-0711 CS-G

int main()
{
	Game game;
	game.start();
	RenderWindow window(VideoMode(HorizontalBox*11, verticalBox*6), "Plants Vs Zombies");
	Image icon;
	if (!icon.loadFromFile("images/icon.png"))
	{
		return 1;
	}
	window.setIcon(32, 32, icon.getPixelsPtr());
	Clock MousePress;
	while (window.isOpen())
	{
		game.start();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape &&!game.getpause())
					game.pause();
				if (event.key.code == Keyboard::BackSpace)
					window.close();
			}
		}
		sf::Event::MouseMoved;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && MousePress.getElapsedTime().asSeconds()>=0.2)
		{
			MousePress.restart();
			sf::Vector2i mousePos= sf::Mouse::getPosition(window);
			game.draw(window,mousePos);
		}
		game.drawEntities(window,event);
		window.setSize(sf::Vector2u(HorizontalBox*11, verticalBox*6));
		window.display();
		window.clear();

	}
	return 0;
}
