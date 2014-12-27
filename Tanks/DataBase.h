#ifndef DATABASE_H
#define DATABASE_H
#pragma once

#include<SFML/Audio/Sound.hpp>
#include<iostream>
#include<fstream>
#include"arus.h"
#include"ResourceHolder.h"

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
};

class DataBase
{
public:
	void loadFont();
	void load();

	//zakonczenie poziomu
	void afterCompleteLvl();
	//zresetowanie opcji
	void resetToDefaultStats();

	//using to get texture (param: arus::Textures)
	sf::Texture& get(arus::Textures t);
	//using to get font (param: arus::Font)
	sf::Font& get(arus::Font f);
	//using to get std::string (param: int)
	std::string& get(unsigned int i);
	//using to get Configuration
	Stats& get();

private:
	void loadResources(); //ladowanie zasobow

	Stats stats;
	ResourceHolder<sf::Texture, arus::Textures>TextureHolder;
	ResourceHolder<sf::Font, arus::Font> FontHolder;

};

#endif
