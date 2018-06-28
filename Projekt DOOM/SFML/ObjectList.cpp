#include "ObjectList.h"


void ObjectList::load(Map* map) //! nie mo¿e polegaæ na sta³ych wartoœciach
{
	sf::Texture * t = new sf::Texture();
	t->loadFromFile("Graphics/textures.png");
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			if (map->flexMap[j][i] == 1) // zmiana j i i
			{
				objects.push_back(new Wall(sf::Vector2f(i, j), t));
			}

		}
	}
}

void ObjectList::loadFromFile(string path)
{
	fstream file;
	vector<string> data;
	file.open(path, ios::in);
	if (file.good() == false) return;

	for (int i = 0; !file.eof(); i++)
	{
		//! Do poprawy
		string word;
		getline(file, word, ';');
		data.push_back(word);
	}
	// Player nieznany, stworzyæ playera
	file.close();
	return;
}

void ObjectList::setPlayer(Player * newPlayer)
{
	players.push_back(newPlayer);
}

int ObjectList::objectCount()
{
	return objects.size();
}

ObjectList::ObjectList()
{
}


ObjectList::~ObjectList()
{
}
