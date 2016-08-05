#include "Enemy.h"

typedef std::list<Node*> NodeList;

Enemy::Enemy(Level& l, int xx, int yy, int spawn)
	: level(l)
{
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
	currDirection = arus::Direction::down;
	this->updateTexture();
	this->setScale(0.9f, 0.9f);
	canMove = true;

	//to logic 
	path.clear();
	
	for (int x = 0; x < 13; x++) {
		for (int y = 0; y < 13; y++) {
			map[x][y] = Node(level.getMapElement(x, y), x, y);
		}
	}

	calcRandomCoord();
	astar();
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

void Enemy::update(float deltaTime) {
	//obliczenie wspolrzednych x i y w tablicy
	posX = int((this->getPosition().x - 30.f) / 54.f);
	posY = int((this->getPosition().y - 25.f) / 48.f);


	if (path.empty()) { 
		calcRandomCoord();
		astar();
	}

	followPath(deltaTime);

	if (path.empty() == false && path.back()->mustDestroy == true) {
		tryShoot();
	}

	//if (currTarget != nullptr) {
		
	//	std::cout << "posX: " << posX << " posY: " << posY << std::endl;
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
	//}
	//calculateNextDir();
	//setDirection(currDirection);
	//this->ride(currDirection, rideSpeed*deltaTime);

}

void Enemy::followPath(float deltaTime) {
	if (path.empty()) {
		return;
	}

	std::cout << "mapElement position: x: " << level.getMapElement(path.back()->x, path.back()->y).getPosition().x
		<< " y: " << level.getMapElement(path.back()->x, path.back()->y).getPosition().y
		<< " enemy position x: " << getPosition().x << " y: " << getPosition().y << std::endl;
	auto temp = level.getMapElement(path.back()->x, path.back()->y).getPosition() - getPosition();
	std::cout << "difrence: x: " << temp.x << " y:" << temp.y << std::endl;

	if (abs(temp.y) > 2.f && temp.y > -2) {
		//jedz w dol
		ride(arus::Direction::down, rideSpeed * deltaTime);
	}
	else if (abs(temp.y) > 2.f && temp.y < 2) {
		//jedz w gore
		ride(arus::Direction::up, rideSpeed * deltaTime);
	}
	else if (abs(temp.x) > 2.f && temp.x > -2) {
		//jedz w prawo
		ride(arus::Direction::right, rideSpeed * deltaTime);
	}
	else if (abs(temp.x) > 2.f && temp.x < 2) {
		//jedz w lewo
		ride(arus::Direction::left, rideSpeed * deltaTime);
	}

	if (abs(temp.y) < 2.f && abs(temp.x) < 2.f) {
		path.back() = nullptr;
		path.pop_back();
	}

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
		astar();
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


void Enemy::calcRandomCoord()
{
	bool good = false;
	int x = 0, y = 0;

	while (good == false) {
		srand(unsigned(time(NULL)));
		x = rand() % 13;
		y = rand() % 13;

		auto tex = map[x][y].TextureType;

		if (tex == arus::Textures::water ||
			(tex == arus::Textures::steel && getBulletType() == arus::bulletType::normal) ||
			(x == posX && y == posY)) {
			good = false;
		}
		else {
			good = true;
		}
	}

	pathTargetX = x;
	pathTargetY = y;
}

//PATHFINDER
//indeksy pola do ktorych ma dotrzec
void Enemy::astar() {

	path.clear();
	
	int tab[4][2] = {	{ -1,0 }, //left
						{ 1,0 }, //right
						{ 0,-1 }, //up
						{ 0,1 } }; //down

	Node *start = &map[posX][posY]; 
	Node *end = &map[pathTargetX][pathTargetY];//
	std::cout << "Target: x: " << pathTargetX << " y: " << pathTargetY << std::endl;

	Node *current = start; //
	Node *child = nullptr; //

	NodeList visited; 
	NodeList open; 
	std::list<Node*>::iterator i;

	start->inOpenList = true;
	open.push_back(start); //1

	sf::Vector2i curr(posX, posY);
	sf::Vector2i temp;

	while (!open.empty()) 
	{ 
		current->computeScores(end);
		for (i = open.begin(); i != open.end(); ++i) { //2a
			(*i)->computeScores(end);
			if (i == open.begin() || (*i)->f <= current->f) {
				current = (*i);
				curr = current->getIndex();
			}
		}
		open.remove(current);
		current->inOpenList = false;
		visited.push_back(current);
		current->inClosedList = true; 

		//if current == target the brak
		if (current == end) break;

		for (int x = 0; x < 4; ++x) {
			//sasiad niedostepny lub jak jest w closed to pomin
			temp = curr;
			temp.x += tab[x][0];
			temp.y += tab[x][1]; //ok

			//pominiecie obszaru poza mapa
			if (temp.x<0 || temp.x> 12) continue;
			if (temp.y<0 || temp.y> 12) continue; 
			//pominiecie klockow po ktorych nie moze jechac i ich rozwalic
			if (map[temp.x][temp.y].TextureType == arus::Textures::water && powerUpType != arus::PowerUp::swim) continue;
			if (map[temp.x][temp.y].TextureType == arus::Textures::steel && bulletType != arus::bulletType::super) continue;
			if (map[temp.x][temp.y].inClosedList == true) continue;

			child = &map[temp.x][temp.y]; //poprawnie przypisuje

			if (child->inOpenList) { //jezeli jest w openlist 2c2
				if (child->g > child->getGScore(current)) { //2c3
					child->computeScores(end);
					child->parent = current;
				}
			}
			else { //jezeli nie jest w openlist
				open.push_back(child);
				child->parent = current;
				child->computeScores(end);
				child->inOpenList = true;
			}
		}
		if (child != nullptr && child->x == end->x && child->y == end->y) break;
	
	} //to dziala

	if (path.size() == 0) {
		//find closest reachable point to end
		Node* closest = start;
		for (auto x : visited) {
			if (x->h < closest->h) {
				closest = x;
			}
		}
		end = closest;
		pathTargetX = end->x;
		pathTargetY = end->y;

		std::cout << "Destination is not reachable, closest:  x: " << closest->x << " y: " << closest->y << std::endl;
	}

	current = end;
	while (current->hasParent() && current != start) //odbudowanie 
	{
		path.push_back(current);
		current = current->parent;
	}

	for (unsigned int i = 0; i < path.size(); i++) {
		auto tex = map[path[i]->getIndex().x][path[i]->getIndex().y].TextureType;
		if (tex == arus::Textures::brick ||
			(tex == arus::Textures::steel && getBulletType() == arus::bulletType::super )) {
			path[i]->mustDestroy = true;
		}
		else {
			path[i]->mustDestroy = false;
		}
	}

	std::cout << "Path Size: " << path.size() << std::endl;

	//for (auto a : path) {
	//	std::cout << "path x: " << a->x << " y: " << a->y <<" MustD: "<< a->mustDestroy << std::endl;
	//}

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