#include "GUI.h"

#include"DataBase.h"

extern DataBase DATABASE;
Stats& stats = DATABASE.get();

GUI::GUI(MyWindow& tar)
	:target(tar)
	, flaga()
	, tank_icon()
	, player1()
	, player2()
	, hScore()
	, player1elements()
	, player2elements()
	, underline()
{
	for (sf::Text& t : Teksty){
		t.setFont(DATABASE.get(arus::Font::DisposableDroid));
		t.setCharacterSize(40);
		t.setColor(sf::Color::Black);
	}

	for (RenderElement& r : tank_icon) {
		r.setTexture(arus::Textures::tankIcon);
		r.setScale(1.5f, 1.5f);
	}
	flaga.setTexture(arus::Textures::flag);
	flaga.setScale(1.5f, 1.5f);

	std::string tex[3] = { "Enemy:", "IP:", "IIP:" };
	//string s = std::to_string(123);
	float x = tank_icon[0].getLocalBounds().height;
	//info z prawej
	Teksty[0].setString(tex[0]); //Enemy
	Teksty[0].setPosition(750, 100);
	tank_icon[0].setPosition(750, 140 + x);
	Teksty[1].setString(std::to_string(DATABASE.get().enemyCount)); //ilosc przeciwnikow
	Teksty[1].setPosition(780, 135);
	Teksty[2].setString(tex[1]); //1 gracz
	Teksty[2].setPosition(750, 300);
	tank_icon[1].setPosition(750, 340 + x);
	Teksty[3].setString(std::to_string(DATABASE.get().p1LIVES)); //zycia 1 gracza
	Teksty[3].setPosition(780, 335);
	flaga.setPosition(750, 585);
	Teksty[4].setString(std::to_string(DATABASE.get().displayedLevel)); //numer rundy
	Teksty[4].setPosition(780, 600);
	Teksty[5].setString(tex[2]); //2 gracz
	Teksty[5].setPosition(750, 380);
	tank_icon[2].setPosition(750, 420 + x);
	Teksty[6].setString(std::to_string(DATABASE.get().p2LIVES)); //zycia 2 gracza
	Teksty[6].setPosition(780, 415);

	for (sf::Text& t : player1){
		t.setColor(sf::Color::White);
		t.setFont(DATABASE.get(arus::Font::DisposableDroid));
		t.setCharacterSize(35);
	}
	for (sf::Text& t : player2){
		t.setColor(sf::Color::White);
		t.setFont(DATABASE.get(arus::Font::DisposableDroid));
		t.setCharacterSize(35);
	}

	//p1
	player1elements[0].setTexture(arus::Textures::tanks);
	player1elements[0].setScale(1.2f, 1.2f);
	player1elements[0].setPosition(400.f, 250.f);//

	player1elements[1].setTexture(arus::Textures::arrows);
	player1elements[1].setScale(1.2f, 1.2f);
	player1elements[1].setPosition(370.f, 260.f); //

	player1elements[2].setTexture(arus::Textures::PTS);
	player1elements[2].setScale(1.2f, 1.2f);
	player1elements[2].setPosition(240.f, 260.f);//

	underline.setFillColor(sf::Color::White);
	underline.setSize(sf::Vector2f(180.f, 6.f));
	underline.setPosition(330.f, 475.f); //

	//p2
	player2elements[0].setTexture(arus::Textures::arrows);
	player2elements[0].setScale(1.2f, 1.2f);
	player2elements[0].rotate(180.f);
	player2elements[0].setPosition(470.f, 450.f); //

	player2elements[1].setTexture(arus::Textures::PTS);
	player2elements[1].setScale(1.2f, 1.2f);
	player2elements[1].setPosition(540.f, 260.f);

	//ustawienie ekranu wynikow
	player1[0].setPosition(150.f, 120.f); ////
	player1[1].setCharacterSize(45); ////
	player1[1].setPosition(350.f, 65.f); ////
	player1[2].setPosition(170.f, 170.f); ////
	player1[3].setPosition(150.f, 242.f); ////
	player1[4].setPosition(335.f, 242.f); ////
	player1[5].setPosition(150.f, 300.f); ////
	player1[6].setPosition(335.f, 300.f); ////
	player1[7].setPosition(150.f, 358.f); ////
	player1[8].setPosition(335.f, 358.f); ////
	player1[9].setPosition(150.f, 416.f); ////
	player1[10].setPosition(335.f, 416.f); ////
	player1[11].setPosition(230.f, 490.f); ////
	player1[12].setPosition(335.f, 490.f); ////
	player1[13].setPosition(260.f, 570.f); ////

	//p2
	player2[0].setPosition(560.f, 120.f);
	player2[1].setPosition(580.f, 170.f);
	player2[2].setPosition(490.f, 242.f); ////
	player2[3].setPosition(630.f, 242.f);
	player2[4].setPosition(490.f, 300.f);
	player2[5].setPosition(630.f, 300.f);
	player2[6].setPosition(490.f, 358.f);
	player2[7].setPosition(630.f, 358.f);
	player2[8].setPosition(490.f, 416.f);
	player2[9].setPosition(630.f, 416.f); ////
	player2[10].setPosition(400.f, 490.f);
	player2[11].setPosition(490.f, 490.f); //


	for (sf::Text& t : hScore){
		t.setColor(sf::Color::White);
		t.setFont(DATABASE.get(arus::Font::DisposableDroid));
		t.setCharacterSize(100);
	}
	hScore[0].setPosition(target.getPosition().x / 2.f - hScore[0].getLocalBounds().width, target.getSize().y / 2.f - 200.f);
	hScore[1].setPosition(target.getPosition().x / 2.f - hScore[1].getLocalBounds().width, target.getSize().y / 2.f - 100.f);
	//

}

void GUI::update(const bool& isTwoPlayers, const bool& mapCompleted, const bool& isSummary){
	if (!mapCompleted){
		Teksty[1].setString(std::to_string(DATABASE.get().enemyCount)); //ilosc przeciwnikow
		Teksty[3].setString(std::to_string(DATABASE.get().p1LIVES)); //zycia 1 gracza
		Teksty[4].setString(std::to_string(DATABASE.get().displayedLevel)); //numer rundy
		Teksty[6].setString(std::to_string(DATABASE.get().p2LIVES)); //zycia 2 gracza
	}
	else{
		if (isSummary == false){
			player1[0].setString("I-Player");
			player1[1].setString("STAGE " + std::to_string(stats.displayedLevel));
			player1[2].setString(std::to_string(stats.p1POINTS));
			player1[3].setString(std::to_string(stats.e1p1 * 100));
			player1[4].setString(std::to_string(stats.e1p1));
			player1[5].setString(std::to_string(stats.e2p1 * 200));
			player1[6].setString(std::to_string(stats.e2p1));
			player1[7].setString(std::to_string(stats.e3p1 * 300));
			player1[8].setString(std::to_string(stats.e3p1));
			player1[9].setString(std::to_string(stats.e4p1 * 400));
			player1[10].setString(std::to_string(stats.e4p1));
			player1[11].setString("Total");
			player1[12].setString(std::to_string(stats.e1p1 + stats.e2p1 + stats.e3p1 + stats.e4p1));
			player1[13].setString("Press SPACE to continue");

			if (isTwoPlayers){
				player2[0].setString("II-Player");
				player2[1].setString(std::to_string(stats.p2POINTS));
				player2[2].setString(std::to_string(stats.e1p2));
				player2[3].setString(std::to_string(stats.e1p2 * 100));
				player2[4].setString(std::to_string(stats.e2p2));
				player2[5].setString(std::to_string(stats.e2p2 * 200));
				player2[6].setString(std::to_string(stats.e3p2));
				player2[7].setString(std::to_string(stats.e3p2 * 300));
				player2[8].setString(std::to_string(stats.e4p2));
				player2[9].setString(std::to_string(stats.e4p2 * 400));
				player2[10].setString("vs");
				player2[11].setString(std::to_string(stats.e1p2 + stats.e2p2 + stats.e3p2 + stats.e4p2));
			}
		}
		else {
			unsigned int temp;
			if (isTwoPlayers){
				if (stats.p1POINTS < stats.p2POINTS) temp = stats.p2POINTS;
				else temp = stats.p1POINTS;
			}
			else temp = stats.p1POINTS;

			int t;
			if (stats.p1POINTS > stats.p2POINTS) t = stats.p1POINTS;
			else {
				t = stats.p2POINTS;
			}

			hScore[0].setString("HI-SCORE");
			hScore[1].setString(std::to_string(t));

			DATABASE.resetToDefaultStats();
		}
	}
}

void GUI::render(const bool& isTwoPlayers, const bool& mapCompleted, const bool& isSummary){
	if (mapCompleted == false){//rysowanie podczas gry

		if (isTwoPlayers){
			target.draw(Teksty[5]);
			target.draw(Teksty[6]);
			tank_icon[2] >> target;
		}

		for (int i = 0; i < 5; i++) target.draw(Teksty[i]);

		tank_icon[0] >> target;
		tank_icon[1] >> target;
		flaga >> target;

	}
	else{//loadscreen lub summary
		target.clear(sf::Color::Black);

		if (isSummary == true){
			//gdy podsumowanie
			for (sf::Text& t : hScore) target.draw(t);
		}
		else {
			//teksty gdy jeden gracz
			for (sf::Text& t : player1) target.draw(t);
			for (RenderElement& r : player1elements) r >> target;
			target.draw(underline);
			if (isTwoPlayers){
				//+ teksty gracza 2 
				for (sf::Text& t : player2) target.draw(t);
				for (RenderElement& r : player2elements) r >> target;
			}
		}
	}
}