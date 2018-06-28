#include "Map.h"



void Map::checkCollision(sf::Vector2f &position, double vecX, double vecY, double size) // od pozycji gracza +/- 0.5 (krawêdŸ œciany)
{
	if ((static_cast<int>(position.y + vecY + 0.5 + ((vecY > 0) + (vecY < 0))*size) > (flexMap.size() - 1)) || (static_cast<int>(position.x + vecX + 0.5 + ((vecX > 0) + (vecX < 0))*size)) > (flexMap.size() - 1)) return;
	else if ((static_cast<int>(position.y + vecY + 0.5 + ((vecY > 0) - (vecY < 0))*size) < 0) || (static_cast<int>(position.x + vecX + 0.5 +((vecX > 0) - (vecX < 0))*size) < 0)) return;

	double copyX = position.x;
	if (flexMap[static_cast<int>(position.y + 0.5)][static_cast<int>(position.x + vecX + 0.5 + ((vecX > 0) - (vecX < 0))*size)] == 1) // jesteœ w œcianie w poziomie
	{
	}
	else copyX += vecX; // przesuñ normalnie
	if (flexMap[static_cast<int>(position.y + vecY + 0.5 + ((vecY > 0) - (vecY < 0))*size)][static_cast<int>(position.x + 0.5)] == 1) // jesteœ w œcianie w pionie
	{
	}
	else position.y += vecY;
	position.x = copyX;
}
		

Map::Map(string path)
{
	BMP MapImage;
	MapImage.ReadFromFile(path.c_str()); //! dodaæ obs³ugê wyj¹tków
	flexMap.resize(MapImage.TellHeight());
	int width = MapImage.TellWidth(); // unikam wywo³ywania funkcji TellWidth() i-razy
	for (int i = 0; i < MapImage.TellHeight(); i++) // y
	{
		flexMap[i].resize(width);

		for (int j = 0; j < MapImage.TellWidth(); j++) // x
		{
			RGBApixel Check = MapImage.GetPixel(j, i);
			// mo¿liwe problemy z kana³em alpha?
			if ( (static_cast<int>(Check.Red) == 255) && (static_cast<int>(Check.Green) == 255) && (static_cast<int>(Check.Blue) == 255) ) // sprawdŸ, czy bia³y
			{
				flexMap[i][j] = 0; // wolna przestrzeñ
			}
			//else if (0) {} // miejsce na mo¿liwe nowe elementy mapy
			else flexMap[i][j] = 1; // œciana
		}
	}
}


Map::~Map()
{
}

