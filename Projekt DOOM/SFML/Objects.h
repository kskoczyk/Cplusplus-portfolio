#pragma once

#include <SFML/Graphics.hpp>

class Object // klasa abstrakcyjna do dziedziczenia dla gracza i itemków
{
protected:
	sf::Vector2f position;
public:
	virtual void moveTo(sf::Vector2f);
	virtual double getPositionX();
	virtual double getPositionY();
	virtual sf::Vector2f getPosition();
	Object();
	Object(sf::Vector2f); // potrzebne?
	~Object();
};

// jeœli itemki polegaj¹ tylko na powy¿szych funkcjach (odpowiednio przeci¹¿onych), to base pointer JEST OK