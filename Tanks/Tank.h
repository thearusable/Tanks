#pragma once
#include "RenderElement.h"
#include"PowerUp.h"
#include"AnimateElement.h"
class Tank :
	public RenderElement
{
public:
	Tank(void);
	Tank(arus::Textures texture, sf::Vector2f pos);
	virtual ~Tank();//

	virtual bool tryShoot() = 0; //
	virtual void update(float deltaTime) = 0; //
	virtual void setPowerUp(PowerUp& p) = 0; //

	virtual void ride(arus::Direction dir, float deltaTime);//

	void setFreezeDirection(arus::Direction dir); //
	arus::Direction getFreezeDirection(); //

	void setBulletType(arus::bulletType bullet); //
	arus::bulletType getBulletType(); //

	void setSpeed(float speed); //
	float getSpeed(); //

	void setColldown(float c); //
	float getColldown(); //

	void setTextureSource(int x, int y); //

	void setHP(int hp); //
	int getHP(); //

	void setDirection(arus::Direction d); //
	arus::Direction getDirection(); //

	void setPowerUp(arus::PowerUp p); //
	arus::PowerUp getPowerUp(); //

	void operator>>(sf::RenderWindow& target); //

protected:
	void updateTexture(); //

	float defaultSpeed, rideSpeed, colldown, powerUpTime;
	int HP;
	bool isMoving, canMove, canBeDestroyed;
	arus::PowerUp powerUpType;
	arus::Direction currDirection, lastDirection, freezeDirection;
	arus::bulletType bulletType;
	sf::Vector2i textureSource;
	AnimateElement * additional;
};
