#include<string>
/*
#include"../include/DataBase.h"
#include"../include/MyWindow.h"
#include"../include/Menu.h"
#include "../include/Task.h"
#include "../include/ThreadManager.h"

DataBase DATABASE;
*/
int main(){
    /*
    try {
		DATABASE.loadFont();
	}
	catch (const char* s) {
		system("cls");
		std::cout << s << std::endl;
		system("pause");
		return;
	}

	Task test = Task();
	test = [] {std::cout << "FROM LAMBDA" << std::endl; };
	MyThread t(test);

	ThreadManager manager;


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

		DATABASE.load();
		//DATABASE.load();

	}
	catch (const char * s) {
		system("cls");
		std::cout << s << std::endl;
		system("pause");
		return;
	}

	Menu menu(window);
	menu.start();
    */
	return 0;
}