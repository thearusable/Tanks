#include "MyWindow.h"

extern DataBase DATABASE;

MyWindow::MyWindow() :RenderWindow(), showFPS(true)
{
	this->initialize();
}

MyWindow::MyWindow(VideoMode Mode, const std::string &Title) 
	: RenderWindow(Mode, Title)
	, showFPS(true)
{
	this->initialize();
}

MyWindow::~MyWindow(){}

BOOL MyWindow::initialize(){
	FPS.setCharacterSize(30);
	FPS.setColor(sf::Color::Yellow);
	FPS.setFont(DATABASE.get(arus::Font::DisposableDroid));
	FPS.setPosition(10,5);

	BOOL b = QueryPerformanceFrequency(&timeFrequency);
	if (!b)
		return false;
	return QueryPerformanceCounter(&timeLastFrame);
}

void MyWindow::newFrame(){
	LARGE_INTEGER thisTime, delta;
	QueryPerformanceCounter(&thisTime);
	delta.QuadPart = thisTime.QuadPart - timeLastFrame.QuadPart;
	deltaTime = float(delta.QuadPart) / timeFrequency.QuadPart;
	timeLastFrame.QuadPart = thisTime.QuadPart;
}

void MyWindow::display(){
	if (showFPS){
		FPS.setString(std::to_string(int(1.f / deltaTime)));
		this->draw(FPS);
	}
	RenderWindow::display();
	this->newFrame();
}

void MyWindow::setDisplayFPS(bool b){
	showFPS = b;
}

float MyWindow::timeElapsedLastFrame(){
	return deltaTime;
}