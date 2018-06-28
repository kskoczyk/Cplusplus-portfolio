#include "Cube.h"



Side::Side(sf::Vector2f Beginning, sf::Vector2f End, sf::Texture *t)
{
	this->Beginning = Beginning;
	this->End = End;
	this->texture = t;
	
}

Side::Side()
{
}

Side::~Side()
{
}

void Side::setTexture(sf::Texture * t)
{
	this->texture = t;
}

Wall::Wall(sf::Vector2f position, sf::Texture * t)
{
	this->position = position;


	this->left.Beginning.x = position.x - 0.5;
	this->left.End.x = position.x - 0.5;
	this->left.Beginning.y = position.y - 0.5;
	this->left.End.y = position.y + 0.5;
	this->left.shape.setPointCount(4);
	this->left.setTexture(t);
	this->left.shape.setTexture(this->left.texture);

	this->right.Beginning.x = position.x + 0.5;
	this->right.End.x = position.x + 0.5;
	this->right.Beginning.y = position.y - 0.5;
	this->right.End.y = position.y + 0.5;
	this->right.shape.setPointCount(4);
	this->right.setTexture(t);
	this->right.shape.setTexture(this->right.texture);
	
	this->front.Beginning.x = position.x - 0.5;
	this->front.End.x = position.x + 0.5;
	this->front.Beginning.y = position.y - 0.5;
	this->front.End.y = position.y - 0.5;
	this->front.shape.setPointCount(4);
	this->front.setTexture(t);
	this->front.shape.setTexture(this->front.texture);

	this->back.Beginning.x = position.x - 0.5;
	this->back.End.x = position.x + 0.5;
	this->back.Beginning.y = position.y + 0.5;
	this->back.End.y = position.y + 0.5;
	this->back.shape.setPointCount(4);
	this->back.setTexture(t);
	this->back.shape.setTexture(this->back.texture);
}




Wall::~Wall()
{
}




