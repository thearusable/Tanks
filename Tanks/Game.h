#pragma once
#include"MyWindow.h"
#include"Level.h"
#include"Bullet.h"
#include"Player.h"
#include"Enemy.h"
#include"PowerUp.h"
#include"GUI.h"

class Game
{
public:
	Game(MyWindow& window, bool TwoPlayers = false);
	//true gdy ukonczony lvl
	void run();

protected:
	void events();
	void update();
	void render();

	void nextMap();
	void collisions();
	bool checkCollision(sf::Sprite& s1, sf::Sprite& s2);
	//czolg z plansza
	void correctPosition(sf::Sprite& s1, arus::Direction dir, sf::Sprite& s2);
	//czolg z czolgiem
	void correctPosition(Tank& t1, Tank& t2);
	void createBulletDestroyAnimation(Bullet* b);
	void createTankDestroyAnimation(Tank* t);
	void createSpawnAnimation(int numerSpawnu);

	//game
	GUI gui;
	MyWindow& target;
	Level Poziom;
	Player Gracz1, Gracz2;
	std::vector<Enemy*> EnemyHolder;
	std::vector<Bullet*> BulletHolder;
	std::vector<int> BulletsToDestroy;
	std::vector<int> EnemyToDestroy;
	PowerUp powerUp;
	std::vector<AnimateElement *> AnimetedElements;
	AnimateElement * SpawnPoints[5];
	bool PointsToSpawn[3];
	bool isTwoPlayers, isGameOver, isSummary, mapCompleted;//
	
	int EnemyToSpawn, numerPoziomu;
	
	Stats& stats;
};

