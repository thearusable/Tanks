#ifndef STATE_H
#define STATE_H

#pragma once
#include "arus.h"

class State
{
	unsigned m_usNumbersOfTransistions; //obslugiwana liczba przejsc
	int* m_piInputs; //wejsciowa tablica dla przejsc
	int* m_piOutputState; //wyjsciowa tablica stanow
	int m_iStateID; //unikatoy indentyfikator stanu
	
public:
	State(int iStateID, unsigned usTransistion); ////
	State(State& state);
	~State(); ////

	int getID();////
	void addTransistion(int iInput, int iOutputID);////
	void deleteTransistion(int iOutputID);//
	int getOutput(int iInput);////
};

#endif