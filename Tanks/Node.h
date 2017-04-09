#pragma once
#include "MapElement.h"
class Node
{
public:
	Node();
	Node(MapElement& element, int xx, int yy);
	virtual ~Node();

	Node& operator=(MapElement& element);

	void initNode();

	int getGScore(Node* node);
	int getHScore(Node* node);
	void computeScores(Node* endNode);

	bool hasParent();
	sf::Vector2i getIndex();

	//rodzic
	Node* parent;
	//wartosci
	int f, g, h;
	//index
	int x, y;
	//w ktorej liscie
	bool inOpenList, inClosedList, canDestroy, mustDestroy;
	//type of ground
	arus::Textures TextureType;
};
