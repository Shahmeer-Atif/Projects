#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Image.hpp"
#include <ctime>
#include <cstdlib> 
#include"Global.h"
#include"Inventory.h"
#include"ZombieFactory.h"
#include"Animation.h"
#include"Sun.h"
#include"Plants.h"
using namespace std;
using namespace sf;
class Plant_Factory {
	Plants** plan;
	Zombie_Factory* Zomb;
	Inventory* Inven;
	int size;
	bool* exist;
	int index;
public:
	Plant_Factory(Inventory& I) :Inven(&I), size(1), plan(new Plants* [size]), index(-1), exist(new bool[100]), Zomb(nullptr) {
		for (int i = 0; i < 100; i++)
			exist[i] = false;
	}
	~Plant_Factory() {
		delete[] exist;
		for (int i = 0; i < size - 1; i++)
			delete plan[i];
		delete[] plan;
	}
	void addZombies(Zombie_Factory* Z = nullptr) {
		Zomb = Z;
		for (int i = 0; i < size - 1; i++)
			plan[i]->addZombie(Z);
	}
	void addplant(int& x, int& y, bool** Feild) {

		this->index = Inven->getindex();
		if (index >= 0 && index <= Inven->getnumofplants())
		{
			if (checkRange(x, y, Feild))
			{
				if (size != 1)
				{
					Plants** temp = new Plants * [size];
					for (int i = 0; i < size; i++)
						temp[i] = plan[i];
					delete[] plan;
					plan = new Plants * [size];
					for (int i = 0; i < size; i++)
						plan[i] = temp[i];
					delete[] temp;
				}

				if (index == 0)
					plan[size - 1] = new PeaShooter(Zomb);
				else if (index == 1)
					plan[size - 1] = new Sunflower();
				if (index == 2)
					plan[size - 1] = new Wallnut(Zomb);
				else if (index == 3)
					plan[size - 1] = new CherryBomb(Zomb);
				else if (index == 4)
					plan[size - 1] = new Repeater(Zomb);
				else if (index == 5)
					plan[size - 1] = new SnowPea(Zomb);
				else if (index == 6)
					plan[size - 1] = new FumeShroom(Zomb);
				plan[size - 1]->setindex(index);
				exist[size - 1] = true;
				plan[size - 1]->getpos().x = x;
				plan[size - 1]->getpos().y = y;
				plan[size - 1]->setposition(x, y);
				plan[size - 1]->Action();
				size++;

				Inven->setindex(-1);

			}
		}
	}
	bool exists(int i) const {
		return exist[i];
	}
	void destroyplant(int i) {
		exist[i] = false;
	}
	int getsize() const {
		return size;
	}
	Sprite getSprite(int i) const {
		return plan[i]->getPlant();
	}
	void drawPlants(RenderWindow& w) const
	{
		for (int i = 0; i < size - 1; i++)
		{
			if (exists(i))
			{
				plan[i]->Action();
				w.draw(plan[i]->getPlant());
				plan[i]->draw(w);
			}
			if (!(plan[i]->alive()))
				exist[i] = false;
		}

	}
	Plants& getPlant(int x) const {
		for (int i = 0; i < size; i++)
		{
			if (x == i)
				return *(plan[i]);
		}
	}
	bool checkRange(int& x, int& y, bool** Feild) {
		for (int i = verticalBox, a = 0; i <= verticalBox * 5; i += verticalBox, a++)
		{
			for (int j = HorizontalBox, b = 0; j <= HorizontalBox * 9; j += HorizontalBox, b++)
			{
				if (y > i && y < i + verticalBox && x > j && x < j + HorizontalBox && Feild[a][b])
				{
					Feild[a][b] = false;
					x = j;
					y = i;
					cout << "x: " << x << endl;
					cout << "y: " << y << endl << endl;
					return true;
				}
			}
		}
		return false;
	}
	void checkFeild(bool** Feild) {
		for (int k = 0; k < size - 1; k++)
		{
			if (exist[k] == false)
			{
				for (int i = verticalBox, a = 0; i <= verticalBox * 5; i += verticalBox, a++)
				{
					for (int j = HorizontalBox, b = 0; j <= HorizontalBox * 9; j += HorizontalBox, b++)
					{
						if (getPlant(k).getpos().y == i && getPlant(k).getpos().x == j && !Feild[a][b])
						{
							Feild[a][b] = true;
						}
					}
				}
			}
		}
	}
	void pause() {
		for (int i = 0; i < size - 1; i++)
			plan[i]->pauseplants();
	}
	int getsize() {
		return size;
	}

};
