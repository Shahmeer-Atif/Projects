#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Image.hpp"
#include <ctime>
#include <cstdlib> 
#include"Global.h"
#include"Animation.h"
using namespace std;
using namespace sf;
class Sun {
protected:
	Animation SUNS;
	Clock time;
	Clock Animate;
	sf::Texture SunT;
	Vector2f *pos;
	bool paused;
	int size;
	int spawn;
	int current;
	int* exist;
public:

	Sun(int t=10) :spawn(t),size(0){
		pos = new Vector2f[size];
		SunT.loadFromFile("Images/assets/Spritesheets/sun.png");
		SUNS.setFrame(SunT, 78, 78, 1716, 0);
		paused = true;
	}
	~Sun() {
		delete[] pos;
		delete[] exist;
	}
	void addSun(int x = (rand() % 10 + 1) * 100, int y = (rand() % 6 + 1)*100) {
		if (paused)
		{
			if (time.getElapsedTime().asSeconds() > spawn)
			{
				time.restart();
				size++;
				int* temp1 = new int[size];
				for (int i = 0; i < size - 1; i++)
					temp1[i] = exist[i];
				delete[] exist;
				exist = new int[size];
				for (int i = 0; i < size - 1; i++)
					exist[i] = temp1[i];
				delete[] temp1;
				exist[size - 1] = 1;
				Vector2f* temp = new Vector2f[size];
				for (int i = 0; i < size; i++)
					temp[i] = pos[i];
				delete[] pos;
				pos = new Vector2f[size];
				for (int i = 0; i < size; i++)
					pos[i] = temp[i];
				delete[] temp;
				pos[size - 1].x = x;
				pos[size - 1].y = y;
			}
		}
		else
			time.restart();
	}
	Vector2f& getpos(int i) {
		return pos[i];
	}
	void pauseSun() {
		if (paused)
			paused = false;
		else
			paused = true;
	}
	int getexist(int i) {
		return exist[i];
	}
	void setexist(int i) {
		exist[i]=0;
	}
	void setspawntime(int t) {
		spawn = t;
	}
	Sprite getSun(int i) {

		SUNS.animate();
		SUNS.getSprite().setPosition(pos[i]);
		return SUNS.getSprite();
	}
	int getsize() {
		return size;
	}
};
