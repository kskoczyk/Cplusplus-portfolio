#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
class Side
{
	friend class Wall;
	friend class ObjectList;
	friend class DisplayList;
public:
	void setTexture(sf::Texture *);
	Side(sf::Vector2f, sf::Vector2f, sf::Texture *);
	Side();
	~Side();
private:
	sf::ConvexShape shape;
	sf::Texture * texture;
	sf::Vector2f Beginning, End;
};

class Wall
{
public:
	friend class ObjectList;
	friend class DisplayList;
	Wall(sf::Vector2f, sf::Texture *);
	~Wall();
private:
	Side left, right, front, back;
	sf::Vector2f position;

};
