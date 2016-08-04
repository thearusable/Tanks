#include "Player.h"

extern DataBase DATABASE;

Player::Player(arus::bulletType bullet, bool isFirst)
	:stats(DATABASE.getStats())
	, isFirstPlayer(isFirst)
{
	canMove = true;
	bulletType = bullet;
	resetPlayer();
	setScale(0.9f, 0.9f);
}

Player::~Player(){
	
}


void Player::resetPlayer(){
	delete additional;
	additional = nullptr;
	canMove = true;
	setBulletType(bulletType);
	setFreezeDirection(arus::Direction::none);
	lastDirection = arus::Direction::up;
	currDirection = arus::Direction::up;
	setSpeed(defaultSpeed);
	if (bulletType == arus::bulletType::normal){
		if (isFirstPlayer) this->setTexture(arus::Textures::player11);
		else this->setTexture(arus::Textures::player21);
	}
	if (isFirstPlayer && stats.p1LIVES == 0) return;
	else if (!isFirstPlayer && stats.p2LIVES == 0) return;

	if (isFirstPlayer) this->setPosition(4.f*54.f + 34.f, 12 * 48.f + 25.f);
	else this->setPosition(8.f*54.f + 34.f, 12 * 48.f + 25.f);

	this->setTextureRect(sf::IntRect(0 * 48, 0 * 48, 48, 48));
	this->setTextureSource(0, 0);
}

void Player::hidePlayer(){
	resetPlayer();
	setVisible(false);
	canMove = false;
	setPosition(3000.f, 3000.f);
}
void Player::showPlayer(){
	resetPlayer();
	setVisible(true);
	canMove = true;
}

bool Player::hitPlayer(arus::bulletType bullet){
	if (this->powerUpType == arus::PowerUp::shield) return false;

	if (additional != nullptr){
		delete additional;
		additional = nullptr;
	}
	if (powerUpType == arus::PowerUp::pistol){
		setBulletType(arus::bulletType::normal);
		Tank::setPowerUp(arus::PowerUp::none);
		if (isFirstPlayer == true){
			this->setTexture(arus::Textures::player11);
		}
		else this->setTexture(arus::Textures::player21);

		this->updateTexture();
		HP--;
		return false;
	}

	if (isFirstPlayer && stats.p1LIVES == 0) return true;
	else if (!isFirstPlayer && stats.p2LIVES == 0) return true;

	if (bullet == arus::bulletType::normal) HP--;
	else if (bullet == arus::bulletType::super) HP -= 2;

	if (HP <= 0){
		if (isFirstPlayer) stats.p1LIVES--;
		else if (!isFirstPlayer) stats.p2LIVES--;
	}

	return true;
}

bool Player::tryShoot(){
	if (colldown <= 0.f){
		colldown = 1.f;
		return true;
	}
	//jezeli ma sie 0 zyc to pruba pozyczenia od 2 gracza
	if (isFirstPlayer && stats.p1LIVES == 0){
		if (stats.p2LIVES > 1) {
			stats.p2LIVES--;
			stats.p1LIVES++;
			this->showPlayer();
		}
	}
	else if (!isFirstPlayer && stats.p2LIVES == 0){
		if (stats.p1LIVES > 1){
			stats.p1LIVES--;
			stats.p2LIVES++;
			this->showPlayer();
		}
	}
	return false;
}

void Player::update(float deltaTime){
	if (colldown > 0.f) colldown -= deltaTime;
	if (powerUpTime > 0.f) powerUpTime -= deltaTime;
	if (powerUpTime <= 0.f && (powerUpType == arus::PowerUp::shield || powerUpType == arus::PowerUp::speed)){
		powerUpType = arus::PowerUp::none;
		delete additional;
		additional = nullptr;
	}
	if (additional != nullptr) additional->update();
}

void Player::setPowerUp(PowerUp& p){
	powerUpType = p.getType();
	powerUpTime = p.getTime();

	if (powerUpType == arus::PowerUp::swim){
		delete additional;
		additional = nullptr;
		additional = new AnimateElement(arus::Textures::swim, this->getPosition(), sf::Vector2f(36, 32));
		additional->setScale(1.4f, 1.4f);
		this->HP++;
	}
	else if (powerUpType == arus::PowerUp::shield){
		delete additional;
		additional = nullptr;
		additional = new AnimateElement(arus::Textures::shield, this->getPosition(), sf::Vector2f(36, 32));
		additional->setScale(1.4f, 1.4f);
	}
	else if (powerUpType == arus::PowerUp::pistol){
		this->setBulletType(arus::bulletType::super);
		if (this->isFirstPlayer) this->setTexture(arus::Textures::player12);
		else this->setTexture(arus::Textures::player22);
	}
	else if (powerUpType == arus::PowerUp::speed){
		rideSpeed += 5.f;
	}
}