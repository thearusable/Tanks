#pragma once
#include "Tank.h"
#include "Level.h"
#include "Node.h"
#include "Bullet.h"

#include<list>
#include<iostream>
#include<queue>

class Enemy :
	public Tank
{
public:
	Enemy(Level& poz, std::vector<Bullet*>& bh, int xx, int yy, int spawn);
	virtual ~Enemy();

	void setPowerUp(PowerUp& p);
	void setPowerUp(arus::PowerUp p);
	arus::PowerUp getPowerUp();
	void update(float deltaTime);
	virtual bool tryShoot() override;

	int pointsFromKill, spawnPoint;
	arus::EnemyType Type;
	bool specialEnemy;

	/////////below to path finding and ai logic

	void calculateNextDir();
	void nextTarget();

	//pathfinder
	void astar();
	void calcRandomCoord();
	void followPath(float deltaTime);
	sf::Vector2f IndexToPosition(int indexX, int indexY);
	//virtual void ride(arus::Direction dir, float deltaTime) override;

protected:
	Level& level;
	std::vector<Node*> path;

	std::vector<Bullet*>& BulletHolder;
	Node map[13][13];

	int IndexX, IndexY, pathTargetX, pathTargetY;
	Node* currTarget;
};
