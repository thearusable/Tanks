#include "Level.h"

extern DataBase DATABASE;

Level::Level(void) :elementy(), mEdge(), background(){
	//pozycja mapy
	mapPosition.x = 30;
	mapPosition.y = 25;
	//

	background.setFillColor(sf::Color::Black);
	background.setSize(sf::Vector2f(13 * 54.f, 13 * 48.f));
	background.setPosition(mapPosition);

	for (int i = 0; i<4; i++){
		mEdge[i].setSize(sf::Vector2f(15 * 54.f, 50.f));
		mEdge[i].setTexture(arus::Textures::brick);
	}
	mEdge[0].setPosition(0.f, mapPosition.y - mEdge[0].getLocalBounds().height); //top - ready
	mEdge[1].setPosition(0.f, mapPosition.y + 13 * 48.f); //bot - ready
	mEdge[2].setRotation(90.f);
	mEdge[2].setPosition(mapPosition.x - 50.f, mapPosition.y); //left - ready
	mEdge[3].setRotation(90.f);
	mEdge[3].setPosition(mapPosition.x + 13 * 54.f, mapPosition.y); //right


	elementy[0] = RenderElement();
	elementy[1].setTextureAndRect(arus::Textures::brick, sf::IntRect(0, 0, 54, 48));
	elementy[2].setTextureAndRect(arus::Textures::brick, sf::IntRect(0, 0, 27, 48));
	elementy[3].setTextureAndRect(arus::Textures::brick, sf::IntRect(27, 0, 27, 48));
	elementy[4].setTextureAndRect(arus::Textures::brick, sf::IntRect(0, 0, 54, 24));
	elementy[5].setTextureAndRect(arus::Textures::brick, sf::IntRect(0, 24, 54, 24));
	//steel
	elementy[6].setTextureAndRect(arus::Textures::steel, sf::IntRect(0, 0, 54, 48));
	elementy[7].setTextureAndRect(arus::Textures::steel, sf::IntRect(0, 0, 27, 48));
	elementy[8].setTextureAndRect(arus::Textures::steel, sf::IntRect(27, 0, 27, 48));
	elementy[9].setTextureAndRect(arus::Textures::steel, sf::IntRect(0, 0, 54, 24));
	elementy[10].setTextureAndRect(arus::Textures::steel, sf::IntRect(0, 24, 54, 24));
	//reszta
	elementy[11].setTexture(arus::Textures::water); //water
	elementy[12].setTexture(arus::Textures::ice); //ice
	elementy[13].setTexture(arus::Textures::grass); //grass
	elementy[14].setTexture(arus::Textures::eagle); //eagle

	this->clearMap();

}


void Level::operator>(MyWindow& target){ //wszystko poza zielenia
	target.draw(background);
	for (unsigned int i = 0; i < 13; i++)
		for (unsigned int j = 0; j < 13; j++){
			arus::Textures t = mTiledMap[i][j].getTextureID();
			if (t != arus::Textures::empty && t != arus::Textures::grass)
				mTiledMap[i][j] >> target;
		}
}

void Level::operator>>(MyWindow& target){// rysowanie zieleni
	for (unsigned int i = 0; i < 13; i++)
		for (unsigned int j = 0; j < 13; j++)
			if (mTiledMap[i][j].getTextureID() == arus::Textures::grass)
				mTiledMap[i][j] >> target;

}

void Level::destroyElementOfMap(unsigned int x, unsigned int y){
	mTiledMap[x][y] = elementy[0];
}

void Level::clearMap(){
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 13; j++){
			mTiledMap[i][j] = elementy[0];
			mTiledMap[i][j].setPosition(i * 54.f + 30.f, j * 48.f + 25.f);
		}
}

void Level::loadMap(unsigned int x){
	this->clearMap();

	std::fstream file;
	

	unsigned int xx = x;
	while (true){
		try{
			std::string sciezka = "Data/Levels/" + std::to_string(xx) + ".txt";
			
			file.open(sciezka, std::ios::in);
			if (!file.good()){
				throw "!!!";
			}
			break;
		}
		catch (const char *){
			xx = 1;
			DATABASE.getStats().currLevel = 1;
		}
	}

	int a = 0, b = 0, tempX, tempY, posX, posY, id;
	while (file.good()){

		if (file >> tempY){

			file >> tempX >> id >> posX >> posY;

			mTiledMap[tempX][tempY] = elementy[id];

			mTiledMap[tempX][tempY].setPosition(float(posX), float(posY));

			if (id == 13 || id == 12) mTiledMap[tempX][tempY].setColliderWithTank(false);
			else mTiledMap[tempX][tempY].setColliderWithTank(true);
			if (id == 13 || id == 12 || id == 11) mTiledMap[tempX][tempY].setColliderWithBullet(false);
			else mTiledMap[tempX][tempY].setColliderWithBullet(true);

		}
	}

	file.close();
}

MapElement& Level::getMapElement(int x, int y){
	return mTiledMap[x][y];
}