#pragma once
#include"RenderElement.h"
#include "arus.h"
class Bullet : public RenderElement
{
public:
	Bullet(arus::Direction dir, sf::Vector2f pos, arus::bulletType type = arus::bulletType::normal, float s = 8.0f);

	void update();

	arus::Direction getDirection();
	arus::bulletType getBulletType();

	/*
	1 - pierwszy gracz
	2 - drugi gracz
	3 - komp
	*/
	int bulletOwner;
private:

	float bulletSpeed;
	arus::Direction mDirection;
	arus::bulletType mType;
};

