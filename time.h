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

class times {
	Clock StartingDelay;
	int CompareT;
public:
	times() {
		CompareT = 10;
	}
	Clock getClock() {
		return StartingDelay;
	}
	int getCompareT() {
		return CompareT;
	}
	void setCompareT(int t) {
		CompareT = t;
	}
};