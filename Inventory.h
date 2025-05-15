#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Image.hpp"
#include <ctime>
#include <cstdlib> 
#include"Global.h"
using namespace std;
using namespace sf;
//Group Member 1: Shahmeer Atif 23i-0711 CS-G
//Group Member 2: Irfan Khalid  23i-2092 CS-G


class Inventory {
	Sprite BackGround;
	Texture Back;
	sf::Sprite* PlantS;
	sf::Texture* PlantT;
	sf::Text Suns;
	sf::Font font;
	Clock timer[7];
	int price[7];
	int sun;
	int index;
	bool* select;
	int numofPlants;
public:

	Inventory(int num=2) {
		numofPlants = num;
		
		sun = 100;
		index = -1;
		select = new bool[7];
		for (int i = 0; i < 7; i++)
			select[i] = false;
		PlantS = new Sprite[7];
		PlantT = new Texture[7];

		PlantT[0].loadFromFile("Images/Card/card_peashooter.png");
		PlantS[0].setTexture(PlantT[0]);
		PlantS[0].setTextureRect(sf::IntRect(0, 0, 64, 90));
		PlantS[0].setPosition(75, 0);
		PlantT[1].loadFromFile("Images/Card/card_sunflower.png");
		PlantS[1].setTexture(PlantT[1]);
		PlantS[1].setTextureRect(sf::IntRect(0, 0, 64, 90));
		PlantS[1].setPosition(75 + 70, 0);
		PlantT[2].loadFromFile("Images/Card/card_wallnut.png");
		PlantS[2].setTexture(PlantT[2]);
		PlantS[2].setTextureRect(sf::IntRect(0, 0, 64, 90));
		PlantS[2].setPosition(75 + 140, 0);
		PlantT[3].loadFromFile("Images/Card/card_cherrybomb.png");
		PlantS[3].setTexture(PlantT[3]);
		PlantS[3].setTextureRect(sf::IntRect(0, 0, 64, 90));
		PlantS[3].setPosition(75 + 210, 0);
		PlantT[4].loadFromFile("Images/Card/card_repeaterpea.png");
		PlantS[4].setTexture(PlantT[4]);
		PlantS[4].setTextureRect(sf::IntRect(0, 0, 64, 90));
		PlantS[4].setPosition(75 + 280, 0);
		PlantT[5].loadFromFile("Images/Card/card_snowpea.png");
		PlantS[5].setTexture(PlantT[5]);
		PlantS[5].setTextureRect(sf::IntRect(0, 0, 64, 90));
		PlantS[5].setPosition(75 + 350, 0);
		PlantT[6].loadFromFile("Images/Card/card_scaredyshroom.png");
		PlantS[6].setTexture(PlantT[6]);
		PlantS[6].setTextureRect(sf::IntRect(0, 0, 64, 90));
		PlantS[6].setPosition(75 + 420, 0);
		Back.loadFromFile("Images/ChooserBackground.png");
		BackGround.setTexture(Back);
		BackGround.setTextureRect(sf::IntRect(0, 0, 522, 87));
		BackGround.setPosition(0, 0);
		font.loadFromFile("Images/SamdanEvil.ttf");
		Suns.setFont(font);
		Suns.setScale(1.f, 1.f);
		Suns.setCharacterSize(24);
		Suns.setFillColor(sf::Color::Black);
		Suns.setPosition(35, 57);
		Suns.setString(to_string(sun));
		price[0] = 100;
		price[1] = 100;
		price[2] = 50;
		price[3] = 150;
		price[4] = 200;
		price[5] = 175;
		price[6] = 75;

	}
	
	Sprite getSprite(int i) {
		return PlantS[i];
	}
	void setsun(int i=25) {
		sun += i;
	}
	int getsun() {
		return sun;
	}
	bool checkCoordinates(int x, int y) {
		int HorizontalBox = 70;
		if (x >= HorizontalBox && x < HorizontalBox + 70 && y >= 0 && y < verticalBox && timer[0].getElapsedTime().asSeconds()>2)
		{
			timer[0].restart();
			for (int i = 0; i < numofPlants; i++)
				select[i] = false;
			select[0] = true;
		}
		else if (x > HorizontalBox * 2 && x < HorizontalBox * 3 && y >= 0 && y < verticalBox && timer[1].getElapsedTime().asSeconds()>1)
		{
			for (int i = 0; i < numofPlants; i++)
				select[i] = false;
			select[1] = true;
			timer[1].restart();
		}
		else if (x > HorizontalBox * 3 && x < HorizontalBox * 4 && y >= 0 && y < verticalBox && timer[2].getElapsedTime().asSeconds()>5)
		{
			timer[2].restart();
			for (int i = 0; i < 6; i++)
				select[i] = false;
			select[2] = true;
		}
		else if (x >= HorizontalBox * 4 && x <= HorizontalBox * 5 && y >= 0 && y < verticalBox && timer[3].getElapsedTime().asSeconds()>7)
		{
			timer[3].restart();
			for (int i = 0; i < numofPlants; i++)
				select[i] = false;
			select[3] = true;
		}
		else if (x >= HorizontalBox * 5 && x <= HorizontalBox * 6 && y >= 0 && y < verticalBox && timer[4].getElapsedTime().asSeconds()>3)
		{
			timer[4].restart();
			for (int i = 0; i < numofPlants; i++)
				select[i] = false;
			select[4] = true;
		}
		else if (x >= HorizontalBox * 6 && x <= HorizontalBox * 7 && y >= 0 && y < verticalBox && timer[5].getElapsedTime().asSeconds()>2)
		{
			timer[5].restart();
			for (int i = 0; i < numofPlants; i++)
				select[i] = false;
			select[5] = true;
		}
		else if (x >= HorizontalBox * 7 && x <= HorizontalBox * 8 && y >= 0 && y < verticalBox && timer[6].getElapsedTime().asSeconds()>2)
		{
			timer[6].restart();
			for (int i = 0; i < numofPlants; i++)
				select[i] = false;
			select[6] = true;
		}
		else
		{
			for (int i = 0; i < numofPlants; i++)
				select[i] = false;
			return false;
		}

	}
	int getindex() {
		for (int i = 0; i < numofPlants; i++)
		{
			if (select[i] && sun - price[i] >= 0)
			{
			sun -= price[i];
				index = i;
			}
		}
			return index;
	}
	void setindex(int i) {
		index = i;
	}
	void drawInventory(RenderWindow& w){
		w.draw(BackGround);
		for (int i = 0; i < numofPlants; i++)
			w.draw(PlantS[i]);
		Suns.setString(to_string(sun));
		w.draw(Suns);
	}
	int getnumofplants() {
		return numofPlants;
	}
	void draw(Event& event,RenderWindow& window)
	{
			if (index == 0)
			{
				Texture Tex;
				Sprite Plant1;
				Tex.loadFromFile("Images/Card/card_peashooter.png");
				Plant1.setTexture(Tex);
				Plant1.setTextureRect(sf::IntRect(0, 0, 64, 90));
				Plant1.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				window.draw(Plant1);
			}
			else if (index == 1)
			{
				Texture Tex;
				Sprite Plant1;
				Tex.loadFromFile("Images/Card/card_sunflower.png");
				Plant1.setTexture(Tex);
				Plant1.setTextureRect(sf::IntRect(0, 0, 64, 90));
				Plant1.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				window.draw(Plant1);
			}
			else if (index == 2)
			{
				Texture Tex;
				Sprite Plant1;
				Tex.loadFromFile("Images/Card/card_wallnut.png");
				Plant1.setTexture(Tex);
				Plant1.setTextureRect(sf::IntRect(0, 0, 64, 90));
				Plant1.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				window.draw(Plant1);
			}
			else if (index == 3)
			{
				Texture Tex;
				Sprite Plant1;
				Tex.loadFromFile("Images/Card/card_cherrybomb.png");
				Plant1.setTexture(Tex);
				Plant1.setTextureRect(sf::IntRect(0, 0, 64, 90));
				Plant1.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				window.draw(Plant1);
			}
			else if (index == 4)
			{
				Texture Tex;
				Sprite Plant1;
				Tex.loadFromFile("Images/Card/card_repeaterpea.png");
				Plant1.setTexture(Tex);
				Plant1.setTextureRect(sf::IntRect(0, 0, 64, 90));
				Plant1.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				window.draw(Plant1);
			}
			else if (index == 5)
			{
				Texture Tex;
				Sprite Plant1;
				Tex.loadFromFile("Images/Card/card_snowpea.png");
				Plant1.setTexture(Tex);
				Plant1.setTextureRect(sf::IntRect(0, 0, 64, 90));
				Plant1.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				window.draw(Plant1);
			}
			else if (index == 6)
			{
				Texture Tex;
				Sprite Plant1;
				Tex.loadFromFile("Images/Card/card_scaredyshroom.png");
				Plant1.setTexture(Tex);
				Plant1.setTextureRect(sf::IntRect(0, 0, 64, 90));
				Plant1.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				window.draw(Plant1);
			}
		
	}
};
