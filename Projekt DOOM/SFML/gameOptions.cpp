#include "gameOptions.h"



unsigned int gameOptions::getState()
{
	return state;
}

void gameOptions::setState(unsigned int x)
{
	state = x;
}

bool gameOptions::isMuted()
{
	return mute;
}

void gameOptions::setMute(bool x)
{
	mute = x;
}

void gameOptions::setMouseTexture(string texture)
{
	mouseTexture.loadFromFile(texture);
	mouse->setTexture(&mouseTexture);
}

void gameOptions::setVolume(unsigned int newVolume)
{
	volume = newVolume;
}

void gameOptions::setMap(Map* newMap)
{
	map = newMap;
}
unsigned int gameOptions::getVolume()
{
	return volume;
}

Map* gameOptions::getMap()
{
	return map;
}
gameOptions::gameOptions()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Projekt", sf::Style::Fullscreen, settings);
	music = new sf::Music;
	event = new sf::Event;
	mouse = new sf::RectangleShape(sf::Vector2f(35,35));
	mute = false;
	volume = 50;
	state = 0;
}


gameOptions::~gameOptions()
{
	delete mouse;
	delete music;
	delete event;
	delete window;
}
