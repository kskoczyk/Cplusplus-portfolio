#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
#include "gameOptions.h"
#include "Objects.h"
#include <conio.h>
#include <windows.h>

class Player : public Object
{
	friend class DisplayList;
	sf::Vector2f position;
	double HP, viewAngle, size;
public:
	gameOptions* settings;
	double getAngle();
	double getPositionX();
	double getPositionY();
	void control(sf::Time);
	Player(gameOptions*);
	~Player();
};

