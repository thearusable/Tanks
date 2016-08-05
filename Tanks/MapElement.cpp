#include "MapElement.h"


MapElement::MapElement(void)
	:canCollidedWithBullet(false)
	, canCollidedWithTank(false)
	, minimalBulletType(arus::bulletType::normal)
	, canDestroy(true)
{
}

MapElement::MapElement(MapElement& m){
	canCollidedWithBullet = m.getColliderBullet();
	canCollidedWithTank = m.getColliderTank();
	minimalBulletType = m.minimalBulletType;
	canDestroy = m.canDestroy;
}

MapElement::MapElement(RenderElement& r)
	: RenderElement(r)
	, canCollidedWithBullet(false)
	, canCollidedWithTank(false)
	, minimalBulletType(arus::bulletType::normal)
	, canDestroy(true)
{

}

void MapElement::setSize(sf::Vector2f& size){
	this->mTexture.create(unsigned(size.x), unsigned(size.y));
	this->mSprite.setTexture(this->mTexture);
}

void MapElement::setBulletTypeCanDestroy(arus::bulletType bullet){
	this->minimalBulletType = bullet;
}

void MapElement::setColliderWithTank(bool tank){
	this->canCollidedWithTank = tank;
}

void MapElement::setColliderWithBullet(bool bullet){
	this->canCollidedWithBullet = bullet;
}

void MapElement::setColor(sf::Color c){
	this->mSprite.setColor(c);
}

bool MapElement::getColliderBullet(){
	return canCollidedWithBullet;
}

bool MapElement::getColliderTank(){
	return canCollidedWithTank;
}

int MapElement::hit(arus::bulletType bullet, arus::Direction from){
	if (this->canCollidedWithBullet == false) return -2;
	if (bullet < this->minimalBulletType) return -1;

	int howMany = 0;
	if (from == arus::Direction::down || from == arus::Direction::up){ //gora dol
		if (bullet == arus::bulletType::normal){ //normalna kula
			if (getTextureID() == arus::Textures::brick)	howMany = 12;
		}
		else if (bullet == arus::bulletType::super){ //super kula
			if (getTextureID() == arus::Textures::brick) howMany = 24;
			else if (getTextureID() == arus::Textures::steel) howMany = 12; //ilosc pikseli z dupy
		}
	}
	else if (from == arus::Direction::left || from == arus::Direction::right){
		if (bullet == arus::bulletType::normal){ //normalna kula
			if (getTextureID() == arus::Textures::brick)	howMany = 14;
		}
		else if (bullet == arus::bulletType::super){ //super kula
			if (getTextureID() == arus::Textures::brick) howMany = 28;
			else if (getTextureID() == arus::Textures::steel) howMany = 14; //ilosc pikseli z dupy
		}
	}

	sf::IntRect newRect;
	sf::IntRect oldRect = this->getTextureRect();

	if (from == arus::Direction::up){ //hit z dolu
		newRect.height = oldRect.height - howMany;
		newRect.width = oldRect.width;
		newRect.left = oldRect.left;
		newRect.top = oldRect.top;

		this->setTextureRect(newRect);
	}
	else if (from == arus::Direction::down){ //hit z gory
		newRect.height = oldRect.height - howMany;
		newRect.width = oldRect.width;
		newRect.left = oldRect.left;
		newRect.top = oldRect.top + howMany;

		this->setTextureRect(newRect);
		this->move(0.f, float(howMany));
	}
	else if (from == arus::Direction::left){ //hit z prawej
		newRect.height = oldRect.height;
		newRect.width = oldRect.width - howMany;
		newRect.left = oldRect.left;
		newRect.top = oldRect.top;

		this->setTextureRect(newRect);
	}
	else if (from == arus::Direction::right){ //hit z lewej
		newRect.height = oldRect.height;
		newRect.width = oldRect.width - howMany;
		newRect.left = oldRect.left + howMany;
		newRect.top = oldRect.top;
		this->setTextureRect(newRect);
		this->move(float(howMany), 0.f);
	}
	if (newRect.height <= 0 || newRect.width <= 0) return 1;
	else return 0;
}

