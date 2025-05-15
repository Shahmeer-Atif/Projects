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
using namespace std;
using namespace sf;
//Group Member 1: Shahmeer Atif 23i-0711 CS-G
//Group Member 2: Irfan Khalid  23i-2092 CS-G
class Plants {
protected:
	Zombie_Factory* Zomb;
	Animation PeaS;
	sf::Texture PeaT;
	Vector2f pos;
	bool paused;
	bool sun;
	int index;
	bool exist;
	int Price;
	int health;
	bool move = false;
public:
	virtual ~Plants(){}
	Plants(int P=100,int H = 4) :Price(P), health(H) {
		exist = true;
		sun = false;
		index = 0;
		paused = true;

	}
	void pauseplants() {
		if (paused)
			paused = false;
		else
			paused = true;
	}
	void addZombie(Zombie_Factory* Z) {
		Zomb = Z;
	}
	bool getsun() {
		return sun;
	}
	bool alive() {
		return exist;
	}
	Sprite getPlant() {
		PeaS.animate();
		return PeaS.getSprite();
	}
	Vector2f& getpos() {
		return pos;
	}
	int getHealth() {
		return health;
	}
	void setindex(int i) {
		index = i;
	}
	int getindexof() {
		return index;
	}
	void setHealth(int i) {
		if (health - i >= 0)
			health -= i;
		else
			health = 0;
	}
	void setposition(int x, int y) {
		pos.x = x;
		pos.y = y;
		PeaS.getSprite().setPosition(pos);
	}
	
	virtual void Action() = 0;
	virtual Sprite getSprite(int i) = 0;
	virtual int getexist(int i) = 0;
	virtual void setexist(int i) = 0;
	virtual int getsize() = 0;
	virtual Vector2f& getPos(int i) = 0;
	virtual void draw(RenderWindow& window)=0;
	
};
class Shooter :public Plants {
protected:
	int numofbullets;
	bool freeze = false;;
	Sprite Bullet;
	Texture BulletT;
	Vector2f* vel;
	Vector2f* posS;
	Vector2f* dir;
	float speed = 10.0f;
	Clock Delay;
	bool* bexist;
	int current;
	bool sun;
public:

	~Shooter() {
		delete[] vel;
		delete[] posS;
		delete[] dir;
		delete[] bexist;
	}
	Shooter() {
		numofbullets = 10;
		delete[] bexist;
		sun = false;
		bexist = new bool[numofbullets];
		BulletT.loadFromFile("Images/pea.png");
		vel = new Vector2f[numofbullets];
		dir = new Vector2f[numofbullets];
		posS = new Vector2f[numofbullets];
			Bullet.setTexture(BulletT);
			Bullet.setTextureRect(sf::IntRect(0, 0, 28, 28));
		for (int i = 0; i < numofbullets; i++)
		{
			vel[i] = { 0.0f,0.0f };
			dir[i] = { 1.0f,0.0f };
			bexist[i] = false;
		}
		current = 0;
	}

};
class PeaShooter :public Shooter{

public:
	PeaShooter(Zombie_Factory* Z = nullptr) {
		Zomb = Z;
		PeaT.loadFromFile("Images/assets/Spritesheets/peashooter.png");
		PeaS.setFrame(PeaT, 71, 71, 923, 0);
		sun = false;
		numofbullets = 10;

	}
	void Action() {
		if(paused)
		{
			bool shoot = false;
			for (int k = 0; k < Zomb->getsizeofzombies(); k++)
			{
				if (Zomb->getZombie(k).pos.y >= pos.y && Zomb->getZombie(k).pos.y <= pos.y + 70 && Zomb->getexists(k))
				{
					shoot = true;
				}

			}
			for (int i = 0; i < numofbullets; i++)
			{
				if (bexist[i] == false)
				{
					current = i;
					break;
				}
			}
			if (Delay.getElapsedTime().asSeconds() > 2 && current < numofbullets)
			{
				if (shoot)
				{
					Delay.restart();
					posS[current].x = pos.x + 64;
					posS[current].y = pos.y;
					bexist[current] = true;
					current++;
				}


			}
			for (int i = 0; i < numofbullets; i++)
			{
				if (bexist[i])
				{
					if (posS[i].x <= HorizontalBox * 11)
					{
						vel[i] = dir[i] * speed;
						posS[i] += vel[i] * 1.0f / 60.0f;
					}
					else
						bexist[i] = false;
				}

			}
		}
	}
	Sprite getSprite(int i) {
		if (bexist[i])
		{
			Bullet.setPosition(posS[i]);
			return Bullet;
		}
	}
	int getexist(int i) {
		return bexist[i];
	}
	void setexist(int i) {
		bexist[i] = false;
	}
	int getsize() {
		return numofbullets;
	}
	Vector2f& getPos(int i) {
		if (bexist[i])
			return posS[i];
	}
	void draw(RenderWindow& window) {
		for (int i = 0; i < numofbullets; i++)
		{
			if (bexist[i])
			{
				Bullet.setPosition(posS[i]);
				window.draw(Bullet);
			}
		}
	}
};
class Repeater :public PeaShooter {
	Clock Interval;
	int count;
	bool shoot;
public:
	Repeater(Zombie_Factory* Z = nullptr) {
		Zomb = Z;
		count = 0;
		PeaT.loadFromFile("Images/assets/Spritesheets/repeater.png");
		PeaS.setFrame(PeaT, 71, 71, 1065, 0);
		numofbullets = 10;
		shoot = false;
	}
	void Action() {
		if (paused)
		{
			for (int k = 0; k < Zomb->getsizeofzombies(); k++)
			{
				if (Zomb->getZombie(k).pos.y >= pos.y && Zomb->getZombie(k).pos.y <= pos.y + 70 && Zomb->getexists(k))
				{
					shoot = true;
				}

			}
			if (Interval.getElapsedTime().asSeconds() > 1.7)
			{
				for (int i = 0; i < 10; i++)
				{
					if (bexist[i] == false)
					{
						current = i;
						break;
					}
				}
				if (Delay.getElapsedTime().asSeconds() > 0.2 && current < numofbullets)
				{
					if (shoot)
					{
						count++;
						Delay.restart();
						posS[current].x = pos.x + 64;
						posS[current].y = pos.y;
						bexist[current] = true;
						current++;
					}


				}
				if (count >= 2)
				{
					shoot = false;
					count = 0;
					Interval.restart();
				}
			}
			for (int i = 0; i < numofbullets; i++)
			{
				if (bexist[i])
				{
					if (posS[i].x <= HorizontalBox * 11)
					{
						vel[i] = dir[i] * speed;
						posS[i] += vel[i] * 1.0f / 60.0f;
					}
					else
						bexist[i] = false;
				}

			}

		}
	}
};
class SnowPea :public PeaShooter {

public:
	SnowPea(Zombie_Factory* Z = nullptr) {
		Zomb = Z;
		PeaT.loadFromFile("Images/assets/Spritesheets/snowpea.png");
		PeaS.setFrame(PeaT, 71, 71, 1065, 0);
		numofbullets = 10;
		BulletT.loadFromFile("Images/icepea.png");
		Bullet.setTexture(BulletT);
		Bullet.setTextureRect(sf::IntRect(0, 0, 56, 34));
		freeze = true;
	}

};
class FumeShroom :public PeaShooter {

public:
	FumeShroom(Zombie_Factory* Z = nullptr) {
		Zomb = Z;
		PeaT.loadFromFile("Images/assets/Spritesheets/fumeshroom.png");
		PeaS.setFrame(PeaT, 71, 71, 0, 0);
		numofbullets = 10;
		BulletT.loadFromFile("Images/fume.gif");
		Bullet.setTexture(BulletT);
		Bullet.setTextureRect(sf::IntRect(0, 0, 51, 45));
		freeze = false;
	}
	void Action() {
		if (paused)
		{
			bool shoot = false;
			for (int k = 0; k < Zomb->getsizeofzombies(); k++)
			{
				if (Zomb->getZombie(k).pos.y >= pos.y && Zomb->getZombie(k).pos.y <= pos.y + 70 && pos.x<=Zomb->getZombie(k).pos.x && pos.x+300 >= Zomb->getZombie(k).pos.x && Zomb->getexists(k))
				{
					shoot = true;
				}

			}
			for (int i = 0; i < numofbullets; i++)
			{
				if (bexist[i] == false)
				{
					current = i;
					break;
				}
			}
			if (Delay.getElapsedTime().asSeconds() > 1 && current < numofbullets)
			{
				if (shoot)
				{
					Delay.restart();
					posS[current].x = pos.x + 64;
					posS[current].y = pos.y;
					bexist[current] = true;
					current++;
				}


			}
			for (int i = 0; i < numofbullets; i++)
			{
				if (bexist[i])
				{
					if (posS[i].x <= HorizontalBox * 11)
					{
						vel[i] = dir[i] * speed;
						posS[i] += vel[i] * 1.0f / 60.0f;
					}
					else
						bexist[i] = false;
				}

			}
		}
	}

};
class CherryBomb :public PeaShooter {
	Clock Boom;
public:
	CherryBomb(Zombie_Factory* Z=nullptr) {
		Zomb = Z;
		PeaT.loadFromFile("Images/assets/Spritesheets/explode3.png");
		PeaS.setFrame(PeaT, 200, 200, 5607, 70);
		numofbullets = 0;
	}
	void Action() {
		if (paused)
		{
			if (PeaS.getInterval())
				exist = false;
			int x = (pos.x / 100) * 100;
			int y = (pos.y / 100) * 100;
			if (Boom.getElapsedTime().asSeconds() > 1.75 && exist)
			{
				for (int k = 0; k < Zomb->getsizeofzombies(); k++)
				{
					if (x - 100 < Zomb->getZombie(k).pos.x && x + 100 >= Zomb->getZombie(k).pos.x && y - 90 < Zomb->getZombie(k).pos.y && y + 100 >= Zomb->getZombie(k).pos.y)
					{
						Zomb->getZombie(k).setHealth(10);
						if (Zomb->getZombie(k).getHealth() == 0)
							Zomb->getZombie(k).blastZ();
					}

				}
			}
		}
	}
		
};
class Sunflower :public  Plants{
	Sun power;
public:
	Sunflower() {
		PeaT.loadFromFile("Images/assets/Spritesheets/sunf.png");
		PeaS.setFrame(PeaT, 71, 71, 1065, 0);
		power.setspawntime(5);
		sun = true;
	}
	Sprite getSprite(int i) {
		return power.getSun(i);
	}
	Vector2f& getPos(int i) {
		return power.getpos(i);
	}
	int getsize(){
		return power.getsize();
	}
	int getexist(int i) {
		return power.getexist(i);
	}
	void Action() {
		if(paused)
		power.addSun(pos.x+rand()%20,pos.y+rand()%30);
		else
		power.pauseSun();

	}
	void setexist(int i) {
		power.setexist(i);
	}
	void draw(RenderWindow& window) {
		for (int i = 0; i < power.getsize(); i++)
		{
			if (power.getexist(i))
			{
				window.draw(power.getSun(i));
			}
		}
	}

};
class Wallnut :public PeaShooter {
	Vector2f vel;
	Vector2f dir;
	Vector2f newpos;
	float speed = 100.0f;
	int move;
	bool b,c;
public:
	Wallnut(Zombie_Factory *Z=nullptr){
		Zomb = Z;

		PeaT.loadFromFile("Images/assets/Spritesheets/wallnut.png");
		PeaS.setFrame(PeaT, 71, 71, 1136, 0);
		numofbullets = 0;
		speed = 10.0f;
		b = false;
		c = true;
		vel = { 0.0f,0.0f };
		dir = { 1.0f,0.0f };
		newpos.x = pos.x;
		newpos.y = pos.y;
	}
	void Action() {
		if (paused)
		{
			if (c)
			{
				newpos.x = pos.x;
				newpos.y = pos.y;
				c = false;
			}
			if (newpos.x <= HorizontalBox * 11)
			{
				vel = dir * speed;
				newpos += vel * 1.0f / 60.0f;
				PeaS.updateposition(newpos);
				PeaS.getSprite().setPosition(newpos);
			}
			else
				exist = false;
			if (Zomb != nullptr)
			{
				for (int i = 0; i < Zomb->getsizeofzombies() && exist; i++)
				{
					if (!Zomb->getZombie(i).getdieZ() && Zomb->getZombie(i).getindex()!=2)
					{
						if (newpos.x >= Zomb->getZombie(i).pos.x - 30 && newpos.x <= Zomb->getZombie(i).pos.x + 100 && newpos.y >= Zomb->getZombie(i).pos.y - 50 && newpos.y <= Zomb->getZombie(i).pos.y + 50)
						{
							Zomb->getZombie(i).dieZ();
							if (b == false)
							{
								if (rand() % 2)
									dir.y = 1;
								else
									dir.y = -1;
							}
							dir.y *= -1;
							b = true;

						}
					}
				}
			}
			if (newpos.y < 100)
			{
				dir.y *= -1;
			}
			else if (newpos.y > 500)
				dir.y *= -1;
		}
	}
	int getexist() {
		return move;
	}
};
