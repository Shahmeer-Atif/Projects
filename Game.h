#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Image.hpp"
#include <ctime>
#include <cstdlib> 
#include<string>
#include"sublevels.h"
#include"Global.h"
#include"Menu.h"
#include"ScoreBoard.h"
using namespace std;
using namespace sf;
//Group Member 1: Shahmeer Atif 23i-0711 CS-G
//Group Member 2: Irfan Khalid  23i-2092 CS-G
class Game {
	ScoreBoard Sboard;
	Levels* level;
	Screen* Menu;
	bool *exist;
	int numoflevel;
	bool** FIELD_GAME_STATUS;
	const int ROWS = 5;
	const int COLS = 9;
	Clock Pause;
	bool pauseG;
	bool starting;
	int life;
	int score;
	sf::Texture livesTexture;
	sf::Sprite livesSprite;
	sf::Texture Medal;
	sf::Sprite MedalSprite;
	int badge;
	bool SB = false;
public:
	Game() {
		pauseG = false;
		livesTexture.loadFromFile("images/life.png");
		livesSprite.setTexture(livesTexture);
		badge=Sboard.Action();
		Menu = new GameMenu();
		starting = false;
		exist = new bool[5];
		for (int i = 0; i < 5; i++)
			exist[i] = true;
		numoflevel = 0;
		level = nullptr;
		FIELD_GAME_STATUS = new bool* [ROWS];
		for (int i = 0; i < ROWS; i++)
			FIELD_GAME_STATUS[i] = new bool[COLS];
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				FIELD_GAME_STATUS[i][j] = true;
			}
		}
		life = 4;
		score = 10;
		if(badge!=-1)
		{
			if (badge == 0)
				Medal.loadFromFile("images/assets/Inventory-GameScreen/Gold64.png");
			else if (badge == 2)
				Medal.loadFromFile("images/assets/Inventory-GameScreen/Silver64.png");
			else if (badge == 4)
				Medal.loadFromFile("images/assets/Inventory-GameScreen/Bronze64.png");
			MedalSprite.setTexture(Medal);
			MedalSprite.setPosition(740, 0);
		}
	}
	void pause() {
		
		Menu = new PauseS();
		pauseG = true;
		level->pauselevel();
	}
	bool getpause() {
		return pauseG;
	}
	void start() {
		if(starting)
		{
			if (numoflevel == 1 && exist[numoflevel])
			{
				delete level;
				for (int i = 0; i < ROWS; i++) {
					for (int j = 0; j < COLS; j++) {
						FIELD_GAME_STATUS[i][j] = true;
					}
				}
				level = new ZombieOutskirts();
				exist[numoflevel] = false;
			}
			else if (numoflevel == 2 && exist[numoflevel])
			{
				delete level;
				for (int i = 0; i < ROWS; i++) {
					for (int j = 0; j < COLS; j++) {
						FIELD_GAME_STATUS[i][j] = true;
					}
				}
				level = new SunflowerFeilds();
				exist[numoflevel] = false;
			}
			else if (numoflevel == 3 && exist[numoflevel])
			{
				delete level;
				for (int i = 0; i < ROWS; i++) {
					for (int j = 0; j < COLS; j++) {
						FIELD_GAME_STATUS[i][j] = true;
					}
				}
				level = new FoggyForest();
				exist[numoflevel] = false;
			}
		}
	}
	void draw(RenderWindow& window,Vector2i& mousePos) {
		if (starting)
		{
			level->getInventory().checkCoordinates(mousePos.x, mousePos.y);
			level->getPlants().addplant(mousePos.x, mousePos.y, FIELD_GAME_STATUS);
			level->CollectSun(mousePos);
			level->getPlants().checkFeild(FIELD_GAME_STATUS);
			if (pauseG)
			{
				if (Menu->Input(mousePos))
					delete Menu;
				pauseG = false;
				level->pauselevel();
			}
		}
		else
		{
			if (Menu->Input(mousePos) == 1)
			{
				delete Menu;
				starting = true;
				level = new BeginnersGarden();
				numoflevel = 0;
				exist[numoflevel] = false;
			}
			else if(Menu->Input(mousePos) == 2)
			{
				delete Menu;
				Menu = new Instructions();
			}
			else if (Menu->Input(mousePos) == 3)
			{
				delete Menu;
				Menu = new GameMenu();
			}
			else if (Menu->Input(mousePos) == 4)
			{
				Menu->setSeize();
				SB = true;
			}
			else if(Menu->Input(mousePos) == 5)
			{
				Menu->setSeize();
				SB = false;
			}
		}

		

	}
	void drawEntities(RenderWindow& window, Event& event) {
		if(starting)
		{
			score = level->getscore();
			level->getPlants().checkFeild(FIELD_GAME_STATUS);
			window.draw(level->getGrid());
			window.draw(level->getText());
			level->spawnZombies();
			level->getInventory().drawInventory(window);
			level->getPlants().drawPlants(window);
			level->getSun().addSun();
			level->getInventory().draw(event, window);
			if (level->getZombies().DrawZombie(window))
				life--;
			for (int i = 0; i < level->getSun().getsize(); i++)
			{
				if (level->getSun().getexist(i))
					window.draw(level->getSun().getSun(i));
			}
			if (level->LevelEnd())
			{
				numoflevel++;
				if(numoflevel==4)
				{
					Sboard.setscore(score);
					Sboard.addscore(badge);
					starting = false;
					Menu = new Won();
					for (int i = 0; i < numoflevel; i++)
						exist[i] = true;
				}

			}
			int livesDrawx;
			int livesDrawy;
			int gap=0;
			for (int i = life; i > 0; i--)
			{
				livesDrawx =700-gap;
				livesDrawy = 0;
				livesSprite.setPosition(livesDrawx, livesDrawy);
				window.draw(livesSprite);
				gap += 32;
			}
			if (life == 0)
			{
				starting = false;
				delete level;
				Menu = new Lost();
				life = 4;

				Sboard.setscore(score);
				Sboard.addscore(badge);
			}
			window.draw(MedalSprite);
			if (pauseG)
			{
				Menu->draw(window);
			}
		}
		else
			Menu->draw(window);
		if(SB)
			Sboard.draw(window);
	}
	Levels* getlevel() {
		return level;
	}
};