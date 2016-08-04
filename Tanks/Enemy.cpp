#include "Enemy.h"



Enemy::Enemy(Level& poz, int xx, int yy, int spawn) :poziom(poz)
{
	sciezka.clearMap();
	this->setPowerUp(arus::PowerUp::none);
	spawnPoint = spawn;
	srand(unsigned(time(NULL)));
	int temp = rand() % 4 + 1;
	pointsFromKill = temp * 100;
	//random
	if (temp == 1) {
		rideSpeed = 10;
		this->setTexture(arus::Textures::enemyRandom);
		Type = arus::EnemyType::random;
	}
	else if (temp == 2) { //normal
		rideSpeed = 11;
		this->setTexture(arus::Textures::enemyNormal);
		Type = arus::EnemyType::normal;
	}
	else if (temp == 3) {//heavy
		this->setPowerUp(arus::PowerUp::pistol);
		this->setTexture(arus::Textures::enemyHeavy);
		rideSpeed = 9;
		Type = arus::EnemyType::heavy;
	}
	else if (temp == 4) { //fast
		rideSpeed = 12;
		this->setTexture(arus::Textures::enemyFast);
		Type = arus::EnemyType::fast;
	}

	int temp2 = rand() % 10 + 1;
	if (temp2 == 1) specialEnemy = true;
	else specialEnemy = false;

	posX = xx;
	posY = yy;
	this->setPosition(xx * 54.f + 30.f + 4, yy * 48.f + 25.f + 3);
	path.clear();
	currDirection = arus::Direction::down;
	this->updateTexture();
	this->setScale(0.9f, 0.9f);
	currTarget = nullptr;
	pathTargetX = pathTargetY = currTargetX = currTargetY = 0;

	//test

	pathTargetX = rand() % 13;  //tu beda losowania 
	pathTargetY = rand() % 13;
	astar(pathTargetX, pathTargetY);
}


Enemy::~Enemy(void)
{
}

bool Enemy::tryShoot() {
	if (colldown <= 0.f) {
		colldown = 1.f;
		return true;
	}
	return false;
}

void Enemy::operator!() {
	std::cout << "ilosc elementow w sciezce: " << path.size() << std::endl << "Elementy w sciezce:" << std::endl;
	for (unsigned int i = 0; i < path.size(); i++)
		std::cout << path[i]->x << " " << path[i]->y << std::endl;
}

void Enemy::update(float deltaTime) {

	if (path.empty()) { //jezeli sciezka nic nie przechowuje
						//std::cout<<"dlugosc sciezki: "<<path.size()<<std::endl;
		//nextTarget();
	}
	//std::cout << "obecny cel: " << pathTargetX << " " << pathTargetY << std::endl;

	/*
	if(!path.empty()) {
	nextTarget();
	std::cout<<"dlugosc sciezki"<<path.size()<<std::endl;
	}
	*/
	if (currTarget != nullptr) {
		//obliczenie wspolrzednych x i y w tablicy
		posX = int((this->getPosition().x - 30.f) / 54.f);
		posY = int((this->getPosition().y - 25.f) / 48.f);
		std::cout << "posX: " << posX << " posY: " << posY << std::endl;
	//
	//	//if(currTarget->mustDestroy == true){
	//	//lewo
	//	//arus::Direction dir = calculateNextDir();
	//	//if(dir != currDirection && dir != arus::Direction::none) {
	//	//	currDirection = dir;
	//	//	nextTarget();
	//	//}
	//	//if(currDirection == arus::Direction::left && getPosition().x < currTarget->position.x) nextTarget();
	//	//if(currDirection == arus::Direction::right && getPosition().x > currTarget->position.x) nextTarget();
	//	//if(currDirection == arus::Direction::up && getPosition().y < currTarget->position.y) nextTarget();
	//	//if(currDirection == arus::Direction::left && getPosition().y > currTarget->position.y) nextTarget();
	//	//	}//tu bedzie rozwalanie klocka
	//
	//	calculateNextDir();
	//	this->ride(currDirection, rideSpeed*deltaTime);
	}
	//calculateNextDir();
	//setDirection(currDirection);
	//this->ride(currDirection, rideSpeed*deltaTime);

}

void Enemy::calculateNextDir() {
	if (currTarget != nullptr) {
		std::cout << "currentTarget: x:" << currTarget->x << " y:" << currTarget->y << std::endl;
		if (posX > currTarget->x &&  posY == currTarget->y) { //lewo
			std::cout << "teraz powinien jechac w lewo" << std::endl;
			currDirection = arus::Direction::left;
			//nextTarget();
		}
		if (posX < currTarget->x  &&  posY == currTarget->y) { //prawo
			std::cout << "teraz powinien jechac w prawo" << std::endl;
			currDirection = arus::Direction::right;
			//nextTarget();
		}
		if (posX == currTarget->x &&  posY > currTarget->y) { //gora
			std::cout << "teraz powinien jechac w gore" << std::endl;
			currDirection = arus::Direction::up;
			//nextTarget();
		}
		if (posX == currTarget->x &&  posY < currTarget->y) { //dol
			std::cout << "teraz powinien jechac w dol" << std::endl;
			currDirection = arus::Direction::down;
			//nextTarget();
		}
		//if(this->getPosition().x < currTarget->position.x) return arus::Direction::right; //jazda w prawo
		//if(this->getPosition().x > currTarget->position.x) return arus::Direction::left; //jazda w lewo
		//if(this->getPosition().y > currTarget->position.y) return arus::Direction::up; //jazda do gory
		//if(this->getPosition().y < currTarget->position.y) return arus::Direction::down; //jazda do gory
	}
}

void Enemy::nextTarget() {
	if (path.empty()) {
		pathTargetX = rand() % 13;  //tu beda losowania 
		pathTargetY = rand() % 13;
		astar(pathTargetX, pathTargetY);
	}
	else if (!path.empty()) { //jezeli sciezka nie jest pusta
		currTarget = path.back();
		path.pop_back();
		pathTargetX = currTarget->x;
		pathTargetY = currTarget->y;
		//currDirection = calculateNextDir();
	}
	else currTarget = nullptr;
}

//PATHFINDER
//indeksy pola do ktorych ma dotrzec
bool Enemy::astar(int xx, int yy) {
	path.clear();//wyczysczenie sciezki
	typedef std::list<MapElement*> NodeList;
	int tab[4][2] = { { -1,0 }, //left
	{ 1,0 }, //right
	{ 0,-1 }, //up
	{ 0,1 } }; //down

	MapElement *start = &poziom.getMapElement(posX, posY); //
	MapElement *end = &poziom.getMapElement(xx, yy);//
	end->setTexture(arus::Textures::cursor);

	MapElement *current = start; //
	MapElement *child = nullptr; //

	NodeList visited; //zbior wierzcholkow przejzanych - 2
	NodeList open; //lista wierzcholkow nieodwiedzonych
	std::list<MapElement*>::iterator i;

	start->inOpenList = true;
	open.push_back(start); //1

	unsigned int n = 0;
	sf::Vector2i curr(posX, posY);
	sf::Vector2i temp;

	while (!open.empty()) 
	{ 
		//current->computeScores(end);
		for (i = open.begin(); i != open.end(); ++i) { //2a
			//(*i)->computeScores(end);
			if (i == open.begin() || (*i)->getFScore() <= current->getFScore()) {
				current = (*i);
				curr = current->getIndex();
			}
		}
		open.remove(current);
		current->inOpenList = false;
		visited.push_back(current);
		current->inClosedList = true; 

		int x = 0;
		for (x; x < 4; ++x) {
			std::cout << "wtf!" << std::endl;
			temp = curr;
			temp.x += tab[x][0];
			temp.y += tab[x][1]; //ok

			if (temp.x<0 || temp.x> 12) continue;
			if (temp.y<0 || temp.y> 12) continue; //ok

			child = &poziom.getMapElement(temp.x, temp.y); //poprawnie przypisuje
			if (child != nullptr) {
				std::cout << "child is NOT null" << std::endl;
			}
			else
				std::cout << "child is null" << std::endl;

			if (child->inClosedList || int(child->getTextureID()) > 3) continue; //na poczatek omija wszystko
			if (this->getBulletType() != arus::bulletType::super && int(child->getTextureID()) == 2) continue; //jezeli trafi na stal
			if (this->getPowerUp() != arus::PowerUp::swim && int(child->getTextureID()) == 3) continue;

			if (child->inOpenList) { //jezeli jest w openlist 2c2
				if (child->getGScore() > child->getGScore(current)) { //2c3
					child->computeScores(end);
					child->setParent(current);
				}
			}
			else { //jezeli nie jest w openlist
				open.push_back(child);
				child->setParent(current);
				child->computeScores(end);
				child->inOpenList = true;
			}
		}

		if (child != nullptr && child->x == end->x && child->y == end->y) break;
	
	} //to dziala

	current = end;
	while (current->hasParent() && current != start) //odbudowanie 
	{
		path.push_back(current);
		current = current->getParent();
	}

	for (unsigned int i = 0; i < path.size(); i++) {
		if (poziom.mTiledMap[path[i]->getIndex().x][path[i]->getIndex().y].getTextureID() == arus::Textures::empty) {
			path[i]->mustDestroy = true;
		}
		poziom.mTiledMap[path[i]->getIndex().x][path[i]->getIndex().y].setTexture(arus::Textures::cursor);
		poziom.mTiledMap[path[i]->getIndex().x][path[i]->getIndex().y].setColliderWithTank(false);
		poziom.mTiledMap[path[i]->getIndex().x][path[i]->getIndex().y].setPosition(path[i]->getIndex().x * 54.f + 30.f, path[i]->getIndex().y * 48.f + 25.f);
	}

	std::cout << "Path Size: " << path.size() << std::endl;

	if (path.size() > 0) return true;
	else return false;
}

void Enemy::setPowerUp(PowerUp& p) {
	powerUpType = p.getType();
	powerUpTime = p.getTime();
}

arus::PowerUp Enemy::getPowerUp() {
	return this->powerUpType;
}

void Enemy::setPowerUp(arus::PowerUp p) {
	powerUpType = p;
}