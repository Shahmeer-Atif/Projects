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
//Group Member 1: Shahmeer Atif 23i-0711 CS-G
//Group Member 2: Irfan Khalid  23i-2092 CS-G
class Zombies {
	public:
	Animation ZombieS;
	Animation ZombieD;
	Animation ZombieB;
	Animation ZombieE;
	Animation ZombieHL;
	Animation ZombieH;
	sf::Texture *ZombieT;
	Vector2f pos;
	int index;
	bool paused;
	bool exist;
	bool move;
	bool die;
	bool blast;
	int SpawnZ;
	bool head;
	int health;
	bool freez;
	int dance;
	Clock Eat;
	Clock Freeze;
public:
	virtual ~Zombies() {
		delete[] ZombieT;
	}
	void pauseZomb() {
		if (paused)
			paused = false;
		else
			paused = true;
	}
	int getSpawnZomb() {
		return SpawnZ;
	}
	void setindex(int i) {
		index = i;
	}
	int getindex() {
		return index;
	}
	void setSpawnZomb() {
		SpawnZ=0;
	}
	Zombies(int h = 5) {
		dance = 0;
		health = h;
		head = false;
		move = true;
		blast = false;
		die = false;
		exist = true;
		freez = false;
		paused = true;
	}
	void blastZ() {
		blast = true;
	}
	void dieZ() {
		die = true;
	}
	bool getdieZ() {
		return die;
	}
	void headZ() {
		head = true;
	}
	bool alive() {
		return exist;
	}
	void freezeZomb() {
		freez = true;
		Freeze.restart();
	}
	Sprite getZombie() {}
	virtual void draw(RenderWindow& window) {
		ZombieS.animate();
		ZombieHL.animate();
		ZombieE.animate();
		ZombieS.getSprite().setPosition(pos);
		ZombieB.getSprite().setPosition(pos);
		ZombieHL.getSprite().setPosition(pos);
		ZombieD.getSprite().setPosition(pos);
		ZombieE.getSprite().setPosition(pos);
		ZombieH.getSprite().setPosition(pos);
		if(blast || die)
		{
			if (blast)
			{
				ZombieB.animate();
				window.draw(ZombieB.getSprite());
				if (ZombieB.getInterval())
				{
					blast = false;
					exist = false;
				}
			}
			else if (die)
			{
				ZombieD.animate();
				window.draw(ZombieD.getSprite());
				if (ZombieD.getInterval())
					exist = false;
			}
		}
		else
		{
			if (head && move)
			{
				ZombieH.animate();
				window.draw(ZombieH.getSprite());
				if (ZombieH.getInterval())
					head = false;
			}
			if (!move)
			{
				ZombieE.animate();
				window.draw(ZombieE.getSprite());
			}
			else if (health > 2)
				window.draw(ZombieS.getSprite());
			else if (health < 3 && health>0)
				window.draw(ZombieHL.getSprite());
		}
	}
	int getHealth() {
		return health;
	}
	void setHealth(int i) {
		if (health - i >= 0)
			health -= i;
		else
			health = 0;
	}
	void setposition(int x, int y) {
		ZombieS.updateposition(pos);
		ZombieE.updateposition(pos);
	}
	virtual bool moveZombie() = 0;
};
class Simple_Zombie : public Zombies {
protected:
	Vector2f vel;
	Vector2f dir;
	float speed;

public:

	Simple_Zombie() :Zombies(5) {
		vel = { 0.0f,0.0f };
		dir = { -1.0f,0.0f };
		ZombieT=new Texture[6];
		ZombieT[0].loadFromFile("Images/assets/Spritesheets/nZombWalk.png");
		ZombieS.setFrame(ZombieT[0], 166, 144, 3652, 70);
		ZombieT[1].loadFromFile("Images/assets/Spritesheets/nZombEat.png");
		ZombieE.setFrame(ZombieT[1], 166, 144, 3486, 70);
		ZombieT[2].loadFromFile("Images/assets/Spritesheets/Zombdie.png");
		ZombieD.setFrame(ZombieT[2], 166, 144, 1660, 70);
		ZombieT[3].loadFromFile("Images/assets/Spritesheets/zomboom.png");
		ZombieB.setFrame(ZombieT[3], 166, 144, 2665, 70);
		ZombieT[4].loadFromFile("Images/assets/Spritesheets/zombhead.png");
		ZombieH.setFrame(ZombieT[4], 150, 186, 1529, 70);
		ZombieT[5].loadFromFile("Images/assets/Spritesheets/zombless.png");
		ZombieHL.setFrame(ZombieT[5], 166, 144, 2988, 70);
		speed = 1.25f;
		health = 4;
	}
	bool moveZombie() {
		if(paused)
		{
			if (freez)
			{
				if (Freeze.getElapsedTime().asSeconds() > 4)
				{
					freez = false;
				}
			}
			if (pos.x > -100 && move && !blast && !die && exist)
			{
				if (freez)
					vel = dir * ((speed / 2));
				else
					vel = dir * speed;
				pos += vel * 1.0f / 60.0f;
				ZombieS.updateposition(pos);
			}
			else if (pos.x <= -100 && move && !blast && !die && exist)
			{
				exist = false;
				return true;
			}
		}
		return false;
	}
};
class FootBall_Zombie : public Simple_Zombie {
	float speed;
public:

	FootBall_Zombie() {
		vel = { 0.0f,0.0f };
		dir = { -1.0f,0.0f };
		ZombieT = new Texture[6];
		ZombieT[0].loadFromFile("Images/assets/Spritesheets/bucHeadZombWalk.png");
		ZombieS.setFrame(ZombieT[0], 166, 144, 2490, 70);
		ZombieT[1].loadFromFile("Images/assets/Spritesheets/bucHeadZombEat.png");
		ZombieE.setFrame(ZombieT[1], 166, 144, 1826, 70);
		ZombieT[2].loadFromFile("Images/assets/Spritesheets/Zombdie.png");
		ZombieD.setFrame(ZombieT[2], 166, 144, 1660, 70);
		ZombieT[3].loadFromFile("Images/assets/Spritesheets/zomboom.png");
		ZombieB.setFrame(ZombieT[3], 166, 144, 2665, 70);
		ZombieT[4].loadFromFile("Images/assets/Spritesheets/zombhead.png");
		ZombieH.setFrame(ZombieT[4], 150, 186, 1529, 70);
		ZombieT[5].loadFromFile("Images/assets/Spritesheets/zombless.png");
		ZombieHL.setFrame(ZombieT[5], 166, 144, 2988, 70);
		speed = 2.25f;
		health = 6;
	}
	bool moveZombie() {
		if(paused)
		{
			if (rand() % 3)
				dir.x = -1;
			else
				dir.x = 1;
			if (freez)
			{
				if (Freeze.getElapsedTime().asSeconds() > 4)
				{
					freez = false;
				}
			}
			if (pos.x > -100 && move && !blast && !die && exist)
			{
				if (freez)
					vel = dir * ((speed / 2));
				else
					vel = dir * speed;
				pos += vel * 1.0f / 60.0f;
				ZombieS.updateposition(pos);
			}
			else if (pos.x <= -100 && move && !blast && !die && exist)
			{
				exist = false;
				return true;
			}
		}
		return false;
	}
};
class Flying_Zombie : public Simple_Zombie {
	float speed;
public:

	Flying_Zombie() {
		vel = { 0.0f,0.0f };
		dir = { -1.0f,0.0f };
		ZombieT = new Texture[6];
		ZombieT[0].loadFromFile("Images/assets/Spritesheets/FlyingZomb1.png");
		ZombieS.setFrame(ZombieT[0], 104, 160, 516, 0);
		ZombieS.setOrigin(0, 60);
		ZombieT[1].loadFromFile("Images/assets/Spritesheets/FlyingZomb1.png");
		ZombieE.setFrame(ZombieT[0], 104, 160, 516, 0);
		ZombieE.setOrigin(0, 60);
		ZombieT[2].loadFromFile("Images/assets/Spritesheets/FlyingZomb1.png");
		ZombieD.setFrame(ZombieT[0], 104, 160, 516, 0);
		ZombieD.setOrigin(0, 60);
		ZombieT[3].loadFromFile("Images/assets/Spritesheets/FlyingZomb1.png");
		ZombieB.setFrame(ZombieT[0], 104, 160, 516, 0);
		ZombieB.setOrigin(0, 60);
		ZombieT[4].loadFromFile("Images/assets/Spritesheets/FlyingZomb1.png");
		ZombieH.setFrame(ZombieT[0], 104, 160, 516, 0);
		ZombieH.setOrigin(0, 60);
		ZombieT[5].loadFromFile("Images/assets/Spritesheets/FlyingZomb1.png");
		ZombieHL.setFrame(ZombieT[0], 104, 160, 516, 0);
		ZombieHL.setOrigin(0, 60);
		health = 4;
		speed = 2.25f;
	}
	bool moveZombie() {
		if(paused)
		{
			if (freez)
			{
				if (Freeze.getElapsedTime().asSeconds() > 4)
				{
					freez = false;
				}
			}
			if (pos.x > -100 && move && !blast && !die && exist)
			{
				if (freez)
					vel = dir * ((speed / 2));
				else
					vel = dir * speed;
				pos += vel * 1.0f / 60.0f;
				ZombieS.updateposition(pos);

			}
			else if (pos.x <= -100 && move && !blast && !die && exist)
			{
				exist = false;
				return true;
			}
		}
		return false;
	}
	
};
class Dancing_Zombie : public Simple_Zombie {
public:

	Dancing_Zombie() {
		ZombieT = new Texture[6];
		ZombieT[0].loadFromFile("Images/assets/Spritesheets/DancinZomb1.png");
		ZombieS.setFrame(ZombieT[0], 160, 160, 800, 0);
		ZombieS.setOrigin(20, 50);
		ZombieT[1].loadFromFile("Images/assets/Spritesheets/nZombEat.png");
		ZombieE.setFrame(ZombieT[1], 166, 144, 3486, 70);
		ZombieT[2].loadFromFile("Images/assets/Spritesheets/Zombdie.png");
		ZombieD.setFrame(ZombieT[2], 166, 144, 1660, 70);
		ZombieT[3].loadFromFile("Images/assets/Spritesheets/zomboom.png");
		ZombieB.setFrame(ZombieT[3], 166, 144, 2665, 70);
		ZombieT[4].loadFromFile("Images/assets/Spritesheets/zombhead.png");
		ZombieH.setFrame(ZombieT[4], 150, 186, 1529, 70);
		ZombieT[5].loadFromFile("Images/assets/Spritesheets/zombless.png");
		ZombieHL.setFrame(ZombieT[5], 166, 144, 2988, 70);
		SpawnZ = 4;
		health = 4;
		speed = 5.0f;
	}
	bool moveZombie() {
		if(paused)
		{
			if (pos.x < 750 && dir.y == 0)
			{
				if (rand() % 10)
					dir.y = -1;
				else
					dir.y = 1;
			}
			if (freez)
			{
				if (Freeze.getElapsedTime().asSeconds() > 4)
				{
					freez = false;
				}
			}
			if (pos.x > -100 && move && !blast && !die && exist)
			{
				if (freez)
					vel = dir * ((speed / 2));
				else
					vel = dir * speed;
				pos += vel * 1.0f / 60.0f;
				ZombieS.updateposition(pos);
			}
			if (pos.y < 100)
			{
				dir.y *= -1;
			}
			else if (pos.y > 500)
				dir.y *= -1;
			else if (pos.x <= -100 && move && !blast && !die && exist)
			{
				exist = false;
				return true;
			}
		}
		return false;
	}
	
};