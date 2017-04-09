#include "Construction.h"

extern DataBase DATABASE;

Construction::Construction(MyWindow& window)
	:target(window)
	, stats(DATABASE.getStats())
	, cursorVector(0, 0, 1)
	, cursor(arus::Textures::cursor)
	, kafelki()
	, elementy()
	, backShape()
	, stillBuildingMap(true)
	, itSaved(false)
	, nextElement()
{
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 13; j++)
			kafelkiID[i][j] = 0;

	next.setFont(DATABASE.get(arus::Font::DisposableDroid));
	next.setString("Next");
	next.setPosition(770, 450);
	next.setCharacterSize(30);
	next.setFillColor(sf::Color::Black);

	mapPos.x = 30;
	mapPos.y = 25;
	backShape.setSize(sf::Vector2f(13 * 54, 13 * 48));
	backShape.setFillColor(sf::Color::Black);
	backShape.setPosition(mapPos.x, mapPos.y);
	backShape.setScale(1, 1);

	backShapeNext.setSize(sf::Vector2f(54, 48));
	backShapeNext.setFillColor(sf::Color::Black);
	backShapeNext.setPosition(mapPos.x, mapPos.y);
	backShapeNext.setScale(1, 1);
	backShapeNext.setPosition(770, 500);

	cursor.setPosition(mapPos.x + 27, mapPos.y + 24);
	underCursor = elementy[0];

	//mapTexture.loadFromFile("/Data/Textures/MapTextures.jpg");
	//brick
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
	elementy[14].setTexture(arus::Textures::eagle); //orzel

	mapPos.x += 27;
	mapPos.y += 24;
}

bool Construction::start() {
	while (target.isOpen() && stillBuildingMap) {
		events();
		update();
		render();
	}
	return itSaved;
}

void Construction::events() {
	sf::Event e;
	while (target.pollEvent(e)) {
		switch (e.type) {
		case sf::Event::KeyPressed:
			if (e.key.code == sf::Keyboard::Up) {
				kafelki[cursorVector.x][cursorVector.y].setVisible(true);
				cursorVector.y -= 1;
				if (cursorVector.y < 0) cursorVector.y = 12;
				kafelki[cursorVector.x][cursorVector.y].setVisible(false);
			}
			else if (e.key.code == sf::Keyboard::Down) {
				kafelki[cursorVector.x][cursorVector.y].setVisible(true);
				cursorVector.y += 1;
				if (cursorVector.y > 12) cursorVector.y = 0;
				kafelki[cursorVector.x][cursorVector.y].setVisible(false);
			}
			else if (e.key.code == sf::Keyboard::Left) {
				kafelki[cursorVector.x][cursorVector.y].setVisible(true);
				cursorVector.x -= 1;
				if (cursorVector.x < 0) cursorVector.x = 12;
				kafelki[cursorVector.x][cursorVector.y].setVisible(false);
			}
			else if (e.key.code == sf::Keyboard::Right) {
				kafelki[cursorVector.x][cursorVector.y].setVisible(true);
				cursorVector.x += 1;
				if (cursorVector.x > 12) cursorVector.x = 0;
				kafelki[cursorVector.x][cursorVector.y].setVisible(false);
			}
			if (e.key.code == sf::Keyboard::Return) {
				saveMap();
				stillBuildingMap = false;
			}
			else if (e.key.code == sf::Keyboard::LAlt) {
				cursorVector.z++;
				if (cursorVector.z > 13) cursorVector.z = 0;
				kafelki[cursorVector.x][cursorVector.y].setVisible(false);
			}
			else if (e.key.code == sf::Keyboard::Escape) {
				stillBuildingMap = false;
			}
			else if (e.key.code == sf::Keyboard::Space) {
				kafelki[cursorVector.x][cursorVector.y] = elementy[cursorVector.z];
				kafelki[cursorVector.x][cursorVector.y].setPosition(cursor.getPosition().x, cursor.getPosition().y);
				if (cursorVector.z == 3 || cursorVector.z == 8) kafelki[cursorVector.x][cursorVector.y].move(27, 0);
				if (cursorVector.z == 5 || cursorVector.z == 10) kafelki[cursorVector.x][cursorVector.y].move(0, 24);
				kafelkiID[cursorVector.x][cursorVector.y] = cursorVector.z;
			}
			break;
		}
		if (e.type == sf::Event::Closed) target.close();
	}
}

void Construction::update() {
	cursor.setPosition(mapPos.x + cursorVector.x * 54.f, mapPos.y + cursorVector.y * 48.f);
	underCursor = elementy[cursorVector.z];
	underCursor.setPosition(cursor.getPosition().x, cursor.getPosition().y);
	if (cursorVector.z == 3 || cursorVector.z == 8) underCursor.move(27, 0);
	if (cursorVector.z == 5 || cursorVector.z == 10) underCursor.move(0, 24);

	int a = cursorVector.z;
	if (a + 1 > 13) a = 0;
	else a++;
	nextElement = elementy[a];
	nextElement.setPosition(770, 500);
	if (a == 3 || a == 8) nextElement.move(27, 0);
	if (a == 5 || a == 10) nextElement.move(0, 24);
	nextElement.setOrigin(0.f, 0.f);
}

void Construction::render() {
	target.clear(sf::Color(125, 125, 125, 255));
	target.draw(backShape);
	target.draw(backShapeNext);
	target.draw(next);

	for (int a = 0; a < 13; a++)
		for (int b = 0; b < 13; b++)
			kafelki[a][b] >> target;

	underCursor >> target;
	cursor >> target;
	nextElement >> target;
	target.display();
}

void Construction::saveMap() {
	kafelki[6][12] = elementy[14];
	kafelki[6][12].setPosition(mapPos.x + 6 * 54.f, mapPos.y + 12 * 48.f);
	kafelkiID[0][0] = kafelkiID[6][0] = kafelkiID[12][0] = kafelkiID[4][12] = kafelkiID[8][12] = 0;
	kafelkiID[6][12] = 14;
	std::fstream file;

	stats.isCustomMap = true;
	stats.currLevel = 0;
	try {
		file.open("Data/Levels/0.txt", std::ios::out); //usuniecie zawartosci

		if (!file.good()) {
			throw "THROW - Nie udalo sie otworzyc pliku - 0.txt";
		}

		int tempX = 0, tempY = 0;
		while (file.good()) {
			if (kafelkiID[tempX][tempY] > 0) {
				file << tempX << " ";
				file << tempY << " ";
				file << kafelkiID[tempX][tempY] << " ";
				file << kafelki[tempX][tempY].getPosition().x - 27 << " ";
				file << kafelki[tempX][tempY].getPosition().y - 24 << std::endl;
			}

			tempX++;
			if (tempX > 12) {
				tempX = 0;
				tempY++;
			}
			if (tempY > 12) {
				break;
			}
		}
		file.close();
	}
	catch (const char *) {
		stats.isCustomMap = false;
		stats.currLevel = 1;
	}
	itSaved = true;
	return;
}