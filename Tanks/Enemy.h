#pragma once
#include "Tank.h"
#include "Level.h"
#include "MapElement.h"

#include<list>
#include<iostream>
#include<queue>

class Enemy :
	public Tank
{
public:
	Enemy(Level& poz, int xx, int yy, int spawn);
	virtual ~Enemy();

	void setPowerUp(PowerUp& p); //gdy podniesie sie power up
	void setPowerUp(arus::PowerUp p);
	arus::PowerUp getPowerUp();
	virtual bool tryShoot() override;

	void update(float deltaTime);
	void calculateNextDir();
	void nextTarget();

	//pathfinder
	bool astar(int desX, int desY);

	void operator ! ();
	int pointsFromKill, spawnPoint;
	arus::EnemyType Type;
	bool specialEnemy;

	Level sciezka;
protected:
	std::vector<MapElement*> path;
	Level& poziom;


	int posX, posY, pathTargetX, pathTargetY, currTargetX, currTargetY;
	MapElement* currTarget;
};

