#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Image.hpp"
#include <ctime>
#include <cstdlib> 
#include"Global.h"
#include"Animation.h"
#include"Zombies.h"
using namespace std;
using namespace sf;
class Zombie_Factory {
	Zombies** Zomb;
	int numofzombies;
	int zombiesunlocked;
	Clock Delay;
	bool pause;
	int size;
	bool* exist;
	int danZ;
	bool b = true;
public:
	Zombie_Factory(int noz = 3, int zu = 1) :size(0), Zomb(new Zombies* [size]), exist(new bool[100]) {
		zombiesunlocked = zu;
		for (int i = 0; i < 100; i++)
			exist[i] = false;
		numofzombies = noz;
		danZ = 0;
		pause = false;
	}
	~Zombie_Factory() {
		delete[] exist;
		for (int i = 0; i < size; i++)
			delete Zomb[i];
		delete[] Zomb;
	}
	void addZombie(float x = HorizontalBox * 11, float y = 100 * (rand() % 5 + 1), int dance = 0) {
		srand(time(0));
		int time = 5;
			if (pause)
				Delay.restart();
		if (y >= 100 && y <= 600)
		{
		}
		else
		{
			dance--;
		}
		numofzombies += dance;
		if (Delay.getElapsedTime().asSeconds() > time && size <= numofzombies || dance)
		{
			int index = rand() % 7;
			while (index >= zombiesunlocked)
				index = rand() % 7;
			size++;
			Zombies** temp = new Zombies * [size];
			for (int i = 0; i < size; i++)
				temp[i] = Zomb[i];
			delete[] Zomb;
			Zomb = new Zombies * [size];
			for (int i = 0; i < size; i++)
				Zomb[i] = temp[i];
			delete[] temp;
			if (dance)
			{
				Zomb[size - 1] = new Simple_Zombie();
				Zomb[size - 1]->setindex(0);
			}
			else if (index <= 1)
			{
				Zomb[size - 1] = new Simple_Zombie();
				Zomb[size - 1]->setindex(0);
			}
			else if (index == 2)
			{
				Zomb[size - 1] = new FootBall_Zombie();
				Zomb[size - 1]->setindex(1);
			}
			else if (index == 3)
			{
				Zomb[size - 1] = new Flying_Zombie();
				Zomb[size - 1]->setindex(2);
			}
			else if (index == 4)
			{
				Zomb[size - 1] = new Dancing_Zombie();
				Zomb[size - 1]->setindex(3);
			}
			exist[size - 1] = true;
			int r = rand() % 5 + 1;
			Zomb[size - 1]->pos.x = x;
			Zomb[size - 1]->pos.y = y;
			Delay.restart();
		}

	}
	bool DrawZombie(RenderWindow& window) {
		bool life = false;
		for (int i = 0; i < size; i++)
		{
			if (exist[i])
			{
				if (Zomb[i]->moveZombie())
					life = true;
				Zomb[i]->draw(window);
				if (!Zomb[i]->alive())
					exist[i] = false;
			}
		}
		return life;
	}
	Zombies& getZombie(int i) {
		return *Zomb[i];
	}
	bool getexists(int i) {
		if (exist[i])
			return true;
		else
			return false;
	}
	void destroyZombie(int i) {
		exist[i] = false;
	}
	int getnumofzombies() {
		return numofzombies;
	}
	int getsizeofzombies() {
		return size;
	}
	void pauseZomb() {
		if (pause)
			pause = false;
		else
			pause = true;
		for (int i = 0; i < size; i++)
			Zomb[i]->pauseZomb();
	}
	int getsize() {
		return size;
	}
};
