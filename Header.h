#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Image.hpp"
#include <ctime>
#include <cstdlib> 
using namespace std;
using namespace sf;

int verticalBox = 100;
int HorizontalBox = 100;

struct coordinates {
	float x;
	float y;
	void setcoordinates(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

class Zombies {
public:
	sf::Sprite ZombieS;
	sf::Texture ZombieT;
	Vector2f vel = { 0.0f,0.0f };
	Vector2f pos;
	Vector2f dir = {-1.0f,0.0f};
	int health;
	float speed;
	coordinates co;
public:
	Zombies(int h = 5) {
		health = h;
	}
	virtual  ~Zombies() {

	}
	Sprite getZombie() {
		return ZombieS;
	}
	int getHealth() {
		return health;
	}
	void setposition(int x, int y) {
		co.setcoordinates(x, y);
		ZombieS.setPosition(co.x, co.y);
	}
};
class Simple_Zombie: public Zombies {
public:
	~Simple_Zombie() {

	}
	Simple_Zombie():Zombies(5) {
		ZombieT.loadFromFile("Images/Zombie_alpha.png");
		ZombieS.setTexture(ZombieT);
		ZombieS.setTextureRect(sf::IntRect(0, -30, 166, 174));
		speed = 20.0f;
	}

};
class Zombie_Factory {
	Zombies** Zomb;
	int numofzombies;
	Clock Delay;
	int size;
	bool* exist;

public:
	Zombie_Factory(int noz) :size(0), Zomb(new Zombies* [size]), exist(new bool[100]) {
		for (int i = 0; i < 100; i++)
			exist[i] = false;

		numofzombies = noz;
	}
	~Zombie_Factory() {
		delete[] exist;
		delete[] Zomb;
	}
	void addZombie() {
			srand(time(0));
			int time = rand() %  10+ 5;
		if(Delay.getElapsedTime().asSeconds()>time && size<numofzombies)
		{
			size++;
			Zombies** temp = new Zombies * [size];
			for (int i = 0; i < size; i++)
				temp[i] = Zomb[i];
			delete[] Zomb;
			Zomb = new Zombies * [size];
			for (int i = 0; i < size; i++)
				Zomb[i] = temp[i];
			delete[] temp;

			int index = 0;
			if (index == 0)
				Zomb[size - 1] = new Simple_Zombie();

			exist[size - 1] = true;
			int r = rand() % 5;
			Zomb[size-1]->pos.x = HorizontalBox * 9;
			Zomb[size-1]->pos.y = verticalBox * r;
			Zomb[size-1]->ZombieS.setPosition(Zomb[size-1]->pos);
			Delay.restart();
		}
		
	}
	void Update() {
		for(int i=0;i<size;i++)
		{
			if (Zomb[i]->pos.x >= HorizontalBox)
			{
				Zomb[i]->vel = Zomb[i]->dir * Zomb[i]->speed;
				Zomb[i]->pos += Zomb[i]->vel * 1.0f / 60.0f;
				Zomb[i]->ZombieS.setPosition(Zomb[i]->pos);
			}
		}
	}
	void DrawZombie(RenderWindow& window) {
		for(int i=0;i<size;i++)
		{
			window.draw(Zomb[i]->ZombieS);
		}
		
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
	int getnumofzombies() {
		return numofzombies;
	}
	int getsizeofzombies() {
		return size;
	}
};
class Inventory {
	Sprite BackGround;
	Texture Back;
	sf::Sprite* PlantS;
	sf::Texture* PlantT;
	int index;
	bool* select;
	int numofPlants;
public:

	Inventory() {
		numofPlants = 4;
		index = -1;
		select = new bool[numofPlants];
		for (int i = 0; i < numofPlants; i++)
			select[i] = false;
		PlantS = new Sprite[numofPlants];
		PlantT = new Texture[numofPlants];

		PlantT[0].loadFromFile("Images/Card/card_peashooter.png");
		PlantS[0].setTexture(PlantT[0]);
		PlantS[0].setTextureRect(sf::IntRect(0, 0, 64, 90));
		PlantS[0].setPosition(75, 0);
		PlantT[1].loadFromFile("Images/Card/card_sunflower.png");
		PlantS[1].setTexture(PlantT[1]);
		PlantS[1].setTextureRect(sf::IntRect(0, 0, 64, 90));
		PlantS[1].setPosition(75 + 70, 0);
		PlantT[2].loadFromFile("Images/Card/card_repeaterpea.png");
		PlantS[2].setTexture(PlantT[2]);
		PlantS[2].setTextureRect(sf::IntRect(0, 0, 64, 90));
		PlantS[2].setPosition(75 + 140, 0);
		PlantT[3].loadFromFile("Images/Card/card_wallnut.png");
		PlantS[3].setTexture(PlantT[3]);
		PlantS[3].setTextureRect(sf::IntRect(0, 0, 64, 90));
		PlantS[3].setPosition(75 + 210, 0);
		Back.loadFromFile("Images/ChooserBackground.png");
		BackGround.setTexture(Back);
		BackGround.setTextureRect(sf::IntRect(0, 0, 522, 87));
		BackGround.setPosition(0, 0);

	}
	Sprite getSprite(int i) {
		return PlantS[i];
	}
	bool checkCoordinates(int x, int y) {
		int HorizontalBox = 70;
		if (x >= HorizontalBox && x < HorizontalBox + 70 && y >= 0 && y < verticalBox)
		{
			for (int i = 0; i < numofPlants; i++)
				select[i] = false;
			select[0] = true;
		}
		else if (x > HorizontalBox * 2 && x < HorizontalBox * 3 && y >= 0 && y < verticalBox)
		{
			for (int i = 0; i < numofPlants; i++)
				select[i] = false;
			select[1] = true;
		}
		else if (x > HorizontalBox * 3 && x < HorizontalBox * 4 && y >= 0 && y < verticalBox)
		{
			for (int i = 0; i < numofPlants; i++)
				select[i] = false;
			select[2] = true;
		}
		else if (x >= HorizontalBox * 4 && x <= HorizontalBox * 5 && y >= 0 && y < verticalBox)
		{
			for (int i = 0; i < numofPlants; i++)
				select[i] = false;
			select[3] = true;
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
			if (select[i])
				index = i;
		}
		return index;
	}
	void setindex(int i) {
		index = i;
	}
	void drawInventory(RenderWindow& w) const {
		w.draw(BackGround);
		for (int i = 0; i < numofPlants; i++)
			w.draw(PlantS[i]);
	}

};

class Plants {
protected:
	sf::Sprite PeaS;
	sf::Texture PeaT;
	int Price;
	int health;
	coordinates co;
public:

	Plants(int P = 100, int H = 50) :Price(P), health(H) {}
	Sprite getPlant() {
		return PeaS;
	}
	void setposition(int x, int y) {
		co.setcoordinates(x, y);
		PeaS.setPosition(co.x, co.y);
	}
	virtual void shootBullet() = 0;
	virtual void addBullet() = 0;
	virtual Sprite& getBullet(int i) = 0;
	virtual bool getexist(int i) = 0;
	virtual Vector2f getBulletPos(int i) = 0;
};
class Shooter :public Plants {
protected:
	Sprite* Bullet;
	Texture BulletT;
	Vector2f* vel;
	Vector2f* pos;
	Vector2f* dir;
	float speed = 100.0f;
	Clock Delay;
	Clock Interval;
	Clock dummy;
	bool* exist;
	int current;
public:
	Shooter() {
		delete[] Bullet;
		Bullet = new Sprite[10];
		delete[] exist;
		exist = new bool[10];
		BulletT.loadFromFile("Images/pea.png");
		vel = new Vector2f[10];
		dir = new Vector2f[10];
		pos = new Vector2f[10];
		for (int i = 0; i < 10; i++)
		{
			Bullet[i].setTexture(BulletT);
			Bullet[i].setTextureRect(sf::IntRect(0, 0, 28, 28));
			vel[i] = { 0.0f,0.0f };
			dir[i] = { 1.0f,0.0f };
			exist[i] = false;
		}
		current = 0;
	}
	virtual void shootBullet() = 0;
	virtual void addBullet() = 0;
	virtual Sprite& getBullet(int i) = 0;
	virtual bool getexist(int i) = 0;
	virtual Vector2f getBulletPos(int i) = 0;
};
class PeaShooter :public Shooter {

public:
	PeaShooter() {

		PeaT.loadFromFile("Images/peashooter_12.png");
		PeaS.setTexture(PeaT);
		PeaS.setTextureRect(sf::IntRect(0, 0, 71, 71));

	}
	void shootBullet() {
		for (int i = 0; i < 10; i++)
		{
			if (exist[i])
			{
				if (pos[i].x <= HorizontalBox * 11)
				{
					vel[i] = dir[i] * speed;
					pos[i] += vel[i] * 1.0f / 60.0f;
					Bullet[i].setPosition(pos[i]);
				}
				else
					exist[i] = false;
			}

		}
	}
	void addBullet() {
		for (int i = 0; i < 10; i++)
		{
			if (exist[i] == false)
			{
				current = i;
				break;
			}
		}
		if (Interval.getElapsedTime().asSeconds() > 0)
		{
			Interval.restart();
			if (Delay.getElapsedTime().asSeconds() > 2 && current < 10)
			{
				Delay.restart();
				pos[current].x = co.x + 64;
				pos[current].y = co.y;
				Bullet[current].setPosition(pos[current]);
				exist[current] = true;
				current++;


			}
		}
		//cout << Delay.getElapsedTime().asSeconds() << endl;
		//shootBullet();

	}
	Sprite& getBullet(int i) {
		if (exist[i])
			return Bullet[i];
	}
	bool getexist(int i) {
		return exist[i];
	}
	Vector2f getBulletPos(int i) {
		if (exist[i])
			return pos[i];
	}

};
class Sunflower :public Shooter {

public:
	Sunflower() {
		PeaT.loadFromFile("Images/sunflower.png");
		PeaS.setTexture(PeaT);
		PeaS.setTextureRect(sf::IntRect(0, 0, 83, 83));
	}
	void shootBullet() {}
	void addBullet() {}
	Sprite& getBullet(int i) { return Bullet[i]; }
	bool getexist(int i) { return false; }
	Vector2f getBulletPos(int i) {
		if (exist[i])
			return pos[i];
	}
};
class Repeater :public Shooter {
	int count;
public:
	Repeater() {
		count = 0;
		PeaT.loadFromFile("Images/repeater.png");
		PeaS.setTexture(PeaT);
		PeaS.setTextureRect(sf::IntRect(0, 0, 83, 83));
	}

	void shootBullet() {
		for (int i = 0; i < 10; i++)
		{
			if (exist[i])
			{
				if (pos[i].x <= HorizontalBox * 11)
				{
					vel[i] = dir[i] * speed;
					pos[i] += vel[i] * 1.0f / 60.0f;
					Bullet[i].setPosition(pos[i]);
				}
				else
					exist[i] = false;
			}

		}
	}
	void addBullet() {
		for (int i = 0; i < 10; i++)
		{
			if (exist[i] == false)
			{
				current = i;
				break;
			}
		}
		if (Interval.getElapsedTime().asSeconds() > 1.7)
		{
			if (Delay.getElapsedTime().asSeconds() > 0.2 && current < 10)
			{
				count++;
				Delay.restart();
				pos[current].x = co.x + 64;
				pos[current].y = co.y;
				Bullet[current].setPosition(pos[current]);
				exist[current] = true;
				current++;

			}
			if (count >= 2)
			{
				count = 0;
				Interval.restart();

			}
		}
		//cout << Delay.getElapsedTime().asSeconds() << endl;
		//shootBullet();

	}
	Sprite& getBullet(int i) {
		if (exist[i])
			return Bullet[i];
	}
	Vector2f getBulletPos(int i) {
		if (exist[i])
			return pos[i];
	}
	bool getexist(int i) {
		return exist[i];
	}
};
class Wallnut :public Shooter {

public:
	Wallnut() {
		PeaT.loadFromFile("Images/wallnut.png");
		PeaS.setTexture(PeaT);
		PeaS.setTextureRect(sf::IntRect(0, 0, 83, 83));
	}
	void shootBullet() {}
	void addBullet() {}
	Sprite& getBullet(int i) { return Bullet[i]; }
	bool getexist(int i) { return exist[i]; }
	Vector2f getBulletPos(int i) {
		if (exist[i])
			return pos[i];
	}
};

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

	~Plant_Factory() {}
	void addZombies(Zombie_Factory* Z) {
		Zomb = Z;
	}
	void addplant(int& x, int& y, bool** Feild) {

		this->index = Inven->getindex();
		if (index >= 0 && index <= 3)
		{
			if (checkRange(x, y, Feild))
			{
				if (size != 1)
				{
					cout << Inven->getindex();
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
					plan[size - 1] = new PeaShooter();
				else if (index == 1)
					plan[size - 1] = new Sunflower();
				if (index == 2)
					plan[size - 1] = new Repeater();
				else if (index == 3)
					plan[size - 1] = new Wallnut();
				//Inven->setindex(-1);
				exist[size - 1] = true;
				plan[size - 1]->setposition(x, y);
				plan[size - 1]->addBullet();
				size++;

			}
		}

	}
	bool exists(int i) const {
		return exist[i];
	}
	int getsize() const {
		return size;
	}
	Sprite getSprite(int i) const {
		return plan[i]->getPlant();
	}
	void drawPlants(RenderWindow& w) const
	{
		for (int i = 0; i < size; i++)
		{
			if (exists(i))
			{
				w.draw(plan[i]->getPlant());
			}
		}
		for (int i = 0; i < size; i++)
		{
			if (exists(i))
			{
				plan[i]->shootBullet();
				plan[i]->addBullet();
				for (int j = 0; j < 10; j++)
				{
					if (plan[i]->getexist(j))
						w.draw(plan[i]->getBullet(j));
				}
			}
		}

	}
	Plants& getPlant(int x) const {
		for (int i = 0; i < size; i++)
		{
			if (x == i)
				return *(plan[i]);
		}
	}
	void hitZomb() {
		for (int i = 0; i < size-1; i++)
		{
			for (int j = 0; j < 10 && plan[i]->getexist(j); j++)
			{
				for (int k = 0; k < Zomb->getsizeofzombies() && Zomb->getexists(k); k++)
				{
					if (plan[i]->getBulletPos(j).x > Zomb->getZombie(k).pos.x - 100 && plan[i]->getBulletPos(j).x < Zomb->getZombie(k).pos.x + 50 && plan[i]->getBulletPos(j).y <= Zomb->getZombie(k).pos.y + 100 && plan[i]->getBulletPos(j).y > Zomb->getZombie(k).pos.y)
						cout << "Impact";
				}
			}
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
};


class Levels {

protected:
	int numofPlants;
	int Waves;
	int numofZombie;
	Inventory Inven;
	Plant_Factory* Plants;
	Zombie_Factory* Zombie;
public:
	Levels(int nop=4,int w=3) :Zombie(new Zombie_Factory(w)),Plants(new Plant_Factory(Inven)) {
		Plants->addZombies(Zombie);
		numofPlants = 4;
		Waves = w;
		numofZombie = 0;
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
	virtual void spawnZombies() = 0;
};
class BeginnersGarden: public Levels{
public:
	BeginnersGarden():Levels(4,3)
	{}
	void spawnZombies() {
		if(Waves > 0)
		{
			if (Zombie->getnumofzombies() >= Zombie->getsizeofzombies())
			{
				getZombies().Update();
				getZombies().addZombie();
				Plants->hitZomb();
			}
			else
			{

				delete Zombie;
				Waves--;
				numofZombie = rand() % 5;
				if (Waves > 0)
				Zombie = new Zombie_Factory(numofZombie);
			}
		}
	}
	/*void BulletZombie() {
		for (int i = 0; i < Plants->exists(i); i++)
		{
			for(int j=0;j<10 && Plants->getPlant(i).getexist(j) ;j++)
			{
				if (Plants->getPlant(i).getBullet(j)<=Zombie->)
			}
		}
	}*/
};

class Game {
	Levels* level;
	int numoflevel;
public:
	Game() {
		numoflevel = 1;
		level = nullptr;
	}
	void start() {
		if (numoflevel == 1)
			level = new BeginnersGarden();
	}
	void draw(Vector2i& mousePos,bool **FIELD_GAME_STATUS) {
		level->getInventory().checkCoordinates(mousePos.x,mousePos.y);
		level->getPlants().addplant(mousePos.x, mousePos.y, FIELD_GAME_STATUS);
	}
	void drawEntities(RenderWindow& window, bool** FIELD_GAME_STATUS) {
		level->spawnZombies();
		level->getInventory().drawInventory(window);
		level->getZombies().DrawZombie(window);
		level->getPlants().drawPlants(window);
	}
	Levels* getlevel() {
		return level;
	}
};