#pragma once
#include"MapElement.h"
#include"MyWindow.h"
#include<fstream>
#include<string>

class Level
{
public:
	Level(void);

	void loadMap(unsigned int x); //laduje konkretna mape
	void destroyElementOfMap(unsigned int x, unsigned int y);

	void operator > (MyWindow& target); //1 faza rysowania
	void operator >> (MyWindow& target);//2 faza rysowania
	void clearMap(); //czyszczenie mapy
	MapElement& getMapElement(int x, int y);

	MapElement mTiledMap[13][13];
	MapElement mEdge[4];
protected:
	MapElement elementy[15];

	sf::Vector2f mapPosition;
	sf::RectangleShape background;
};
