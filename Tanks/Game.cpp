#include "Game.h"

extern DataBase DATABASE;

Game::Game(MyWindow& window, bool TwoPlayers)
	:target(window)
	, stats(DATABASE.getStats())
	, gui(window)
	, Poziom()
	, isTwoPlayers(TwoPlayers)
	, isGameOver(false)
	, mapCompleted(false)
	, isSummary(false)
	, Gracz1(arus::bulletType::normal)
	, Gracz2(arus::bulletType::normal, false)
	, EnemyToSpawn()
	, powerUp()
{

	for (int i = 0; i< 3; ++i){
		PointsToSpawn[i] = false;
	}

	numerPoziomu = 1;
	Gracz1.hidePlayer();
	Gracz2.hidePlayer();
	createSpawnAnimation(3);
	if (isTwoPlayers) createSpawnAnimation(4);

	for (AnimateElement* s : SpawnPoints) s = nullptr;

	stats.p1POINTS = 0;
	stats.p2POINTS = 0;

	if (!isTwoPlayers) stats.p2LIVES = 0;

	BulletHolder.clear();
	BulletsToDestroy.clear();
	AnimetedElements.clear();
}

void Game::run(){
	Poziom.loadMap(stats.currLevel);/////
	EnemyHolder.clear();
	createSpawnAnimation(0);
	createSpawnAnimation(1);
	createSpawnAnimation(2);
	PointsToSpawn[0] = PointsToSpawn[1] = PointsToSpawn[2] = true;

	while (target.isOpen() && !isGameOver){
		events(); 
		collisions();
		update();
		render();
	}
}

void Game::nextMap(){

	isSummary = false;
	mapCompleted = false;

	stats.afterCompleteLvl();
	Poziom.loadMap(stats.currLevel);

	Gracz1.resetPlayer();
	if (isTwoPlayers) Gracz2.resetPlayer();
	
	BulletHolder.clear();
	BulletsToDestroy.clear();
	EnemyToDestroy.clear();

	EnemyHolder.clear();
	EnemyToSpawn = 3;
	createSpawnAnimation(0);
	createSpawnAnimation(1);
	createSpawnAnimation(2);
	PointsToSpawn[0] = PointsToSpawn[1] = PointsToSpawn[2] = true;

}

void Game::events(){
	sf::Event e;
	while (target.pollEvent(e)){
		switch (e.type){
		case sf::Event::KeyPressed:

			if (e.key.code == sf::Keyboard::Escape ||
				(e.key.code == sf::Keyboard::Return || e.key.code == sf::Keyboard::Escape || e.key.code == sf::Keyboard::Space) && isSummary == true){
				isGameOver = true;
				stats.resetToDefaultStats();
			}
			if (e.key.code == sf::Keyboard::T){ //ukonczenie lvla
				powerUp.create();
			}
			if (e.key.code == sf::Keyboard::Y){ //ukonczenie lvla
				Gracz2.hitPlayer(arus::bulletType::normal);

			}
			if (e.key.code == sf::Keyboard::F10){ //ukonczenie lvla
				mapCompleted = true;
			}
			if (e.key.code == sf::Keyboard::F11){ //ukonczenie gry
				isSummary = true;
				mapCompleted = true;
			}
			if ((e.key.code == sf::Keyboard::Space || e.key.code == sf::Keyboard::Return) && mapCompleted == true){ //ukonczenie lvla
				this->nextMap();
			}
			break;
		}

	}
	if (e.type == sf::Event::Closed) target.close();
	//gracz 1
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) Gracz1.ride(arus::Direction::down, target.timeElapsedLastFrame());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) Gracz1.ride(arus::Direction::up, target.timeElapsedLastFrame());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) Gracz1.ride(arus::Direction::left, target.timeElapsedLastFrame());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) Gracz1.ride(arus::Direction::right, target.timeElapsedLastFrame());
	else Gracz1.setFreezeDirection(arus::Direction::none);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		if (Gracz1.tryShoot()) {
			Bullet* temp = new Bullet(Gracz1.getDirection(), Gracz1.getPosition(), Gracz1.getBulletType());
			temp->bulletOwner = 1;
			BulletHolder.push_back(temp);
			Gracz1.setFreezeDirection(arus::Direction::none);
		}
	//gracz 2
	if (isTwoPlayers){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) Gracz2.ride(arus::Direction::down, target.timeElapsedLastFrame());
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) Gracz2.ride(arus::Direction::up, target.timeElapsedLastFrame());
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) Gracz2.ride(arus::Direction::left, target.timeElapsedLastFrame());
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) Gracz2.ride(arus::Direction::right, target.timeElapsedLastFrame());
		else Gracz2.setFreezeDirection(arus::Direction::none);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			if (Gracz2.tryShoot()){
				Bullet* temp = new Bullet(Gracz2.getDirection(), Gracz2.getPosition(), Gracz2.getBulletType());
				temp->bulletOwner = 2;
				BulletHolder.push_back(temp);
				Gracz2.setFreezeDirection(arus::Direction::none);
			}
	}
}

void Game::update(){

	for(Enemy* e : EnemyHolder){
		if(e != nullptr){
			e->update(target.timeElapsedLastFrame());
		}
	}

	this->Gracz1.update(target.timeElapsedLastFrame());
	if (isTwoPlayers){
		Gracz2.update(target.timeElapsedLastFrame());
	}

	for (Bullet* b : BulletHolder){
		if (b != nullptr) b->update();
	}

	if (stats.enemyCount <= 0){
		if (EnemyHolder.size() == 0) {
			mapCompleted = true;
			powerUp.take();
		}
	}
	if (stats.p1LIVES == 0){
		if (isTwoPlayers && stats.p2LIVES == 0){
			isSummary = true;
			mapCompleted = true;
			stats.currLevel = 1;
		}
	}
	//spawny
	if (PointsToSpawn[0] == true){//spawn przeciwnika po lewej
		if (SpawnPoints[0] == nullptr) {
			createSpawnAnimation(0);
			stats.enemyCount--;
		}
		if (SpawnPoints[0]->update() == true){
			EnemyHolder.push_back(new Enemy(Poziom, 0, 0, 0));
			SpawnPoints[0] = nullptr;
			PointsToSpawn[0] = false;
		}
	}
	//if (PointsToSpawn[1] == true){//spawn przeciwnika na srodku
	//	if (SpawnPoints[1] == nullptr) {
	//		createSpawnAnimation(1);
	//		stats.enemyCount--;
	//	}
	//	if (SpawnPoints[1]->update() == true){
	//		EnemyHolder.push_back(new Enemy(Poziom, 6, 0, 1));
	//		SpawnPoints[1] = nullptr;
	//		PointsToSpawn[1] = false;
	//	}
	//}
	//if (PointsToSpawn[2] == true){//spawn przeciwnika po prawej
	//	if (SpawnPoints[2] == nullptr){
	//		createSpawnAnimation(2);
	//		stats.enemyCount--;
	//	}
	//	if (SpawnPoints[2]->update() == true){
	//		EnemyHolder.push_back(new Enemy(Poziom, 12, 0, 2));
	//		SpawnPoints[2] = nullptr;
	//		PointsToSpawn[2] = false;
	//	}
	//}

	if (SpawnPoints[3] != nullptr){//gracz1
		if (SpawnPoints[3]->update() == true){
			Gracz1.resetPlayer();
			SpawnPoints[3] = nullptr;
		}
	}
	if (SpawnPoints[4] != nullptr){//gracz 2
		if (SpawnPoints[4]->update() == true){
			Gracz2.resetPlayer();
			SpawnPoints[4] = nullptr;
		}
	}

	for (unsigned int i = 0; i < EnemyHolder.size(); ++i){
		if (EnemyHolder[i] == nullptr) EnemyHolder.erase(EnemyHolder.begin() + i);
	}

	for (unsigned int i = 0; i < AnimetedElements.size(); ++i){
		if (AnimetedElements[i] != nullptr)
			if (AnimetedElements[i]->update() == true){
				AnimetedElements.erase(AnimetedElements.begin() + i);
			}
	}
	
	gui.update(isTwoPlayers, mapCompleted, isSummary);
}

void Game::render(){
	if (isGameOver) return;

	if (mapCompleted == false){//rysowanie podczas gry

		target.clear(sf::Color(125, 125, 125, 255));

		Poziom > target;

		for (Bullet* b : BulletHolder){
			if (b != nullptr) *b >> target;
		}

		Gracz1 >> target;
		if (isTwoPlayers){
			Gracz2 >> target;
		}

		for (Enemy* e : EnemyHolder){
			if (e != nullptr) *e >> target;
		}

		Poziom >> target;

		powerUp >> target;

		for (AnimateElement* a : SpawnPoints) if (a != nullptr) *a >> target;

		if (AnimetedElements.size() != 0){
			for (unsigned int i = 0; i < AnimetedElements.size(); ++i){
				if (AnimetedElements[i] != nullptr) *AnimetedElements[i] >> target;
			}
		}

	}
	gui.render(isTwoPlayers,mapCompleted,isSummary);

	target.display();
}

void Game::createBulletDestroyAnimation(Bullet * b){
	if (b == nullptr) return;
	sf::Vector2f pos = b->getPosition();
	if (b->getDirection() == arus::Direction::left){
		pos.x = b->getPosition().x + 4.f;
	}
	else if (b->getDirection() == arus::Direction::up){
		pos.y = b->getPosition().y + 4.f;
	}
	AnimetedElements.push_back(new AnimateElement(arus::Textures::bulletDestroy, pos, sf::Vector2f(44, 44), false, 1.f));
	AnimetedElements.back()->setScale(0.95f, 0.95f);
}

void Game::createTankDestroyAnimation(Tank* t){
	sf::Vector2f pos;
	pos.x = t->getPosition().x + 24.f;
	pos.y = t->getPosition().y + 27.f;

	AnimetedElements.push_back(new AnimateElement(arus::Textures::tankDestroy, pos, sf::Vector2f(109, 93), false, 1.2f));
}

void Game::createSpawnAnimation(int numerSpawnu){
	int x, y;

	if (numerSpawnu == 0){
		x = 0;
		y = 0;
	}
	if (numerSpawnu == 1){
		x = 6;
		y = 0;
	}
	if (numerSpawnu == 2){
		x = 12;
		y = 0;
	}
	if (numerSpawnu == 3){
		x = 4;
		y = 12;
	}
	if (numerSpawnu == 4){
		x = 8;
		y = 12;
	}

	sf::Vector2f pos(x * 54.f + 58.f, y * 48.f + 49.f);

	if (SpawnPoints[numerSpawnu] == nullptr){
		if (numerSpawnu == 0 && stats.enemyCount == 0){
			return;
		}
		else if (numerSpawnu == 1 && stats.enemyCount == 0){
			return;
		}
		else if (numerSpawnu == 2 && stats.enemyCount == 0){
			return;
		}
		else if (numerSpawnu == 3 && stats.p1LIVES == 0){
			return;
		}
		else if (numerSpawnu == 4 && stats.p2LIVES == 0){
			return;
		}
		SpawnPoints[numerSpawnu] = new AnimateElement(arus::Textures::spawn, pos, sf::Vector2f(42, 38), false, 1.2f);
	}
}

void Game::collisions(){
	//Bullet
	for (unsigned int bCount = 0; bCount < BulletHolder.size(); bCount++){//dla kazdej kuli sprawdz z:
		// kule z mapa - ready
		if (BulletHolder[bCount] != nullptr){
			for (int rCountX = 0; rCountX < 13; rCountX++){ //na osi X
				for (int rCountY = 0; rCountY < 13; rCountY++){ // na osi Y
					if (Poziom.mTiledMap[rCountX][rCountY].getColliderBullet()) // jezli klocek moze kolidowac z kula
						if (this->checkCollision(BulletHolder[bCount]->getSprite(), Poziom.mTiledMap[rCountX][rCountY].getSprite())){
							if (Poziom.mTiledMap[rCountX][rCountY].getTextureID() == arus::Textures::eagle){//jezeli orzel zdechl
								isSummary = true;
								mapCompleted = true;
								stats.currLevel = 1;
							}
							if (Poziom.mTiledMap[rCountX][rCountY].hit(BulletHolder[bCount]->getBulletType(), BulletHolder[bCount]->getDirection()) == 1){
								Poziom.destroyElementOfMap(rCountX, rCountY); //zniszczenie calosci klocka
							}
							//zmiana colldowna gracza na 0
							if (BulletHolder[bCount]->bulletOwner == 1) Gracz1.setColldown(0.2f);
							if (BulletHolder[bCount]->bulletOwner == 2) Gracz2.setColldown(0.2f);
							//dodanie kuli do tych przeznaczonych do zniszczenia
							BulletsToDestroy.push_back(bCount);
						}
				}
			}
			//kule z krawedziami mapy (poprawki w krawedzi mapy)
			for (int i = 0; i < 4; i++){
				if (checkCollision(BulletHolder[bCount]->getSprite(), Poziom.mEdge[i].getSprite())){
					BulletsToDestroy.push_back(bCount);
				}
			}
			//kule z graczami i przeciwnikami
			//gracz 1
			if (checkCollision(BulletHolder[bCount]->getSprite(), Gracz1.getSprite())
				&& BulletHolder[bCount]->bulletOwner != 1){
				BulletsToDestroy.push_back(bCount);
				if (Gracz1.hitPlayer(BulletHolder[bCount]->getBulletType()) == true){
					if (BulletHolder[bCount]->bulletOwner == 2) stats.p2POINTS -= 1000;
					createTankDestroyAnimation(&Gracz1);
					createSpawnAnimation(3);
					Gracz1.hidePlayer();
					if (stats.p1LIVES <= 0) Gracz1.hidePlayer();
				}
			}
			//gracz 2
			if (checkCollision(BulletHolder[bCount]->getSprite(), Gracz2.getSprite())
				&& BulletHolder[bCount]->bulletOwner != 2){
				BulletsToDestroy.push_back(bCount);
				if (Gracz2.hitPlayer(BulletHolder[bCount]->getBulletType()) == true){
					if (BulletHolder[bCount]->bulletOwner == 1) stats.p1POINTS -= 1000;
					createTankDestroyAnimation(&Gracz2);
					createSpawnAnimation(4);
					Gracz2.hidePlayer();
					if (stats.p2LIVES <= 0) Gracz2.hidePlayer();
				}
			}

			//przeciwnicy
			for (unsigned int i = 0; i < EnemyHolder.size(); i++){
				if (EnemyHolder[i] != nullptr){
					if (checkCollision(BulletHolder[bCount]->getSprite(), EnemyHolder[i]->getSprite())){
						BulletsToDestroy.push_back(bCount);
						EnemyToDestroy.push_back(i);
						//dodawanie punktow
						//e1 - random
						//e2 - normal
						//e3 - heavy
						//e4 - fast
			
						if (BulletHolder[bCount]->bulletOwner == 1){//P1
							if (EnemyHolder[i]->Type == arus::EnemyType::fast) {
								stats.e4p1++;
								stats.p1POINTS += 400;
							}
							if (EnemyHolder[i]->Type == arus::EnemyType::heavy) {
								stats.e3p1++;
								stats.p1POINTS += 300;
							}
							if (EnemyHolder[i]->Type == arus::EnemyType::normal) {
								stats.e2p1++;
								stats.p1POINTS += 200;
							}
							if (EnemyHolder[i]->Type == arus::EnemyType::random) {
								stats.e1p1++;
								stats.p1POINTS += 100;
							}
						}
						else if (BulletHolder[bCount]->bulletOwner == 2){
							if (EnemyHolder[i]->Type == arus::EnemyType::fast) {
								stats.e4p2++;
								stats.p2POINTS += 400;
							}
							if (EnemyHolder[i]->Type == arus::EnemyType::heavy) {
								stats.e3p2++;
								stats.p2POINTS += 300;
							}
							if (EnemyHolder[i]->Type == arus::EnemyType::normal) {
								stats.e2p2++;
								stats.p2POINTS += 200;
							}
							if (EnemyHolder[i]->Type == arus::EnemyType::random) {
								stats.e1p2++;
								stats.p2POINTS += 100;
							}
						}
					}
				}
			}

			//kule z kulami 
			for (unsigned int bCountB = 0; bCountB < BulletHolder.size(); bCountB++){
				if (BulletHolder[bCountB] != nullptr && bCount != bCountB)
					if (checkCollision(BulletHolder[bCountB]->getSprite(), BulletHolder[bCount]->getSprite())){
						BulletsToDestroy.push_back(bCount);
						BulletsToDestroy.push_back(bCountB);
					}
			}
		}
	}
	//z mapa
	for (int rCountX = 0; rCountX < 13; rCountX++){ //na osi X
		for (int rCountY = 0; rCountY < 13; rCountY++){ // na osi Y
			if (Poziom.mTiledMap[rCountX][rCountY].getColliderTank()){ // jezli klocek moze kolidowac z czolgiem
				//gracz 1
				if (checkCollision(Gracz1.getSprite(), Poziom.mTiledMap[rCountX][rCountY].getSprite())){
					Gracz1.setFreezeDirection(Gracz1.getDirection());
					correctPosition(Gracz1.getSprite(), Gracz1.getDirection(), Poziom.mTiledMap[rCountX][rCountY].getSprite());
				}
				//gracz 2
				if (isTwoPlayers){
					if (checkCollision(Gracz2.getSprite(), Poziom.mTiledMap[rCountX][rCountY].getSprite())){
						Gracz2.setFreezeDirection(Gracz2.getDirection());
						correctPosition(Gracz2.getSprite(), Gracz2.getDirection(), Poziom.mTiledMap[rCountX][rCountY].getSprite());
					}
				}

			}
			//przeciwnicy
			if (Poziom.mTiledMap[rCountX][rCountY].getColliderBullet()){
				for (unsigned int i = 0; i < EnemyHolder.size(); i++){
					if (EnemyHolder[i] != nullptr){
						if (checkCollision(EnemyHolder[i]->getSprite(), Poziom.mTiledMap[rCountX][rCountY].getSprite())){
							EnemyHolder[i]->setFreezeDirection(EnemyHolder[i]->getDirection());
							correctPosition(EnemyHolder[i]->getSprite(), EnemyHolder[i]->getDirection(), Poziom.mTiledMap[rCountX][rCountY].getSprite());
						}
					}
				}
			}
		}
	}
	//z krawiedzia mapy
	for (int i = 0; i < 4; i++){
		//gracz 1
		if (checkCollision(Gracz1.getSprite(), Poziom.mEdge[i].getSprite())){
			Gracz1.setFreezeDirection(Gracz1.getDirection());
			correctPosition(Gracz1.getSprite(), Gracz1.getDirection(), Poziom.mEdge[i].getSprite());
		}
		//gracz 2
		if (isTwoPlayers){
			if (checkCollision(Gracz2.getSprite(), Poziom.mEdge[i].getSprite())){
				Gracz2.setFreezeDirection(Gracz2.getDirection());
				correctPosition(Gracz2.getSprite(), Gracz2.getDirection(), Poziom.mEdge[i].getSprite());
			}
		}
		//przeciwnicy
		for (unsigned int i = 0; i < EnemyHolder.size(); i++){
			if (EnemyHolder[i] != nullptr){
				if (checkCollision(EnemyHolder[i]->getSprite(), Poziom.mEdge[i].getSprite())){
					EnemyHolder[i]->setFreezeDirection(EnemyHolder[i]->getDirection());
					correctPosition(EnemyHolder[i]->getSprite(), EnemyHolder[i]->getDirection(), Poziom.mEdge[i].getSprite());
				}
			}
		}
	}
	//z powerUpem
	for (unsigned int i = 0; i < EnemyHolder.size(); i++){
		if (EnemyHolder[i] != nullptr){
			if (checkCollision(powerUp.getSprite(), EnemyHolder[i]->getSprite())){
				if (powerUp.getType() == arus::PowerUp::granade){
					Gracz1.resetPlayer();
					if (isTwoPlayers) Gracz2.resetPlayer();
					stats.p1LIVES--;
					stats.p2LIVES--;
				}
				else if (powerUp.getType() == arus::PowerUp::life){
					stats.enemyCount += 10;
				}
				else if (powerUp.getType() == arus::PowerUp::pistol){
					EnemyHolder[i]->setBulletType(arus::bulletType::super);
				}
				else if (powerUp.getType() == arus::PowerUp::shield){
					EnemyHolder[i]->setPowerUp(powerUp);
				}
				else if (powerUp.getType() == arus::PowerUp::speed){
					EnemyHolder[i]->setSpeed(14.f);
				}
				else if (powerUp.getType() == arus::PowerUp::swim){
					EnemyHolder[i]->setPowerUp(powerUp);
				}
				powerUp.take();
			}
		}
	}
	if (checkCollision(powerUp.getSprite(), Gracz1.getSprite())){
		if (powerUp.getType() == arus::PowerUp::granade){
			EnemyToDestroy.clear();
			EnemyToSpawn = 3;
			 PointsToSpawn[0] = PointsToSpawn[1] = PointsToSpawn[2] = true;
			for (unsigned i = 0; i < EnemyHolder.size(); i++){
				if (EnemyHolder[i] != nullptr) EnemyToDestroy.push_back(i);
				if (stats.enemyCount > 0){
					int temp = EnemyHolder[EnemyToDestroy[i]]->spawnPoint;
					PointsToSpawn[temp] = true;
				}
				//conf.enemyCount--;
			}
		}
		else if (powerUp.getType() == arus::PowerUp::life){
			stats.p1LIVES++;
		}
		else Gracz1.setPowerUp(powerUp);
		powerUp.take();
	}
	if (isTwoPlayers){
		if (checkCollision(powerUp.getSprite(), Gracz2.getSprite())){
			if (powerUp.getType() == arus::PowerUp::granade){
				EnemyToDestroy.clear();
				if(stats.enemyCount > 2) PointsToSpawn[0] = PointsToSpawn[1] = PointsToSpawn[2] = true;
				for (unsigned i = 0; i < EnemyHolder.size(); i++){
					if (EnemyHolder[i] != nullptr) EnemyToDestroy.push_back(i);
					//conf.enemyCount--;
					if (stats.enemyCount > 0){
						int temp = EnemyHolder[EnemyToDestroy[i]]->spawnPoint;
						PointsToSpawn[temp] = true;
					}
				}
			}
			else if (powerUp.getType() == arus::PowerUp::life){
				stats.p2LIVES++;
			}
			else Gracz2.setPowerUp(powerUp);
			powerUp.take();
		}
	}

	//zderzenie dwoch graczy


	//niszczenie kul
	for (unsigned int i = 0; i < BulletsToDestroy.size(); i++){
		createBulletDestroyAnimation(BulletHolder[BulletsToDestroy[i]]);
		delete BulletHolder[BulletsToDestroy[i]];
		BulletHolder[BulletsToDestroy[i]] = nullptr;
	}
	BulletsToDestroy.clear();

	//niszczenie przeciwnikow
	for (unsigned int i = 0; i < EnemyToDestroy.size(); i++){
		//Data.get().enemyCount -= 1;
		if (stats.enemyCount > 0) PointsToSpawn[EnemyHolder[EnemyToDestroy[i]]->spawnPoint] = true;
		createTankDestroyAnimation(EnemyHolder[EnemyToDestroy[i]]);
		if (EnemyHolder[EnemyToDestroy[i]]->specialEnemy == true) powerUp.create();
		delete EnemyHolder[EnemyToDestroy[i]];
		EnemyHolder[EnemyToDestroy[i]] = nullptr;
	}
	EnemyToDestroy.clear();

}

bool Game::checkCollision(sf::Sprite& s1, sf::Sprite& s2){
	float
		e1Left = s1.getPosition().x,
		e1Right = e1Left + s1.getGlobalBounds().width,
		e1Top = s1.getPosition().y,
		e1Bottom = e1Top + s1.getGlobalBounds().height,

		e2Left = s2.getPosition().x,
		e2Right = e2Left + s2.getGlobalBounds().width,
		e2Top = s2.getPosition().y,
		e2Bottom = e2Top + s2.getGlobalBounds().height;

	if (e1Right >= e2Left && e1Left <= e2Right && e1Bottom >= e2Top && e1Top <= e2Bottom) return true;
	return false;
}

//s1 to obiekt ruchomy
void Game::correctPosition(sf::Sprite& s1, arus::Direction dir, sf::Sprite& s2){
	float
		e1Left = s1.getPosition().x,
		e1Right = e1Left + s1.getGlobalBounds().width,
		e1Top = s1.getPosition().y,
		e1Bottom = e1Top + s1.getGlobalBounds().height,

		e2Left = s2.getPosition().x,
		e2Right = e2Left + s2.getGlobalBounds().width,
		e2Top = s2.getPosition().y,
		e2Bottom = e2Top + s2.getGlobalBounds().height;

	if (dir == arus::Direction::up){ //uderzenie od dolu
		s1.setPosition(s1.getPosition().x, e2Bottom + 0.1f);
	}
	else if (dir == arus::Direction::down){ //uderzenie z gory
		s1.setPosition(s1.getPosition().x, e2Top - s1.getGlobalBounds().height - 0.1f);
	}
	else if (dir == arus::Direction::right){ //uderzenie z lewej
		s1.setPosition(e2Left - s1.getGlobalBounds().width - 0.1f, s1.getPosition().y);
	}
	else if (dir == arus::Direction::left){ //uderzenie z prawej5
		s1.setPosition(e2Right + 0.1f, s1.getPosition().y);
	}
}

void Game::correctPosition(Tank& t1, Tank& t2){

}