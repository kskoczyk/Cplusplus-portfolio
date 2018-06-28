#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "ObjectList.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <windows.h>

class DisplayList
{
	std::list<sf::ConvexShape*> objects;
	std::list<sf::RectangleShape*> entities;
public:
	void display(gameOptions*);
	void startRay(ObjectList* objectList, Player* player);
	DisplayList();
	~DisplayList();
};

