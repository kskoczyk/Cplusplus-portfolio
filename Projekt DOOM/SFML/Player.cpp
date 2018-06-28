#include "Player.h"


double Player::getAngle()
{
	return viewAngle;
}

double Player::getPositionX()
{
	return position.x;
}

double Player::getPositionY()
{
	return position.y;
}

Player::Player(gameOptions* settings)
{
	this->settings = settings;
	position.x = 5;
	position.y = 5;
	viewAngle = 0;
	HP = 100;
	size = 0.3; // do ustalenia
}

void Player::control(sf::Time time)
{
	double milliseconds = time.asMilliseconds();

	double moveSpeed = 6 * milliseconds / 1000;
	double moveSpeedMultiplier;
	double rotationSpeed = 0.1;

	double vectorX = 0;
	double vectorY = 0;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		settings->music->setPitch(1.0);
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				moveSpeedMultiplier = 2;
				settings->music->setPitch(1.05);
			}
			else
			{
				moveSpeedMultiplier = 1;
				settings->music->setPitch(1.0);
			}
			vectorX -= cos(viewAngle* M_PI / 180)*moveSpeed*moveSpeedMultiplier;
			vectorY -= sin(viewAngle* M_PI / 180)*moveSpeed*moveSpeedMultiplier;
		}
		else
		{
			settings->music->setPitch(1.0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{

			vectorX += cos(viewAngle* M_PI / 180)*moveSpeed;
			vectorY += sin(viewAngle* M_PI / 180)*moveSpeed;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		vectorX += sin(viewAngle* M_PI / 180)*moveSpeed;
		vectorY -= cos(viewAngle* M_PI / 180)*moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		vectorX -= sin(viewAngle* M_PI / 180)*moveSpeed;
		vectorY += cos(viewAngle* M_PI / 180)*moveSpeed;
	}

	settings->map->checkCollision(position, vectorX, vectorY, size);

	viewAngle -= (1.0*sf::Mouse::getPosition().x - 1.0*settings->window->getSize().x / 2)*rotationSpeed;
	if (viewAngle >= 360)
		viewAngle -= 360;
	if (viewAngle < 0)
		viewAngle += 360;
	sf::Mouse::setPosition(sf::Vector2i(settings->window->getSize().x / 2, 0));
}

Player::~Player()
{
}
