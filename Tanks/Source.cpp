#pragma once
#include<string>
#include"DataBase.h"
#include"MyWindow.h"
#include"Menu.h"

DataBase DATABASE;

#include "lua\lua.hpp"

//lua function test
int LUA_Test(lua_State *S)
{
	//odczytanie ze stosu
	float x = lua_tonumber(S, 1);
	//wrzucenie wyniku na stos
	lua_pushnumber(S,x*x*x);
	//ile obiektów zwróci
	return 1;
}

class Object {
public:
	int x = 10;
};

int LUA_CreateObject(lua_State *S) {
	//wrzucenie wskaznika na stos
	lua_pushlightuserdata(S, new Object());
	return 1;
}

int LUA_DestroyObject(lua_State *S) {
	//odczytanie ze stosu
	Object * p = (Object *)lua_touserdata(S, 1);
	if (p) {
		delete p;
	}
	return 0;
}

int LUA_GetObjectData(lua_State *S) {
	Object * p = (Object *)lua_touserdata(S, 1);
	if (p) {
		lua_pushnumber(S, p->x);
	}
	return 1;
}


void main(){


	//lua test
	lua_State *S = luaL_newstate();
	luaL_openlibs(S);
	//registers
	lua_register(S, "doTrzeciej", LUA_Test);
	lua_register(S, "CreateObject", LUA_CreateObject);
	lua_register(S, "DestroyObject", LUA_DestroyObject);
	lua_register(S, "GetObjectData", LUA_GetObjectData);

	luaL_loadfile(S, "test.lua");
	lua_call(S, 0, 0);

	try{
		DATABASE.loadFont();
	}
	catch (const char* s){
		system("cls");
		std::cout << s << std::endl;
		system("pause");
		return;
	}

	MyWindow window(sf::VideoMode(864, 673, 32), "Tanks");
	try{
		window.setFramerateLimit(60);
		int a = sf::VideoMode::getDesktopMode().width;
		window.setPosition(sf::Vector2i(int((a - 864) / 2.f), 10));

		window.clear(sf::Color::Black);
		sf::Text loading;
		loading.setColor(sf::Color::White);
		loading.setCharacterSize(30);
		loading.setFont(DATABASE.get(arus::Font::DisposableDroid));
		loading.setString("Wczytywanie...");
		loading.setPosition(window.getSize().x /2.f - loading.getLocalBounds().width /2.f
							, window.getSize().y /2.f - loading.getLocalBounds().height /2.f);
		window.draw(loading);
		window.display();

		DATABASE.load();

	}
	catch (const char * s){
		system("cls");
		std::cout << s << std::endl;
		system("pause");
		return;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Menu menu(window);
	menu.start();

}
