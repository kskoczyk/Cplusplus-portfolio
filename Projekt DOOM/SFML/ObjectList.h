#pragma once

#include <SFML/Graphics.hpp>
#include "Cube.h"
#include "Player.h"
#include <list>
#include "Map.h"
#include <fstream>
#include <vector>

class ObjectList
{
	
public:
	std::list<Wall*> objects;
	std::list<Player*> players;
	void setPlayer(Player*);
	void load(Map*);
	void loadFromFile(string path);
	int objectCount();
	ObjectList();
	~ObjectList();
};

