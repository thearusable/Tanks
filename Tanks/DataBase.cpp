#include "DataBase.h"


void DataBase::loadFont(){
	//wczytywanie czcionek
	if (!FontHolder.load(arus::Font::DisposableDroid, "Data/Fonts/DisposableDroidBB_bld.otf"))
		throw "Wystapil blad podczas wczytywania czcionek.";
}

void DataBase::load(){
	resetToDefaultStats();
	loadResources();
}

/*
-> Przywrocenie Bazy do domyslnych wartosci
*/
void DataBase::resetToDefaultStats(){
	//Player1
	stats.p1LIVES = 3;
	stats.p1POINTS = 0;
	//Player2
	stats.p2LIVES = 3;
	stats.p2POINTS = 0;
	//inne
	stats.displayedLevel = 1; //ilosc map
	stats.currLevel = 1;//indeks obecnej mapy
	stats.enemyCount = 23;//ilosc wszystkich przeciwnikow
	stats.isCustomMap = false; //czy byla tworzona mapa
	//liczba zabitych wrogow
	stats.e1p1 = stats.e1p2 = stats.e2p1 = stats.e2p2 = stats.e3p1 = stats.e3p2 = stats.e4p1 = stats.e4p2 = 0; 

}

void DataBase::afterCompleteLvl(){
	stats.currLevel++;
	stats.displayedLevel++;
	stats.e1p1 = stats.e1p2 = stats.e2p1 = stats.e2p2 = stats.e3p1 = stats.e3p2 = stats.e4p1 = stats.e4p2 = 0;
}

void DataBase::loadResources(){
	//wczytywanie tekstur
	if (TextureHolder.load(arus::Textures::brick, "Data/Textures/brick.jpg") &&
		TextureHolder.load(arus::Textures::logo, "Data/Textures/logo.png") &&
		TextureHolder.load(arus::Textures::ice, "Data/Textures/ice.jpg") &&
		TextureHolder.load(arus::Textures::bullet, "Data/Textures/bullet.png") &&
		TextureHolder.load(arus::Textures::sBullet, "Data/Textures/bulletS.png") &&
		TextureHolder.load(arus::Textures::cursor, "Data/Textures/cursor.png") &&
		TextureHolder.load(arus::Textures::eagle, "Data/Textures/eagle.jpg") &&
		TextureHolder.load(arus::Textures::grass, "Data/Textures/grass.png") &&
		TextureHolder.load(arus::Textures::player11, "Data/Textures/player-1-1.png") &&
		TextureHolder.load(arus::Textures::player21, "Data/Textures/player-2-1.png") &&
		TextureHolder.load(arus::Textures::player12, "Data/Textures/player-1-2.png") &&
		TextureHolder.load(arus::Textures::player22, "Data/Textures/player-2-2.png") &&
		TextureHolder.load(arus::Textures::enemyFast, "Data/Textures/enemy_fast.png") &&
		TextureHolder.load(arus::Textures::enemyHeavy, "Data/Textures/enemy_heavy.png") &&
		TextureHolder.load(arus::Textures::enemyNormal, "Data/Textures/enemy_normal.png") &&
		TextureHolder.load(arus::Textures::enemyRandom, "Data/Textures/enemy_random.png") &&
		TextureHolder.load(arus::Textures::tankDestroy, "Data/Textures/tank_destroy.png") &&
		TextureHolder.load(arus::Textures::spawn, "Data/Textures/spawn.png") &&
		TextureHolder.load(arus::Textures::steel, "Data/Textures/steel.jpg") &&
		TextureHolder.load(arus::Textures::tankMenu, "Data/Textures/tank_menu.png") &&
		TextureHolder.load(arus::Textures::flag, "Data/Textures/flaga.png") &&
		TextureHolder.load(arus::Textures::tankIcon, "Data/Textures/tank_icon.png") &&
		TextureHolder.load(arus::Textures::water, "Data/Textures/water.png") &&
		TextureHolder.load(arus::Textures::arrows, "Data/Textures/arrows.jpg") &&
		TextureHolder.load(arus::Textures::PTS, "Data/Textures/PTS.jpg") &&
		TextureHolder.load(arus::Textures::tanks, "Data/Textures/tanks_loadscreen.jpg") &&
		TextureHolder.load(arus::Textures::granadePU, "Data/Textures/granade.png") &&
		TextureHolder.load(arus::Textures::lifePU, "Data/Textures/life.png") &&
		TextureHolder.load(arus::Textures::pistolPU, "Data/Textures/pistol.png") &&
		TextureHolder.load(arus::Textures::shieldPU, "Data/Textures/shield.png") &&
		TextureHolder.load(arus::Textures::speedPU, "Data/Textures/speed.png") &&
		TextureHolder.load(arus::Textures::swimPU, "Data/Textures/swim.png") &&
		TextureHolder.load(arus::Textures::swim, "Data/Textures/additionalSwim.png") &&
		TextureHolder.load(arus::Textures::bulletDestroy, "Data/Textures/bullet_destroy.png") &&
		TextureHolder.load(arus::Textures::shield, "Data/Textures/additionalShield.png")
		){
	}
	else {
		throw "Wystapil blad podczas wczytywania tekstur";
	}
	std::cout << "Wczytywanie zakonczono sukcesem." << std::endl;
}

sf::Texture& DataBase::get(arus::Textures t){
	return TextureHolder.get(t);
}

sf::Font& DataBase::get(arus::Font f){
	return FontHolder.get(f);
}

Stats& DataBase::get(){
	return stats;
}


