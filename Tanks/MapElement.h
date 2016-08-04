#pragma once
#include "RenderElement.h"
class MapElement :
	public RenderElement
{
public:
	MapElement(void);
	MapElement(MapElement& m);
	MapElement(RenderElement& r);

	void setSize(sf::Vector2f& size);
	void setBulletTypeCanDestroy(arus::bulletType b = arus::bulletType::normal);
	void setColliderWithTank(bool tank);
	void setColliderWithBullet(bool bullet);
	void setColor(sf::Color c);

	bool getColliderTank();
	bool getColliderBullet();

	/*param: przekazac direction kuli !!
	return int:
	-2 -> kula nie reaguje z tym typem elementu
	-1 -> trafiono w stal za slaba kula
	0 -> zniszczenie kawalka
	1 -> zniszczenie calosci*/
	int hit(arus::bulletType bullet, arus::Direction from);//

	//Node do obliczen A*
	void initNode();
	void setIndex(int xx, int yy);
	sf::Vector2i getIndex();
	MapElement* getParent();
	void setParent(MapElement* p);

	int getGScore();
	int getGScore(MapElement* p);
	int getHScore();
	int getHScore(MapElement* p);
	int getFScore();

	void computeScores(MapElement* end);
	bool hasParent();

	bool operator==(MapElement* p);

	int x, y;
	bool inOpenList, inClosedList;
	bool mustDestroy = false;
protected:
	bool canCollidedWithTank, canCollidedWithBullet;
	arus::bulletType minimalBulletType;
	//Node do obliczen A*
	
	MapElement* parent; // tego pewnie tu nie bedzie
	int f, g, h;
	bool canDestroy;
};

