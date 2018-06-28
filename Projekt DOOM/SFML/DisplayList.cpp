#include "DisplayList.h"

double distance(double firstX, double firstY, double secondX, double secondY)
{
	return pow(pow(firstX - secondX, 2) + pow(firstY - secondY, 2), 0.5);
}

double angle(double firstX, double firstY, double secondX, double secondY)
{
	double deltaAngle = (180.0 / M_PI)*atan2((firstY - secondY), (firstX - secondX));
	if (deltaAngle < 0)
	{
		deltaAngle += 360;
	}
	return deltaAngle;
}


void DisplayList::display(gameOptions * settings)
{
	//settings->window->clear(sf::Color(0, 0, 0, 255));
	sf::RectangleShape upperHalf(sf::Vector2f(settings->window->getSize().x, settings->window->getSize().y / 2));
	sf::RectangleShape downHalf(sf::Vector2f(settings->window->getSize().x, settings->window->getSize().y / 2));
	downHalf.setPosition(sf::Vector2f(0, settings->window->getSize().y / 2));
	upperHalf.setFillColor(sf::Color(105, 105, 105));
	downHalf.setFillColor(sf::Color(192, 192, 192));
	settings->window->draw(upperHalf);
	settings->window->draw(downHalf);

	for (list<sf::ConvexShape*>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		settings->window->draw(**it);
	}
		objects.clear();
	//settings->window->display();
	
}
void DisplayList::startRay(ObjectList* objectList, Player* player) // wybór obiektów do wyœwietlenia
{

	double fieldOfView = 120;
	double distanceOfView = 100;
	double viewCompensate = 60;  // poprawa granicy widzenia
	double distanceCompensate = 2; // zmiana rozmiaru obiektów w zale¿noœci od odleg³oœci
	int windowHeight, windowWidth;
	windowHeight = player->settings->window->getSize().y;
	windowWidth = player->settings->window->getSize().x;

	std::list<Wall*> distanceFiltered;
	for (list<Wall*>::iterator it = objectList->objects.begin(); it != objectList->objects.end(); ++it)
	{
		if (distance(player->position.x, player->position.y, (*it)->position.x, (*it)->position.y) <= distanceOfView)
		{
			distanceFiltered.push_back(*it);
		}
	}

	std::list<Wall*> angleFiltered;
	for (list<Wall*>::iterator it = distanceFiltered.begin(); it != distanceFiltered.end(); ++it)
	{
		double deltaAngle = abs(player->viewAngle - angle(player->position.x, player->position.y, (*it)->position.x, (*it)->position.y));
		if (deltaAngle > 180)
			deltaAngle = 360 - deltaAngle;

		if (deltaAngle <= (fieldOfView / 2) + viewCompensate)
		{
			angleFiltered.push_back(*it);
		}
	}

	Wall** toDisplay = new Wall*[angleFiltered.size()];
	double *distanceOfWall = new double[angleFiltered.size()];

	{
		int i = 0;
		for (list<Wall*>::iterator it = angleFiltered.begin(); it != angleFiltered.end(); ++it)
		{

			toDisplay[i] = *it;
			distanceOfWall[i] = distance(player->position.x, player->position.y, (*it)->position.x, (*it)->position.y);
			++i;
		}
	}

	//QUICKSORT
	int size = angleFiltered.size();
	vector< pair<double, Wall*> > pairs;
	pairs.reserve(size); // wydajnoœæ

	for (int i = 0; i < size; i++) // sparuj
	{
		pairs.push_back(make_pair(distanceOfWall[i], toDisplay[i]));
	}

	sort(pairs.begin(), pairs.end(), [](auto &left, auto &right) // u¿ycie lambdy i auto (zobacz: C++14)
	{
		return left.first > right.first; // malej¹co
	});

	for (int i = 0; i < size; i++) // rozdziel pary
	{
		distanceOfWall[i] = pairs[i].first;
		toDisplay[i] = pairs[i].second;
	}

	vector< pair<double, Wall*> >().swap(pairs); // zwolnij pamiêæ NATYCHMIAST

	for (int i = 0; i < angleFiltered.size(); i++)
	{
		if (player->position.x < ((toDisplay[i]->position.x) - 0.5)) // 0.5 odleg³oœæ od œrodka // lewa strona
		{
			double deltaAngle = player->viewAngle - angle(player->position.x, player->position.y, toDisplay[i]->left.Beginning.x, toDisplay[i]->left.Beginning.y); // obliczanie szerokoœci k¹towej POCZ¥TKU wyœwietlanego obiektu, angle() - k¹t miêdzy osi¹ X a obiektem
			if (deltaAngle < -180)
				deltaAngle += 360;
			if (deltaAngle > 180)
				deltaAngle -= 360;
			double sideBegDistance = distance(player->position.x, player->position.y, toDisplay[i]->left.Beginning.x, toDisplay[i]->left.Beginning.y); // odleg³oœæ pocz¹tku œciany od gracza
			toDisplay[i]->left.shape.setPoint(0, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 - 1.0*windowHeight / (distanceCompensate * sideBegDistance)));
			toDisplay[i]->left.shape.setPoint(1, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 + 1.0*windowHeight / (distanceCompensate * sideBegDistance)));

			deltaAngle = player->viewAngle - angle(player->position.x, player->position.y, toDisplay[i]->left.End.x, toDisplay[i]->left.End.y); // obliczanie szerokoœci k¹towej KOÑCA wyœwietlanego obiektu, angle() - k¹t miêdzy osi¹ X a obiektem
			if (deltaAngle < -180)
				deltaAngle += 360;
			if (deltaAngle > 180)
				deltaAngle -= 360;
			sideBegDistance = distance(player->position.x, player->position.y, toDisplay[i]->left.End.x, toDisplay[i]->left.End.y);
			toDisplay[i]->left.shape.setPoint(2, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 + 1.0*windowHeight / (distanceCompensate * sideBegDistance)));
			toDisplay[i]->left.shape.setPoint(3, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 - 1.0*windowHeight / (distanceCompensate * sideBegDistance))); // 0,1,2,3 - kolejne punkty wielok¹ta 
			toDisplay[i]->left.shape.setFillColor(sf::Color(0, 0, 255));	//
		//	toDisplay[i]->left.shape.setOutlineColor(sf::Color(255, 0, 0)); // DO POPRAWY
		//	toDisplay[i]->left.shape.setOutlineThickness(1);				//
		//	toDisplay[i]->left.shape.setTexture(&toDisplay[i]->left.texture);
			sf::Vector2f toTan = toDisplay[i]->left.shape.getPoint(2) - toDisplay[i]->left.shape.getPoint(1);
			double height = (toDisplay[i]->left.shape.getPoint(3) - toDisplay[i]->left.shape.getPoint(2)).y;
			double height2 = (toDisplay[i]->left.shape.getPoint(1) - toDisplay[i]->left.shape.getPoint(0)).y;
			double width = toTan.x;
			double ratio = height / width;
			double ratio2 = height2 / width;
			double tanAngle = 1.0*atan((1.0*toTan.y) / (1.0*toTan.x*ratio))*180.0 / M_PI;
			double tanAngle2 = 1.0*atan((1.0*toTan.y) / (1.0*toTan.x*ratio2))*180.0 / M_PI;
			if (((tanAngle2) <= 0) && ((tanAngle2) >= -30))
			{
				toDisplay[i]->left.shape.setTextureRect(sf::IntRect(250 * (30 + (int)((1.0*tanAngle2))), 0, 250, 250));
			}
			else
			{
				toDisplay[i]->left.shape.setTextureRect(sf::IntRect(250 * (30 - (int)((1.0*tanAngle))), 0, 250, 250));
			}
			objects.push_back(&toDisplay[i]->left.shape);//dodanie do listy wyœwietlania wskaŸnika na Convexshape
		}
		else if (player->position.x > ((toDisplay[i]->position.x) + 0.5)) // prawa strona
		{
			double deltaAngle = player->viewAngle - angle(player->position.x, player->position.y, toDisplay[i]->right.Beginning.x, toDisplay[i]->right.Beginning.y);
			if (deltaAngle < -180)
				deltaAngle += 360;
			if (deltaAngle > 180)
				deltaAngle -= 360;
			double sideBegDistance = distance(player->position.x, player->position.y, toDisplay[i]->right.Beginning.x, toDisplay[i]->right.Beginning.y);
			toDisplay[i]->right.shape.setPoint(0, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 - 1.0*windowHeight / (distanceCompensate * sideBegDistance)));
			toDisplay[i]->right.shape.setPoint(1, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 + 1.0*windowHeight / (distanceCompensate * sideBegDistance)));

			deltaAngle = player->viewAngle - angle(player->position.x, player->position.y, toDisplay[i]->right.End.x, toDisplay[i]->right.End.y);
			if (deltaAngle < -180)
				deltaAngle += 360;
			if (deltaAngle > 180)
				deltaAngle -= 360;

			sideBegDistance = distance(player->position.x, player->position.y, toDisplay[i]->right.End.x, toDisplay[i]->right.End.y);
			toDisplay[i]->right.shape.setPoint(2, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 + 1.0*windowHeight / (distanceCompensate * sideBegDistance)));
			toDisplay[i]->right.shape.setPoint(3, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 - 1.0*windowHeight / (distanceCompensate * sideBegDistance)));
			toDisplay[i]->right.shape.setFillColor(sf::Color(255, 0, 0));	//
			//toDisplay[i]->right.shape.setOutlineColor(sf::Color(255, 0, 0)); // DO POPRAWY
			//toDisplay[i]->right.shape.setOutlineThickness(1);				//
																			//toDisplay[i]->right.shape.setTexture(&toDisplay[i]->right.texture);
			sf::Vector2f toTan = toDisplay[i]->right.shape.getPoint(2) - toDisplay[i]->right.shape.getPoint(1);
			double height = (toDisplay[i]->right.shape.getPoint(3) - toDisplay[i]->right.shape.getPoint(2)).y;
			double height2 = (toDisplay[i]->right.shape.getPoint(1) - toDisplay[i]->right.shape.getPoint(0)).y;
			double width = toTan.x;
			double ratio = height / width;
			double ratio2 = height2 / width;
			double tanAngle = 1.0*atan((1.0*toTan.y) / (1.0*toTan.x*ratio))*180.0 / M_PI;
			double tanAngle2 = 1.0*atan((1.0*toTan.y) / (1.0*toTan.x*ratio2))*180.0 / M_PI;
			if (((tanAngle2) <= 0) && ((tanAngle2) >= -30))
			{
				toDisplay[i]->right.shape.setTextureRect(sf::IntRect(250 * (30 - (int)((1.0*tanAngle2))), 0, 250, 250));
			}
			else
			{
				toDisplay[i]->right.shape.setTextureRect(sf::IntRect(250 * (30 + (int)((1.0*tanAngle))), 0, 250, 250));
			}
			objects.push_back(&toDisplay[i]->right.shape);


		}
		if (player->position.y < ((toDisplay[i]->position.y) - 0.5)) // przód 
		{
			double deltaAngle = player->viewAngle - angle(player->position.x, player->position.y, toDisplay[i]->front.Beginning.x, toDisplay[i]->front.Beginning.y);
			if (deltaAngle < -180)
				deltaAngle += 360;
			if (deltaAngle > 180)
				deltaAngle -= 360;

			double sideBegDistance = distance(player->position.x, player->position.y, toDisplay[i]->front.Beginning.x, toDisplay[i]->front.Beginning.y);
			toDisplay[i]->front.shape.setPoint(0, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 - 1.0*windowHeight / (distanceCompensate * sideBegDistance)));
			toDisplay[i]->front.shape.setPoint(1, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 + 1.0*windowHeight / (distanceCompensate * sideBegDistance)));

			deltaAngle = player->viewAngle - angle(player->position.x, player->position.y, toDisplay[i]->front.End.x, toDisplay[i]->front.End.y);
			if (deltaAngle < -180)
				deltaAngle += 360;
			if (deltaAngle > 180)
				deltaAngle -= 360;
			sideBegDistance = distance(player->position.x, player->position.y, toDisplay[i]->front.End.x, toDisplay[i]->front.End.y);
			toDisplay[i]->front.shape.setPoint(2, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 + 1.0*windowHeight / (distanceCompensate * sideBegDistance)));
			toDisplay[i]->front.shape.setPoint(3, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 - 1.0*windowHeight / (distanceCompensate * sideBegDistance)));

			//toDisplay[i]->front.shape.setFillColor(sf::Color(0, 0, 255));	//
			//toDisplay[i]->front.shape.setOutlineColor(sf::Color(255, 0, 0)); // DO POPRAWY
			//toDisplay[i]->front.shape.setOutlineThickness(1);
			//toDisplay[i]->front.shape.setTexture(&toDisplay[i]->front.texture);//
			sf::Vector2f toTan = toDisplay[i]->front.shape.getPoint(2) - toDisplay[i]->front.shape.getPoint(1);
			double height = (toDisplay[i]->front.shape.getPoint(3) - toDisplay[i]->front.shape.getPoint(2)).y;
			double height2 = (toDisplay[i]->front.shape.getPoint(1) - toDisplay[i]->front.shape.getPoint(0)).y;
			double width = toTan.x;
			double ratio = height / width;
			double ratio2 = height2 / width;
			double tanAngle = 1.0*atan((1.0*toTan.y) / (1.0*toTan.x*ratio))*180.0 / M_PI;
			double tanAngle2 = 1.0*atan((1.0*toTan.y) / (1.0*toTan.x*ratio2))*180.0 / M_PI;
			if (((tanAngle2) <= 0) && ((tanAngle2) >= -30))
			{
				toDisplay[i]->front.shape.setTextureRect(sf::IntRect(250 * (30 - (int)((1.0*tanAngle2))), 0, 250, 250));
			}
			else
			{
				toDisplay[i]->front.shape.setTextureRect(sf::IntRect(250 * (30 + (int)((1.0*tanAngle))), 0, 250, 250));
			}
			objects.push_back(&toDisplay[i]->front.shape);
		}
		else if (player->position.y > ((toDisplay[i]->position.y) + 0.5)) // ty³
		{
			double deltaAngle = player->viewAngle - angle(player->position.x, player->position.y, toDisplay[i]->back.Beginning.x, toDisplay[i]->back.Beginning.y);
			if (deltaAngle < -180)
				deltaAngle += 360;
			if (deltaAngle > 180)
				deltaAngle -= 360;
			double sideBegDistance = distance(player->position.x, player->position.y, toDisplay[i]->back.Beginning.x, toDisplay[i]->back.Beginning.y);
			toDisplay[i]->back.shape.setPoint(0, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 - 1.0*windowHeight / (distanceCompensate * sideBegDistance)));
			toDisplay[i]->back.shape.setPoint(1, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 + 1.0*windowHeight / (distanceCompensate * sideBegDistance)));

			deltaAngle = player->viewAngle - angle(player->position.x, player->position.y, toDisplay[i]->back.End.x, toDisplay[i]->back.End.y);
			if (deltaAngle < -180)
				deltaAngle += 360;
			if (deltaAngle > 180)
				deltaAngle -= 360;
			sideBegDistance = distance(player->position.x, player->position.y, toDisplay[i]->back.End.x, toDisplay[i]->back.End.y);
			toDisplay[i]->back.shape.setPoint(2, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 + 1.0*windowHeight / (distanceCompensate * sideBegDistance)));
			toDisplay[i]->back.shape.setPoint(3, sf::Vector2f(windowWidth / 2 + (windowWidth / fieldOfView)*deltaAngle, windowHeight / 2 - 1.0*windowHeight / (distanceCompensate * sideBegDistance)));
			toDisplay[i]->back.shape.setFillColor(sf::Color(0, 255, 0));	//
			//toDisplay[i]->back.shape.setOutlineColor(sf::Color(255, 0, 0)); // DO POPRAWY
			//toDisplay[i]->back.shape.setOutlineThickness(1);				//
																			//	toDisplay[i]->back.shape.setTexture(&toDisplay[i]->back.texture);	

			sf::Vector2f toTan = toDisplay[i]->back.shape.getPoint(2) - toDisplay[i]->back.shape.getPoint(1);
			double height = (toDisplay[i]->back.shape.getPoint(3) - toDisplay[i]->back.shape.getPoint(2)).y;
			double height2 = (toDisplay[i]->back.shape.getPoint(1) - toDisplay[i]->back.shape.getPoint(0)).y;
			double width = toTan.x;
			double ratio = height / width;
			double ratio2 = height2 / width;
			double tanAngle = 1.0*atan((1.0*toTan.y) / (1.0*toTan.x*ratio))*180.0 / M_PI;
			double tanAngle2 = 1.0*atan((1.0*toTan.y) / (1.0*toTan.x*ratio2))*180.0 / M_PI;
			if (((tanAngle2) <= 0) && ((tanAngle2) >= -30))
			{
				toDisplay[i]->back.shape.setTextureRect(sf::IntRect(250 * (30 + (int)((1.0*tanAngle2))), 0, 250, 250));
			}
			else
			{
				toDisplay[i]->back.shape.setTextureRect(sf::IntRect(250 * (30 - (int)((1.0*tanAngle))), 0, 250, 250));
			}
			objects.push_back(&toDisplay[i]->back.shape);
		}
	}

	delete toDisplay;
	delete distanceOfWall;
}

DisplayList::DisplayList()
{
}


DisplayList::~DisplayList()
{
}
