#include "Menu.h"
using namespace std;
Button::Button(sf::Vector2f size, sf::Vector2f position,gameOptions* settings, string texture)
{
	this->settings = settings;
	buttonTexture.loadFromFile(texture);
	button = new sf::RectangleShape;
	button->setPosition(position);
	button->setSize(size);
	button->setTexture(&buttonTexture);
	border = new sf::FloatRect(position, size);
}
Button::Button(sf::Vector2f size, sf::Vector2f position, gameOptions* settings)
{
	this->settings = settings;
	button = new sf::RectangleShape;
	button->setPosition(position);
	button->setSize(size);
	border = new sf::FloatRect(position, size);
}
Button::~Button()
{
	delete border;
}
void Button::setFunction(void(*func)(gameOptions*))
{
	action = func;
}
bool Button::isTargeted()
{
	return border->contains(sf::Vector2f(sf::Mouse::getPosition()));
}
void Button::changeTexture(string texture)
{
	buttonTexture.loadFromFile(texture);
	button->setTexture(&buttonTexture);
}
void Menu::showMenu()
{	
	
	settings->window->clear(sf::Color(0, 0, 0,255));
	settings->window->draw(*background);
	for (int i = 0; i < numberOfButtons; ++i)
	{
		settings->window->draw(*button[i]->button);
	}
	settings->mouse->setPosition(sf::Vector2f(sf::Mouse::getPosition()));
	settings->window->draw(*settings->mouse);
	settings->window->display();
	
}
void Menu::checkMenu()
{
	for (int i = 0; i < numberOfButtons; ++i)
	{
		if (button[i]->isTargeted() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
			}
			button[i]->action(settings);
		}
	}
}
void Menu::setBackgroundTexture(string texture)
{
	backgroundTexture.loadFromFile(texture);
	background->setTexture(&backgroundTexture);
}
Menu::Menu(gameOptions* options, unsigned int x) :numberOfButtons(x)
{
	settings = options;
	button = new Button*[numberOfButtons];
	background = new sf::RectangleShape;
	sf::Vector2f size = sf::Vector2f(settings->window->getSize());
	background->setSize(size);
	for (int i = 0; i < numberOfButtons; ++i)
	{
		button[i] = new Button(sf::Vector2f(200, 100), sf::Vector2f(800, 200 + i * 150), settings);
	}
}

Menu::~Menu()
{
	for (int i = 0; i < numberOfButtons; ++i)
	{
		delete button[i];
	}
	delete button;
	delete background;
}