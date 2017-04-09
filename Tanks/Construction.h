#pragma once
#include"MyWindow.h"
#include"RenderElement.h"
#include<fstream>
class Construction
{
public:
	Construction(MyWindow& window);

	bool start();

private:
	void events();
	void update();
	void render();

	void saveMap();

	MyWindow& target;
	sf::Vector3i cursorVector;
	RenderElement cursor;
	sf::RectangleShape backShape, backShapeNext;
	RenderElement kafelki[13][13], elementy[15], underCursor, nextElement;
	int kafelkiID[13][13];
	sf::Vector2f mapPos;
	sf::Text next;

	Stats& stats;

	bool stillBuildingMap, itSaved;
};
