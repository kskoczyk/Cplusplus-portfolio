#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Map.h"

using namespace std;

class gameOptions
{
	bool mute;
	unsigned int state;
	unsigned int volume;
public:
	sf::Texture mouseTexture;
	sf::RectangleShape *mouse;
	sf::Music *music;
	sf::Event *event;
	sf::RenderWindow *window;
	Map* map;
unsigned int getState();
void setState(unsigned int);
bool isMuted();
void setMute(bool);
void setMouseTexture(string);
void setVolume(unsigned int);
void setMap(Map*);
Map* getMap();

unsigned int getVolume();
	gameOptions();
	~gameOptions();
};

