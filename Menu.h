#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Image.hpp"
#include <ctime>
#include <cstdlib> 
#include"Plants.h"
#include"Zombies.h"
#include"Inventory.h"
#include"Global.h"
#include"Sun.h"
using namespace std;
using namespace sf;
//Group Member 1: Shahmeer Atif 23i-0711 CS-G
//Group Member 2: Irfan Khalid  23i-2092 CS-G
class Screen {
protected:
	Image map_image;
	Texture map;
	Sprite s_map;
	sf::Font font;
	sf::Text Start;
	bool Seize;
	
public:
	Screen() {
		Seize = true;
	}
	void setSeize()
	{
		if (Seize)
			Seize = false;
		else
			Seize = true;
	}
	virtual int Input(Vector2i Mousepos) = 0;
	virtual void draw(RenderWindow& window) = 0;
};
class GameMenu: public Screen {
	Texture PT;
	Sprite PVZ;
	sf::Text Instructions;
	sf::Text LeaderBoard;
	Vector2f pos;
public:
	GameMenu() {
		pos = { 300,200 };
		font.loadFromFile("Images/SamdanEvil.ttf");
		Start.setFont(font);
		Start.setCharacterSize(100);
		Start.setFillColor(sf::Color::Black);
		Start.setPosition(570, 120);
		Start.rotate(2);
		Start.setString("Start Game");
		Instructions.setFont(font);
		Instructions.setCharacterSize(60);
		Instructions.setFillColor(sf::Color::Black);
		Instructions.setPosition(620, 280);
		Instructions.rotate(5);
		Instructions.setString("Instructions");

		font.loadFromFile("Images/SamdanEvil.ttf");
		LeaderBoard.setFont(font);
		LeaderBoard.setCharacterSize(60);
		LeaderBoard.setFillColor(sf::Color::Yellow);
		LeaderBoard.setString("LeaderBoard");
		map_image.loadFromFile("images/assets/Inventory-GameScreen/MainMenu.png");
		map.loadFromImage(map_image);
		s_map.setTexture(map);
		s_map.setPosition(0, 0);

		PT.loadFromFile("images/assets/Inventory-GameScreen/PVZ.png");
		PVZ.setTexture(PT);
		PVZ.setTextureRect(sf::IntRect(0, 0, 500, 500));
		PVZ.setPosition(100, 0);
	}
	int Input(Vector2i Mousepos) {
		if (Mousepos.x >= 570 && Mousepos.x <= 400 + 570 && Mousepos.y >= 120 && Mousepos.y <= 100 + 120 && Seize)
		{
			return 1;
		}
		if (Mousepos.x >= 620 && Mousepos.x <= 300 + 620 && Mousepos.y >= 280 && Mousepos.y <= 100 + 280 && Seize)
		{
			return 2;
		}
		if (Mousepos.x >= 0 && Mousepos.x <= 270 && Mousepos.y >= 0 && Mousepos.y <= 70 && Seize)
		{
			return 4;
		}
		else
			return 5;
		return -1;
	}
	void draw(RenderWindow& window) {
		window.draw(s_map);
		window.draw(Start);
		window.draw(Instructions);
		window.draw(PVZ);
		window.draw(LeaderBoard);
	}
};
class Instructions : public Screen {

public:
	Instructions() {
		map_image.loadFromFile("images/assets/Inventory-GameScreen/Instructions.png");
		map.loadFromImage(map_image);
		s_map.setTexture(map);
		s_map.setPosition(0, 0);
		font.loadFromFile("Images/SamdanEvil.ttf");
		Start.setFont(font);
		Start.setCharacterSize(35);
		Start.setFillColor(sf::Color::Black);
		Start.setPosition(630, 530);
		Start.setString("Click Anywhere to Exit!!");

	}
	int Input(Vector2i Mousepos) {
		if (Mousepos.x >= 0 && Mousepos.x <= 1100 && Mousepos.y >= 0 && Mousepos.y <= 600)
		{
			return 3;
		}
		return -1;
	}
	void draw(RenderWindow& window) {
		window.draw(s_map);
		window.draw(Start);
	}
};
class Lost : public Screen {

public:
	Lost() {
		map_image.loadFromFile("images/assets/Inventory-GameScreen/GameLoose.png");
		map.loadFromImage(map_image);
		s_map.setTexture(map);
		s_map.setPosition(0, 0);

	}
	int Input(Vector2i Mousepos) {
		if (Mousepos.x >= 0 && Mousepos.x <= 1100 && Mousepos.y >= 0 && Mousepos.y <= 600)
		{
			return 3;
		}
		return -1;
	}
	void draw(RenderWindow& window) {
		window.draw(s_map);
	}
};
class Won : public Screen {

public:
	Won() {
		map_image.loadFromFile("images/assets/Inventory-GameScreen/GameVictory.png");
		map.loadFromImage(map_image);
		s_map.setTexture(map);
		s_map.setPosition(0, 0);

	}
	int Input(Vector2i Mousepos) {
		if (Mousepos.x >= 0 && Mousepos.x <= 1100 && Mousepos.y >= 0 && Mousepos.y <= 600)
		{
			return 3;
		}
		return -1;
	}
	void draw(RenderWindow& window) {
		window.draw(s_map);
	}
};
class PauseS : public Screen {

public:
	PauseS() {
		map_image.loadFromFile("images/assets/Inventory-GameScreen/Pause1.png");
		map.loadFromImage(map_image);
		s_map.setTexture(map);
		s_map.setPosition(360, 100);

	}
	int Input(Vector2i Mousepos) {
		if (Mousepos.x >= 400 && Mousepos.x <= 700 && Mousepos.y >= 330 && Mousepos.y <= 400)
		{
			return 5;
		}
		return 5;
	}
	void draw(RenderWindow& window) {
		window.draw(s_map);
	}
};