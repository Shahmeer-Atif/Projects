#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Image.hpp"
#include <ctime>
#include <cstdlib> 
#include"PlantFactory.h"
#include"ZombieFactory.h"
#include"Inventory.h"
#include"Global.h"
#include"Sun.h"
#include"time.h"
using namespace std;
using namespace sf;
//Group Member 1: Shahmeer Atif 23i-0711 CS-G
//Group Member 2: Irfan Khalid  23i-2092 CS-G

class Levels {

protected:
	int Waves;
	int numofZombie;
	Inventory Inven;
	Plant_Factory* Plants;
	Zombie_Factory* Zombie;
	times* Time;
	sf::Font font;
	sf::Text Levelnum;
	sf::Text Score;
	Sun su;
	bool paused;
	Image map_image;
	Texture map;
	Sprite s_map;
	Clock t;
	int scores;
	int End;

public:
	~Levels() {
		delete Plants;
		delete Zombie;
	}
	Levels(int noz,int zu,int numofplants) :Inven(numofplants),Zombie(new Zombie_Factory(noz,zu)), Plants(new Plant_Factory(Inven)) {
		Time = new times();
		numofZombie = noz;
		Plants->addZombies(Zombie);
		Waves = 3;
		End = 0;
		scores = 0;
		paused = true;
	}
	void pauselevel() {
		if (paused)
			paused = false;
		else
			paused = true;
		getPlants().pause();
		getZombies().pauseZomb();
		getSun().pauseSun();
	}
	Text getText() {
		return Levelnum;
	}
	int LevelEnd() {
		return End;
	}
	Inventory& getInventory() {
		return Inven;
	}
	Plant_Factory& getPlants() {
		return *Plants;
	}
	Zombie_Factory& getZombies() {
		return *Zombie;
	}
	Sun& getSun() {
		return su;
	}
	Sprite& getGrid() {
		return s_map;
	}
	int getscore() {
		return scores;
	}
	void setscore(int s) {
		scores=s;
	}
	void hitZomb() {
		for (int i = 0; i < Plants->getsize() - 1 ; i++)
		{
			for (int k = 0; k < Zombie->getsizeofzombies(); k++)
			{
				for (int j = 0; j < Plants->getPlant(i).getsize(); j++)
				{
					int y= Plants->getPlant(i).getPos(j).y;
					if (Plants->getPlant(i).getPos(j).x >= Zombie->getZombie(k).pos.x && Plants->getPlant(i).getPos(j).x-5 <= Zombie->getZombie(k).pos.x + 50 && Plants->getPlant(i).getPos(j).y <= Zombie->getZombie(k).pos.y && Plants->getPlant(i).getPos(j).y+70 >= Zombie->getZombie(k).pos.y) //&& plan[i]->getBulletPos(j).y > Zomb->getZombie(k).pos.y)
					{
						if (Zombie->getexists(k) && Plants->getPlant(i).getexist(j))
						{
							
							if (Plants->getPlant(i).getexist(j) && paused)
							{
								Zombie->getZombie(k).setHealth(1);
								if(Plants->exists(i))
								{
									if (Plants->getPlant(i).getindexof() == 5)
									{
										Zombie->getZombie(k).freezeZomb();
									}
								}

								if (Zombie->getZombie(k).getHealth() == 2)
								{
									Zombie->getZombie(k).headZ();
								}
								if (Zombie->getZombie(k).getHealth() == 0)
								{
									Zombie->getZombie(k).dieZ();
									scores += 10;
								}
							}
							Plants->getPlant(i).setexist(j);
						}


					}
				}
			}
		}
	}
	void hitPlant() {
		for (int i = 0; i < Plants->getsize() - 1; i++)
		{
				for (int k = 0; k < Zombie->getsizeofzombies(); k++)
				{
					if (Zombie->getexists(k) && Zombie->getZombie(k).getindex()!=2)
					{
						if (paused && Plants->getPlant(i).getindexof()!=5 && Zombie->getZombie(k).pos.x <= Plants->getPlant(i).getpos().x + 50 && Zombie->getZombie(k).pos.x >= Plants->getPlant(i).getpos().x - 50 && Zombie->getZombie(k).pos.y == Plants->getPlant(i).getpos().y && Zombie->getZombie(k).Eat.getElapsedTime().asSeconds() > 2) //> Zombie->getZombie(k).pos.x && Plants->getPlant(i).getBulletPos(j).x < Zombie->getZombie(k).pos.x + 100 && Plants->getPlant(i).getBulletPos(j).y == Zombie->getZombie(k).pos.y) //&& plan[i]->getBulletPos(j).y > Zomb->getZombie(k).pos.y)
						{
							Zombie->getZombie(k).move = false;
							Zombie->getZombie(k).Eat.restart();
							Plants->getPlant(i).setHealth(1);
							if (Plants->getPlant(i).getHealth() <= 0)
							{
								cout << "Destroyed";
								Plants->destroyplant(i);

							}
							if (Plants->exists(i) == false)
								Zombie->getZombie(k).move = true;
						}
					}

				}
			
		}
	}
	void CollectSun(Vector2i& pos) {
		for (int i = 0; i < su.getsize(); i++)
		{
			if (su.getexist(i))
			{
				if (pos.x >= su.getpos(i).x && pos.x <= su.getpos(i).x + HorizontalBox && pos.y >= su.getpos(i).y && pos.y <= su.getpos(i).y + verticalBox-30)
				{
					Inven.setsun();
					su.setexist(i);
				}

			}

		}
		for (int i = 0; i < Plants->getsize() - 1; i++)
		{
			for (int j = 0; j < Plants->getPlant(i).getsize(); j++)
			{
				if(Plants->getPlant(i).getexist(j) && Plants->getPlant(i).getsun())
				{
					if (pos.x >= Plants->getPlant(i).getPos(j).x&& pos.x <= Plants->getPlant(i).getPos(j).x + HorizontalBox && pos.y >= Plants->getPlant(i).getPos(j).y && pos.y <= Plants->getPlant(i).getPos(j).y + verticalBox-30 && Plants->getPlant(i).getexist(j))
					{
						Inven.setsun();
						Plants->getPlant(i).setexist(j);
					}
				}
			}
		}

	}

	virtual void spawnZombies() = 0;
};
