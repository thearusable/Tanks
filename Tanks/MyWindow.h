#ifndef MYWINDOW_H
#define MYWINDOW_H
#pragma once
#include<SFML/Graphics.hpp>
#include <Windows.h>
#include"DataBase.h"

using namespace sf;

class MyWindow : public sf::RenderWindow
{
public:
	MyWindow();
	MyWindow(VideoMode Mode, const std::string &Title);

	virtual ~MyWindow();

	void newFrame();
	void display();
	void setDisplayFPS(bool b);
	float timeElapsedLastFrame();
protected:
	BOOL initialize();

	Text FPS;
	LARGE_INTEGER timeFrequency;
	LARGE_INTEGER timeLastFrame;
	LARGE_INTEGER deltaLastFrame;
	float deltaTime, timeFromLastFPSShow;
	bool showFPS;
};

#endif