#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Image.hpp"
#include <ctime>
#include <cstdlib> 
//Group Member 1: Shahmeer Atif 23i-0711 CS-G
//Group Member 2: Irfan Khalid  23i-2092 CS-G
class Animation {
	sf:: Sprite Frame;
	sf::Clock time;
	int x;
	int y;
	int gap;
	int limit;
	int current;
	int origin;
public:

	void setFrame(sf::Texture& T, int x, int y, int l, int o = 0){
		this->x = x;
		this->y = y;
		Frame.setTexture(T);
		Frame.setTextureRect(sf::IntRect(0, 0, this->x, this->y));
		if(o==49)
		Frame.setOrigin(0,o);
		else
		Frame.setOrigin(o, o);
		gap = this->x;
		current = 0;
		limit = l;

	}
	void setOrigin(int x, int y)
	{
		Frame.setOrigin(x, y);
	}
	void animate() {
		if (time.getElapsedTime().asSeconds() > 0.075)
		{
			if (getInterval())
				current = 0;
			time.restart();
			Frame.setTextureRect(sf::IntRect(current, 0, x, y));
			current += gap;
			//cout << current<<endl;

		}
	}
	bool getInterval() {
		if (current >= limit)
		{
			current = 0;
			return true;
		}
		return false;
	}
	void updateposition(Vector2f& pos) {
		Frame.setPosition(pos);
	}
	sf::Sprite& getSprite() {
		//animate();
		//Frame.setPosition(pos);
		return Frame;
	}
};