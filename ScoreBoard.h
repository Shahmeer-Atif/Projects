#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Image.hpp"
#include <ctime>
#include <cstdlib> 
#include"Plants.h"
#include"Zombies.h"
#include"Inventory.h"
#include"Global.h"
#include"Sun.h"
#include<fstream>
#include<string>
using namespace std;
using namespace sf;
//Group Member 1: Shahmeer Atif 23i-0711 CS-G
//Group Member 2: Irfan Khalid  23i-2092 CS-G
class ScoreBoard {
	fstream File;
	string names[20];
	string myname;
	int score;
	Image map_image;
	Texture map;
	Sprite s_map;
	sf::Font font;
	sf::Text *Start;
	int size;
	int limit = 8;
public:
	ScoreBoard() {
		cout << "Welcome To Plants VS Zombies\nBefore you can start Enter your name:\n";
		getline(cin, myname);
		score = 0;
		map_image.loadFromFile("images/assets/Inventory-GameScreen/ScoreBoard.png");
		map.loadFromImage(map_image);
		s_map.setTexture(map);
		s_map.setPosition(0, 0);
		font.loadFromFile("Images/SamdanEvil.ttf");
		fstream myfile;
		myfile.open("ScoreBoard.txt", ios::in);
		int i = 0;
		if (myfile.is_open()) {
			while (getline(myfile, names[i]))
			{
				i++;
			}
		}
		size = i;
		myfile.close();
		Start = new Text[size];
		for (int k = 0,y=200; k <size;k++)
		{
			Start[k].setFont(font);
			Start[k].setCharacterSize(35);
			if(k%2==0)
			Start[k].setFillColor(sf::Color::Black);
			else
				Start[k].setFillColor(sf::Color::Red);
			Start[k].setPosition(300, y);
			Start[k].setString(names[k]);
			y += 40;
		}
	}
	void setscore(int s)
	{
		score = s;
	}
	int Action() {
		fstream myfile;
		myfile.open("ScoreBoard.txt", ios::out);
		bool b = true;
		int badge = -1;
		for(int i=0;i<size;i++)
		{
			if (myfile.is_open()) {
			if (i % 2 == 0)
			{
				if (myname == names[i])
				{
					myfile << myname << endl;
					if (i < 6)
					badge = i;
					i++;
					if (score > stoi(names[i]))
					myfile << score<<endl;
					else
					myfile << names[i]<<endl;
					b = false;
				}
				else
					myfile << names[i] << endl;
			}
			else
			{
					myfile << names[i] << endl;
			
			}
			}
		}
		myfile.close();
		
		return badge;
	}
	void addscore(int badge) {
		fstream myfile;
		if(badge==-1)
		{
			myfile.open("ScoreBoard.txt", ios::app);
			if (myfile.is_open()) {
				myfile << myname << endl;
				myfile << score << endl;
			}
		}
		else
		{
			Action();
		}
			myfile.close();
		int du = 0;
		myfile.open("ScoreBoard.txt", ios::in);
		if (myfile.is_open()) {
			while (getline(myfile, names[du]))
			{
				du++;
			}
		}
		
		myfile.close();
		size = du;
		for (int step = 1; step < size; step += 2) {
			for (int i = 1; i < size+1; i += 2) {
				if (i + 2 < size && stoi(names[i]) < stoi(names[i + 2])) {
					string temp = names[i];
					names[i] = names[i + 2];
					names[i + 2] = temp;
					temp = names[i - 1];
					names[i - 1] = names[i + 1];
					names[i + 1] = temp;
				}
			}
		}
		if (size > limit)
			size = limit;

		myfile.open("ScoreBoard.txt", ios::out);
		for (int i = 0; i < size; i++)
		{
			if (myfile.is_open()) {
				myfile << names[i]<<endl;
			}
		}
		myfile.close();
		delete[] Start;
		Start = new Text[size];
		font.loadFromFile("Images/SamdanEvil.ttf");
		for (int k = 0, y = 200; k < size; k++)
		{
			Start[k].setFont(font);
			Start[k].setCharacterSize(35);
			if (k % 2 == 0)
				Start[k].setFillColor(sf::Color::Black);
			else
				Start[k].setFillColor(sf::Color::Red);
			Start[k].setPosition(300, y);
			Start[k].setString(names[k]);
			y += 40;
		}

	}
	void draw(RenderWindow& window) {
		window.draw(s_map);
		for(int i=0;i<size;i++)
		window.draw(Start[i]);
	}
};