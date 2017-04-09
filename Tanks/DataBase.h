#ifndef DATABASE_H
#define DATABASE_H
#pragma once

#include<SFML/Audio/Sound.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Font.hpp>
#include<iostream>
#include<fstream>

#include<thread>
#include<mutex>
#include <windows.h>

#include"arus.h"
#include"ResourceHolder.h"
#include"MyThread.h"

struct Stats
{
	//Player1
	unsigned short p1LIVES;
	unsigned int p1POINTS;
	//Player2
	unsigned short p2LIVES;
	unsigned int p2POINTS;
	//inne
	unsigned short displayedLevel; //indeks wyswietlany
	unsigned short currLevel; //indeks obecnej mapy
	unsigned short enemyCount;//ilosc wszystkich przeciwnikow
	bool isCustomMap; //czy byla tworzona mapa

	unsigned short e1p1, e2p1, e3p1, e4p1, e1p2, e2p2, e3p2, e4p2; //liczba zabitych wrogow

	//zakonczenie poziomu
	void afterCompleteLvl() {
		currLevel++;
		displayedLevel++;
		enemyCount = 20;
		e1p1 = e1p2 = e2p1 = e2p2 = e3p1 = e3p2 = e4p1 = e4p2 = 0;
	}
	//zresetowanie opcji
	void resetToDefaultStats() {
		//Player1
		p1LIVES = 3;
		p1POINTS = 0;
		//Player2
		p2LIVES = 3;
		p2POINTS = 0;
		//inne
		displayedLevel = 1;		//ilosc map
		currLevel = 1;			//indeks obecnej mapy
		enemyCount = 20;		//ilosc wszystkich przeciwnikow
		isCustomMap = false;	//czy byla tworzona mapa

		e1p1 = e1p2 = e2p1 = e2p2 = e3p1 = e3p2 = e4p1 = e4p2 = 0;	//liczba zabitych wrogow
	}
};

class DataBase
{
public:

	~DataBase();
	//void loadFont();
	void load();

	//using to get texture (param: arus::Textures)
	sf::Texture& get(arus::Textures t);
	//using to get font (param: arus::Font)
	sf::Font& get(arus::Font f);
	//using to get Configuration
	Stats& getStats();

	

	bool isFullyLoaded();
	void interrupt();

private:
	void loadMenuItems(); 
	void loadResources(); //ladowanie zasobow

	std::mutex mu;
	//std::thread* thread;
	MyThread* myThread;

	bool allLoaded = false;
	Stats stats;
	ResourceHolder<sf::Texture, arus::Textures>TextureHolder;
	ResourceHolder<sf::Font, arus::Font> FontHolder;
};

#endif
