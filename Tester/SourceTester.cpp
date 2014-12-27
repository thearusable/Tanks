#include"State.cpp"
#include"FSM.cpp"
#include<iostream>

using namespace std;

int main(){
	//zdarzenia
	int WIDAC_GRACZA = 101;
	int NIEWIDAC_GRACZA = 102;
	int ELEMENT_DO_ROZWALENIA = 103;
	int ZNISZCZONO_ELEMENT = 104;
	//stany
	int STATE_ID_PATROL = 0;
	int STATE_ID_TAKTYKA = 1;
	int STATE_ID_SZTURM = 2;
	int STATE_ID_ZNISZCZ_KLOCEK = 3;
	int STATE_ID_STOJ_STRZELAJ = 4;
	int STATE_ID_UCIECZKA = 5;
	//dodatkowe dane
	int LOW_HP = 1000;
	int MEDIUM_HP = 1001;
	int HIGH_HP = 1002;

	State* statePatrol = new State(STATE_ID_PATROL, 2);
	statePatrol->addTransistion(WIDAC_GRACZA, STATE_ID_TAKTYKA);
	statePatrol->addTransistion(ELEMENT_DO_ROZWALENIA, STATE_ID_ZNISZCZ_KLOCEK);

	State* stateTaktyka = new State(STATE_ID_TAKTYKA,3); //w zaleznosci od zycia zmieni stan
	stateTaktyka->addTransistion(LOW_HP, STATE_ID_UCIECZKA);
	stateTaktyka->addTransistion(MEDIUM_HP, STATE_ID_STOJ_STRZELAJ);
	stateTaktyka->addTransistion(HIGH_HP, STATE_ID_SZTURM);

	State* stateUcieczka = new State(STATE_ID_UCIECZKA,1);
	stateUcieczka->addTransistion(NIEWIDAC_GRACZA, STATE_ID_PATROL);

	State* stateStojStrzelaj = new State(STATE_ID_STOJ_STRZELAJ, 1);
	stateStojStrzelaj->addTransistion(NIEWIDAC_GRACZA, STATE_ID_PATROL);

	State* stateSzturm = new State(STATE_ID_SZTURM, 1);
	stateSzturm->addTransistion(NIEWIDAC_GRACZA, STATE_ID_PATROL);

	State* stateZniszczKlocek = new State(STATE_ID_ZNISZCZ_KLOCEK, 1);
	stateZniszczKlocek->addTransistion(ZNISZCZONO_ELEMENT, STATE_ID_PATROL);


	//dodawanie do FSM
	FSM FSMachine(STATE_ID_PATROL);

	FSMachine.addState(statePatrol);
	FSMachine.addState(stateTaktyka);
	FSMachine.addState(stateUcieczka);
	FSMachine.addState(stateStojStrzelaj);
	FSMachine.addState(stateSzturm);
	FSMachine.addState(stateZniszczKlocek);




	int input = 0, output = 0, hp = 2;
	while (input != -1){
		
			
		system("cls");
		cout << "******************************" << endl;
		cout << "HP: " << hp << endl;

		output = FSMachine.stateTransition(input);

		if (output == STATE_ID_TAKTYKA){
			if (hp == 1) FSMachine.stateTransition(LOW_HP);
			else if (hp < 3) FSMachine.stateTransition(MEDIUM_HP);
			else if (hp >= 3) FSMachine.stateTransition(HIGH_HP);
		}

		output = FSMachine.getCurrentState();

		if (output == STATE_ID_PATROL) cout << "STATE_PATROL" << endl;
		if (output == STATE_ID_STOJ_STRZELAJ) cout << "STATE_STOJ_STRZELAJ" << endl;
		if (output == STATE_ID_SZTURM) cout << "STATE_SZTURM" << endl;
		if (output == STATE_ID_UCIECZKA) cout << "STATE_UCIECZKA" << endl;
		if (output == STATE_ID_ZNISZCZ_KLOCEK) cout << "STATE_ZNISZCZ_KLOCEK" << endl;

		cout << "******************************" << endl;

		cout << "101 - WIDAC_GRACZA" << endl;
		cout << "102 - NIEWIDAC_GRACZA" << endl;
		cout << "103 - ELEMENT_DO_ROZWALENIA" << endl;
		cout << "104 - ZNISZCZONO_ELEMENT" << endl;
		cin >> input;
		
	}




}