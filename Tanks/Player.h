#pragma once
#include "Tank.h"
#include"DataBase.h"
class Player :
	public Tank
{
public:
	Player(arus::bulletType bullet, bool isFirst);
	virtual ~Player();

	void resetPlayer();
	void hidePlayer();
	void showPlayer();
	bool hitPlayer(arus::bulletType bullet);

	virtual bool tryShoot();
	virtual void update(float deltaTime);
	virtual void setPowerUp(PowerUp& p);

protected:
	bool isFirstPlayer;
	Stats& stats;
};

