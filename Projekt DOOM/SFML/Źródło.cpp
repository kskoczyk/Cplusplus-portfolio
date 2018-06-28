#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "gameOptions.h"
#include "Functions.h"
#include "Player.h"
#include "DisplayList.h"
#include "ObjectList.h"
#include "Map.h"



int main()
{
	sf::Clock MainClock;
	//INIT	
	gameOptions settings;
	Menu menu(&settings, 3);
	menu.setBackgroundTexture("Graphics/Background.png");


	menu.button[0]->changeTexture("Graphics/Play.png");
	menu.button[0]->setFunction(game);
	menu.button[1]->changeTexture("Graphics/Options.png");
	menu.button[1]->setFunction(optionsMenu);
	menu.button[2]->changeTexture("Graphics/Quit.png");
	menu.button[2]->setFunction(closeWindow);

	Menu options(&settings, 4);
	options.setBackgroundTexture("Graphics/Background.png");

	options.button[0]->changeTexture("Graphics/Mute.png");
	options.button[0]->setFunction(mute);
	options.button[1]->changeTexture("Graphics/Volume+.png");
	options.button[1]->setFunction(volumePlus);
	options.button[2]->changeTexture("Graphics/Volume-.png");
	options.button[2]->setFunction(volumeMinus);
	options.button[3]->changeTexture("Graphics/Back.png");
	options.button[3]->setFunction(mainMenu);

	init(&settings);
	DisplayList displayList;
	ObjectList objectList;
	string path = "Maps/map.bmp"; // zmieniæ lokalizacjê
	settings.setMap(new Map(path));
	objectList.load(settings.map);
	Player* player = new Player(&settings);

	objectList.setPlayer(player);

	//
	while (settings.window->isOpen())
	{
		while (settings.window->pollEvent(*settings.event))
		{
			if (settings.event->type == sf::Event::Closed)
			{
				closeWindow(&settings);
			}
		}
		if (settings.getState()== 0) //Menu g³ówne
		{
		menu.showMenu();
		menu.checkMenu();
		}
		else if (settings.getState() == 1) //Menu opcji
		{
			options.showMenu();
			options.checkMenu();
		}
		else if (settings.getState() == 2)	//Gra
		{	
			//Wyœwietlanie
			displayList.startRay(&objectList, player);
			displayList.display(&settings);
			//
			//player.control();

			// Treœci DEBUG
			sf::Text text; // k¹t
			sf::Text text1; // wsp. x
			sf::Text text2; // wsp. y
			sf::Text text3; // FPS
			sf::Font font;

			font.loadFromFile("Fonts/arial.ttf");
			text.setFont(font);
			text.setPosition(400, 200);
			text.setCharacterSize(50);
			text.setString(to_string(player->getAngle()));
			text.setFillColor(sf::Color::Black);
			settings.window->draw(text);

			text1.setFont(font);
			text1.setPosition(800, 200);
			text1.setCharacterSize(50);
			text1.setString(to_string(player->getPositionX()));
			text1.setFillColor(sf::Color::Black);
			settings.window->draw(text1);

			text2.setFont(font);
			text2.setPosition(1200, 200);
			text2.setCharacterSize(50);
			text2.setString(to_string(player->getPositionY()));
			text2.setFillColor(sf::Color::Black);
			settings.window->draw(text2);

			//
			//while (MainClock.getElapsedTime().asMicroseconds() < (16666)); //  60 FPS (limiter)

			text3.setFont(font);
			text3.setPosition(100, 50);
			text3.setCharacterSize(30);
			text3.setString(to_string(1000 / (MainClock.getElapsedTime()).asMilliseconds()));
			text3.setFillColor(sf::Color::Green);
			settings.window->draw(text3);

			settings.window->display();

			player->control(MainClock.getElapsedTime()); // przyspieszenie gracza, gdy ma lagi
			MainClock.restart();
			//
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			mainMenu(&settings);
		}

		// Ustawienie tekstury przycisku MUTE
		if (settings.isMuted() == 0)
		{
			options.button[0]->changeTexture("Graphics/Mute.png");
		}
		else
		{
			options.button[0]->changeTexture("Graphics/Unmute.png");
		}
	}
	return 0;
	
}