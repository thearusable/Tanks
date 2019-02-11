#pragma once
#include<string>
#include"DataBase.h"
#include"MyWindow.h"
#include"Menu.h"
#include "Task.h"
#include "ThreadManager.h"

DataBase DATABASE;

void main(){
	
	DATABASE.load();

	MyWindow window(sf::VideoMode(864, 673, 32), "Tanks");
	try {
		window.setFramerateLimit(60);
		int a = sf::VideoMode::getDesktopMode().width;
		window.setPosition(sf::Vector2i(int((a - 864) / 2.f), 10));

		window.clear(sf::Color::Black);
		sf::Text loading;
		loading.setFillColor(sf::Color::White);
		loading.setCharacterSize(30);
		loading.setFont(DATABASE.get(arus::Font::DisposableDroid));
		loading.setString("Wczytywanie...");
		loading.setPosition(window.getSize().x / 2.f - loading.getLocalBounds().width / 2.f
			, window.getSize().y / 2.f - loading.getLocalBounds().height / 2.f);
		window.draw(loading);
		window.display();
	}
	catch (const char * s) {
		system("cls");
		std::cout << s << std::endl;
		system("pause");
		return;
	}

	Menu menu(window);
	menu.start();
}
