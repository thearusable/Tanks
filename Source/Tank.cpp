#include "Tank.h"

Tank::Tank()
	: powerUpType(arus::PowerUp::none)
	, powerUpTime(0)
	, colldown(0)
	, rideSpeed(120)
	, defaultSpeed(120)
	, HP(1)
	, currDirection(arus::Direction::down)
	, lastDirection(arus::Direction::down)
	, freezeDirection(arus::Direction::none)
	, isMoving(false)
	, canMove(true)
	, textureSource()
	, canBeDestroyed(true)
	, bulletType(arus::bulletType::normal)
{
	updateTexture();
	additional = nullptr;
}

Tank::Tank(arus::Textures texture, sf::Vector2f pos)
	: powerUpType(arus::PowerUp::none)
	, powerUpTime(0)
	, colldown(0)
	, rideSpeed(120)
	, defaultSpeed(120)
	, HP(1)
	, currDirection(arus::Direction::down)
	, lastDirection(arus::Direction::down)
	, freezeDirection(arus::Direction::none)
	, isMoving(false)
	, canMove(true)
	, textureSource()
	, canBeDestroyed(true)
	, bulletType(arus::bulletType::normal)
	, RenderElement(texture, pos)
{
	updateTexture();
	additional = nullptr;
}

Tank::~Tank(void)
{
}

void Tank::ride(arus::Direction dir, float deltaTime) {
	if (dir == freezeDirection) {
		this->updateTexture();
		return;
	}
	else freezeDirection = arus::Direction::none;
	sf::Vector2f pos(0.f, 0.f);
	if (canMove) {
		this->currDirection = dir;

		switch (dir) {
		case arus::Direction::up:
			pos.y -= rideSpeed;
			isMoving = true;
			break;
		case arus::Direction::down:
			pos.y = rideSpeed;
			isMoving = true;
			break;
		case arus::Direction::left:
			pos.x -= rideSpeed;
			isMoving = true;
			break;
		case arus::Direction::right:
			pos.x = rideSpeed;
			isMoving = true;
			break;
		}
	}
	this->move(pos.x * deltaTime, pos.y * deltaTime);
	this->updateTexture();
	if (additional != nullptr) additional->setPosition(this->getPosition().x + 27, this->getPosition().y);
}

void Tank::setFreezeDirection(arus::Direction dir) {
	freezeDirection = dir;
}

arus::Direction Tank::getFreezeDirection() {
	return freezeDirection;
}

void Tank::setBulletType(arus::bulletType b) {
	bulletType = b;
}

arus::bulletType Tank::getBulletType() {
	return bulletType;
}

void Tank::setSpeed(float s) {
	rideSpeed = s;
}

float Tank::getSpeed() {
	return rideSpeed;
}

void Tank::setColldown(float c) {
	colldown = c;
}

float Tank::getColldown() {
	return colldown;
}

void Tank::setTextureSource(int x, int y) {
	textureSource.x = x;
	textureSource.y = y;
}

void Tank::setHP(int h) {
	HP = h;
}

int Tank::getHP() {
	return HP;
}

void Tank::setDirection(arus::Direction d) {
	lastDirection = currDirection;
	currDirection = d;
}

arus::Direction Tank::getDirection() {
	return currDirection;
}

void Tank::setPowerUp(arus::PowerUp p) {
	powerUpType = p;
	powerUpTime = 0;
}

arus::PowerUp Tank::getPowerUp() {
	return powerUpType;
}

void Tank::operator>>(sf::RenderWindow& target) {
	target.draw(mSprite);
	if (additional != nullptr) *additional >> target;
}
//
void Tank::updateTexture() {
	if (currDirection != lastDirection) {
		lastDirection = currDirection;
		if (currDirection == arus::Direction::down) textureSource.y = 3;
		else if (currDirection == arus::Direction::left) textureSource.y = 2;
		else if (currDirection == arus::Direction::right) textureSource.y = 1;
		else if (currDirection == arus::Direction::up) textureSource.y = 0;
		textureSource.x = 0;
	}
	if (isMoving) {
		if (textureSource.x) textureSource.x = 0;
		else textureSource.x = 1;
	}

	this->setTextureRect(sf::IntRect(textureSource.x * 48, textureSource.y * 48, 48, 48));
}