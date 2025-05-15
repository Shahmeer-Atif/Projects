#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Image.hpp"
#include <ctime>
#include <cstdlib> 
#include"PlantFactory.h"
#include"ZombieFactory.h"
#include"Inventory.h"
#include"Level.h"
#include"Global.h"
#include"Sun.h"
#include"time.h"
using namespace std;
using namespace sf;
//Group Member 1: Shahmeer Atif 23i-0711 CS-G
//Group Member 2: Irfan Khalid  23i-2092 CS-G
class BeginnersGarden : public Levels {
public:
	BeginnersGarden() :Levels(3, 1, 2)
	{
		Time->setCompareT(10);
		map_image.loadFromFile("images/assets/Background/level 1.jpg");
		map.loadFromImage(map_image);
		s_map.setTexture(map);
		s_map.setPosition(0, 0);
		font.loadFromFile("Images/SamdanEvil.ttf");
		Levelnum.setFont(font);
		Levelnum.setCharacterSize(30);
		Levelnum.setFillColor(sf::Color::Black);
		Levelnum.setString("Level 1: Beginners Garden");
		Levelnum.setPosition(820, 0);
		Waves = 3;
	}
	void spawnZombies() {
		hitPlant();
		hitZomb();
		bool b = true;
		if (Time->getClock().getElapsedTime().asSeconds() > Time->getCompareT())
		{
			if (Zombie->getnumofzombies() != Zombie->getsizeofzombies() || Zombie->getnumofzombies() == 0)
			{
				getZombies().addZombie();
				for (int i = 0; i < Zombie->getsizeofzombies(); i++)
				{
					if (Zombie->getexists(i) && Zombie->getZombie(i).pos.x < 800 && Zombie->getZombie(i).getSpawnZomb())
					{
						Zombie->getZombie(i).setSpawnZomb();
						for (float k = 0, x = Zombie->getZombie(i).pos.x - 100; k < 2; k++, x += 200)
						{
							for (float z = 0, y = Zombie->getZombie(i).pos.y - 100; z < 2; z++, y += 200)
							{
								if (y >= 100 && y <= 600)
									Zombie->addZombie(x, y, 1);
							}
						}
					}
				}

				b = false;
			}
			else
			{
				for (int i = 0; i < Zombie->getsizeofzombies() && b; i++)
				{
					if (!(Zombie->getexists(i)))
						b = true;
					else
						b = false;
				}
			}
			if (b)
			{
				Waves--;
				numofZombie++;
				Time->getClock().restart();
				Time->setCompareT(3);
				if (Waves <= 0 && End == 0)
				{
					End = 1;
				}
				else
				{
					cout << "\nWave: " << Waves << endl;

					delete Zombie;
					Zombie = new Zombie_Factory(numofZombie);
					Plants->addZombies(Zombie);
				}
			}
		}



	}
};

class ZombieOutskirts : public Levels {
public:
	ZombieOutskirts() :Levels(3, 5, 3)
	{
		Time->setCompareT(10);
		map_image.loadFromFile("images/assets/Background/level 2.png");
		map.loadFromImage(map_image);
		s_map.setTexture(map);
		s_map.setPosition(0, 0);
		font.loadFromFile("Images/SamdanEvil.ttf");
		Levelnum.setFont(font);
		Levelnum.setCharacterSize(30);
		Levelnum.setFillColor(sf::Color::Black);
		Levelnum.setString("Level 2: Zombie Outskirts");
		Levelnum.setPosition(820, 0);
		Waves = 3;
	}
	void spawnZombies() {
		hitPlant();
		hitZomb();
		bool b = true;
		if (Time->getClock().getElapsedTime().asSeconds() > Time->getCompareT())
		{
			if (Zombie->getnumofzombies() != Zombie->getsizeofzombies() || Zombie->getnumofzombies() == 0)
			{
				getZombies().addZombie();
				for (int i = 0; i < Zombie->getsizeofzombies(); i++)
				{
					if (Zombie->getexists(i) && Zombie->getZombie(i).pos.x < 800 && Zombie->getZombie(i).getSpawnZomb())
					{
						Zombie->getZombie(i).setSpawnZomb();
						for (float k = 0, x = Zombie->getZombie(i).pos.x - 100; k < 2; k++, x += 200)
						{
							for (float z = 0, y = Zombie->getZombie(i).pos.y - 100; z < 2; z++, y += 200)
							{
								if (y >= 100 && y <= 600)
									Zombie->addZombie(x, y, 1);
							}
						}
					}
				}

				b = false;
			}
			else
			{
				for (int i = 0; i < Zombie->getsizeofzombies() && b; i++)
				{
					if (!(Zombie->getexists(i)))
						b = true;
					else
						b = false;
				}
			}
			if (b)
			{
				Waves--;
				numofZombie++;
				Time->getClock().restart();
				Time->setCompareT(3);
				if (Waves <= 0 && End == 0)
				{
					cout << "END";
					End = 1;
				}
				else
				{
					bool p = false;
					for (int k = 0; k < Zombie->getsizeofzombies(); k++)
					{
						if (Zombie->getZombie(k).paused)
							p = true;
					}
					cout << "\nWave: " << Waves << endl;
					delete Zombie;
					Zombie = new Zombie_Factory(numofZombie);
					if (!p)
					Zombie->pauseZomb();
					Plants->addZombies(Zombie);
				}
			}
		}



	}
};

class SunflowerFeilds : public Levels {
public:
	SunflowerFeilds() :Levels(3, 5, 4)
	{
		Time->setCompareT(10);
		map_image.loadFromFile("images/assets/Background/level 3.jpg");
		map.loadFromImage(map_image);
		s_map.setTexture(map);
		s_map.setPosition(0, 0);
		font.loadFromFile("Images/SamdanEvil.ttf");
		Levelnum.setFont(font);
		Levelnum.setCharacterSize(30);
		Levelnum.setFillColor(sf::Color::Black);
		Levelnum.setString("Level 3: SunflowerFeilds");
		Levelnum.setPosition(820, 0);
		Waves = 3;
	}
	void spawnZombies() {
		hitPlant();
		hitZomb();
		bool b = true;
		if (Time->getClock().getElapsedTime().asSeconds() > Time->getCompareT())
		{
			if (Zombie->getnumofzombies() != Zombie->getsizeofzombies() || Zombie->getnumofzombies() == 0)
			{
				getZombies().addZombie();
				for (int i = 0; i < Zombie->getsizeofzombies(); i++)
				{
					if (Zombie->getexists(i) && Zombie->getZombie(i).pos.x < 800 && Zombie->getZombie(i).getSpawnZomb())
					{
						Zombie->getZombie(i).setSpawnZomb();
						for (float k = 0, x = Zombie->getZombie(i).pos.x - 100; k < 2; k++, x += 200)
						{
							for (float z = 0, y = Zombie->getZombie(i).pos.y - 100; z < 2; z++, y += 200)
							{
								if (y >= 100 && y <= 600)
									Zombie->addZombie(x, y, 1);
							}
						}
					}
				}

				b = false;
			}
			else
			{
				for (int i = 0; i < Zombie->getsizeofzombies() && b; i++)
				{
					if (!(Zombie->getexists(i)))
						b = true;
					else
						b = false;
				}
			}
			if (b)
			{
				Waves--;
				numofZombie++;
				Time->getClock().restart();
				Time->setCompareT(3);
				if (Waves <= 0 && End == 0)
				{
					End = 1;
				}
				else
				{
					cout << "\nWave: " << Waves << endl;

					delete Zombie;
					Zombie = new Zombie_Factory(numofZombie);
					Plants->addZombies(Zombie);
				}
			}
		}



	}
};


class FoggyForest : public Levels {
public:
	FoggyForest() :Levels(5, 5, 7)
	{
		Time->setCompareT(10);
		map_image.loadFromFile("images/assets/Background/level 4.jpg");
		map.loadFromImage(map_image);
		s_map.setTexture(map);
		s_map.setPosition(0, 0);
		font.loadFromFile("Images/SamdanEvil.ttf");
		Levelnum.setFont(font);
		Levelnum.setCharacterSize(30);
		Levelnum.setFillColor(sf::Color::Black);
		Levelnum.setString("Level 3: FoggyForest");
		Levelnum.setPosition(820, 0);
		Waves = 3;
	}
	void spawnZombies() {
		hitPlant();
		hitZomb();
		bool b = true;
		if (Time->getClock().getElapsedTime().asSeconds() > Time->getCompareT())
		{
			if (Zombie->getnumofzombies() != Zombie->getsizeofzombies() || Zombie->getnumofzombies() == 0)
			{
				getZombies().addZombie();
				for (int i = 0; i < Zombie->getsizeofzombies(); i++)
				{
					if (Zombie->getexists(i) && Zombie->getZombie(i).pos.x < 800 && Zombie->getZombie(i).getSpawnZomb())
					{
						Zombie->getZombie(i).setSpawnZomb();
						for (float k = 0, x = Zombie->getZombie(i).pos.x - 100; k < 2; k++, x += 200)
						{
							for (float z = 0, y = Zombie->getZombie(i).pos.y - 100; z < 2; z++, y += 200)
							{
								if (y >= 100 && y <= 600)
									Zombie->addZombie(x, y, 1);
							}
						}
					}
				}

				b = false;
			}
			else
			{
				for (int i = 0; i < Zombie->getsizeofzombies() && b; i++)
				{
					if (!(Zombie->getexists(i)))
						b = true;
					else
						b = false;
				}
			}
			if (b)
			{
				Waves--;
				numofZombie++;
				Time->getClock().restart();
				Time->setCompareT(3);
				if (Waves <= 0 && End == 0)
				{
					End = 1;
				}
				else
				{
					cout << "\nWave: " << Waves << endl;

					delete Zombie;
					Zombie = new Zombie_Factory(numofZombie);
					Plants->addZombies(Zombie);
				}
			}
		}



	}
};