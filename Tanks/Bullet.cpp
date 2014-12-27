#include "Bullet.h"


Bullet::Bullet(arus::Direction dir, sf::Vector2f pos, arus::bulletType type, float s)
	: mDirection(dir)
	, mType(type)
	, bulletOwner(3)
	, bulletSpeed(s)
{
	if (type == arus::bulletType::normal){
		this->setTexture(arus::Textures::bullet);
	}
	else if (type == arus::bulletType::super){
		this->setTexture(arus::Textures::sBullet);
	}
	this->setOriginToCenter();
	this->setPosition(pos.x, pos.y);
	if (mDirection == arus::Direction::up){
		this->setRotation(270.f);
		this->setPosition(pos.x + 24, pos.y);
	}
	else if (mDirection == arus::Direction::down){
		this->setRotation(90.f);
		this->setPosition(pos.x + 24, pos.y + 48);
	}
	else if (mDirection == arus::Direction::left){
		this->setRotation(180.f);
		this->setPosition(pos.x, pos.y + 24);
	}
	else if (mDirection == arus::Direction::right){
		this->setRotation(0.f);
		this->setPosition(pos.x + 48, pos.y + 24);
	}
}

void Bullet::update(){
	if (this->mDirection == arus::Direction::up){
		//leci w gore
		this->move(0, -bulletSpeed);
	}
	else if (this->mDirection == arus::Direction::down){
		//leci w dol
		this->move(0, bulletSpeed);
	}
	else if (this->mDirection == arus::Direction::left){
		//leci w lewo
		this->move(-bulletSpeed, 0);
	}
	else if (this->mDirection == arus::Direction::right){
		//leci w prawo
		this->move(bulletSpeed, 0);
	}
}

arus::Direction Bullet::getDirection(){
	return mDirection;
}

arus::bulletType Bullet::getBulletType(){
	return mType;
}
