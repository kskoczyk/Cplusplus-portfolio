
#include "Functions.h"

void closeWindow(gameOptions* settings)
{
	settings->window->close();
	settings->music->stop();
}
void optionsMenu(gameOptions* settings)
{
	settings->setState(1);
}
void mainMenu(gameOptions* settings)
{
	settings->setState(0);
}
void game(gameOptions* settings)
{
	settings->setState(2);
}
void init(gameOptions* settings)
{
	settings->window->setMouseCursorVisible(false);
	//settings->window->setFramerateLimit(60);
	settings->setMouseTexture("Graphics/Mouse.png");
	settings->music->openFromFile("Music/Neonlight - Computer Music.wav");
	settings->music->setVolume(settings->getVolume());
	settings->music->play();
}
void mute(gameOptions* settings)
{
	if (settings->isMuted() == 0)
	{
		settings->setMute(true);
		settings->music->stop();
	}
	else
	{
		settings->setMute(false);
		settings->music->play();
	}
}

void volumeMinus(gameOptions * settings)
{
	if(settings->getVolume()>= 5)
	settings->setVolume(settings->getVolume() - 5);
	settings->music->setVolume(settings->getVolume());
}

void volumePlus(gameOptions * settings)
{
	if (settings->getVolume() <= 95)
		settings->setVolume(settings->getVolume() + 5);
	settings->music->setVolume(settings->getVolume());
}
