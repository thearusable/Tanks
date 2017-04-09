#include "PowerUp.h"

PowerUp::PowerUp(void) :time(0), type()
, RenderElement(arus::Textures::empty, sf::Vector2f(0.f, 0.f))
{
	this->setVisible(false);
}

void PowerUp::create() {
	type = arus::PowerUp(std::rand() % 6);

	//ustalenie tekstury
	if (type == arus::PowerUp::granade) { //granade
		this->setTexture(arus::Textures::granadePU);
		time = 0.f;
	}
	else if (type == arus::PowerUp::shield) { //shield
		this->setTexture(arus::Textures::shieldPU);
		time = 10.f;
	}
	else if (type == arus::PowerUp::life) { // life
		this->setTexture(arus::Textures::lifePU);
		time = 0.f;
	}
	else if (type == arus::PowerUp::pistol) {//pistol
		this->setTexture(arus::Textures::pistolPU);
		time = 0.f;
	}
	else if (type == arus::PowerUp::swim) {//swim
		this->setTexture(arus::Textures::swimPU);
		time = 0.f;
	}
	else if (type == arus::PowerUp::speed) { //speed
		this->setTexture(arus::Textures::speedPU);
		time = 15.f;
	}
	//wyloowanie pozycji
	int posX = (std::rand() % 12) + 1;
	int posY = (std::rand() & 7) + 1;

	this->setScale(1.4f, 1.4f);

	this->setPosition(posX * 48.f + 30.f, posY * 54.f + 25.f);

	this->setVisible(true);
}

void PowerUp::take() {
	this->setVisible(false);
	this->setPosition(9999.f, 9999.f);
}

arus::PowerUp PowerUp::getType() {
	return type;
}

float PowerUp::getTime() {
	return time;
}