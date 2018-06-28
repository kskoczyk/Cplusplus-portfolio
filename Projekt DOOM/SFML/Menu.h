#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "gameOptions.h"
using namespace std;
class Button
{
public:
	gameOptions * settings;
	sf::RectangleShape *button;
	sf::Texture buttonTexture;
	sf::FloatRect *border;
	void (*action)(gameOptions*);
	Button(sf::Vector2f, sf::Vector2f, gameOptions* settings, string);
	Button(sf::Vector2f, sf::Vector2f, gameOptions* settings);
	~Button();
	void changeTexture(string);
	void setFunction(void(*)(gameOptions*));
	bool isTargeted();
};

class Menu
{
	sf::RectangleShape* background;
	sf::Texture backgroundTexture;
	const unsigned int numberOfButtons;
	gameOptions * settings;
public:
	Button **button;
	void showMenu();
	void checkMenu();
	void setBackgroundTexture(string);
	Menu(gameOptions*, unsigned int);
	~Menu();
};


