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
	bool canDestroy;

protected:

	bool canCollidedWithTank, canCollidedWithBullet;
	arus::bulletType minimalBulletType;

};

