#include "Objects.h"

void Object::moveTo(sf::Vector2f pos)
{
	position = pos;
}

double Object::getPositionX()
{
	return position.x;
}

double Object::getPositionY()
{
	return position.y;
}

sf::Vector2f Object::getPosition()
{
	return position;
}

Object::Object()
{
}

Object::Object(sf::Vector2f pos)
	:position(pos)
{
}

Object::~Object()
{
}
