#include "Bullet.h"


Bullet::Bullet(arus::Direction dir, sf::Vector2f pos, arus::bulletType type, float s)
	: mDirection(dir)
	, mType(type)
	, bulletOwner(3)
	, bulletSpeed(s)
	, RenderElement()
{
	this->setPosition(pos.x, pos.y);

	if (type == arus::bulletType::normal){
		this->setTexture(arus::Textures::bullet);
	}
	else if (type == arus::bulletType::super){
		this->setTexture(arus::Textures::sBullet);
	}
	std::cout << "Texture " << mTexture.getSize().x << " " << mTexture.getSize().y << std::endl;
	std::cout << "Sprite  " << mSprite.getGlobalBounds().width << " " << mSprite.getGlobalBounds().height << std::endl;
	if (mDirection == arus::Direction::up){
		//this->setPosition(pos.x, pos.y - 20.f);
		//this->setRotation(270.f);
		
	}
	else if (mDirection == arus::Direction::down){
		//this->setPosition(pos.x, pos.y + 20.f);
		//this->setRotation(90.f);
		
	}
	else if (mDirection == arus::Direction::left){
		//this->setPosition(pos.x - 20.f, pos.y);
		//this->setRotation(180.f);
		
	}
	else if (mDirection == arus::Direction::right){
		//this->setPosition(pos.x + 20.f, pos.y);
		//this->setRotation(0.f);
		
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
