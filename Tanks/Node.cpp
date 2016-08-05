#include "Node.h"


Node::Node()
{
	mustDestroy = false;
	initNode();
}

Node::Node(MapElement & element, int xx, int yy)
	: x(xx)
	, y(yy)
{
	TextureType = element.getTextureID();
	canDestroy = element.canDestroy;
	mustDestroy = false;
	initNode();
}

Node::~Node()
{
}

Node & Node::operator=(MapElement & element)
{
	TextureType = element.getTextureID();
	canDestroy = element.canDestroy;

	return *this;
}

void Node::initNode() {
	inClosedList = false;
	inOpenList = false;
	parent = nullptr;
	f = g = h = 0;
}

sf::Vector2i Node::getIndex() {
	return sf::Vector2i(x, y);
}

int Node::getGScore(Node* p) {
	
	int temp = 0;
	if (TextureType == arus::Textures::grass) temp -= 5;
	if (TextureType == arus::Textures::brick || TextureType == arus::Textures::steel) temp += 50;

	if (p == nullptr)
		return temp + 10;

	return p->g + temp + 10;
}

int Node::getHScore(Node* p) {
	return (abs(p->x - x) + abs(p->y - y)) * 10;
}

void Node::computeScores(Node* end) {
	g = getGScore(parent);
	h = getHScore(end);
	f = g + h;
}

bool Node::hasParent() {
	return (parent != nullptr);
}