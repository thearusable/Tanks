#ifndef GUI_H
#define GUI_H

#pragma once
#include"MyWindow.h"
#include"RenderElement.h"
class GUI
{
public:
	GUI(MyWindow& tar);

	void update(const bool& isTwoPlayers, const bool& mapCompleted, const bool& isSummary);
	void render(const bool& isTwoPlayers, const bool& mapCompleted, const bool& isSummary);

protected:
	RenderElement player1elements[3];
	RenderElement player2elements[2];
	RenderElement tank_icon[3], flaga;
	sf::RectangleShape underline;
	sf::Text Teksty[7];
	sf::Text player1[14];
	sf::Text player2[12];
	sf::Text hScore[2];

	MyWindow& target;
};

#endif