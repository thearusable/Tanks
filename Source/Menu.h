#ifndef MENU_H
#define MENU_H
#pragma once
#include"MyWindow.h"
#include"RenderElement.h"
#include"AnimateElement.h"
#include"Construction.h"
#include"Game.h"
class Menu
{
public:
	Menu(MyWindow& window); //glowny kontruktor

	void start(); //rozpoczyna glowna petle menu

private:
	void choose();
	void events(); //obsluga zdarzen
	void update(); //aktualizuje polozenie elementow
	void render(); //odpowiada za rysowanie w oknie

	MyWindow& target;
	sf::Text text[4];
	RenderElement logo;
	AnimateElement tank;
	int currenltyChoosed;
};

#endif