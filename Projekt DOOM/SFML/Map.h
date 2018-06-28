#pragma once

#include "Cube.h"
#include "EasyBMP.h"

class Map
{
	friend class Player;
public:
	vector< vector<int> > flexMap; // adaptowalna mapa
	void checkCollision(sf::Vector2f&, double, double, double);
	Map(string); // tworzenie mapy na podstawie mapy bitowej
	~Map();
};

