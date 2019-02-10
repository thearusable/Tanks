#ifndef FSM_H
#define FSM_H

#pragma once
#include<map>
#include "State.h"

typedef std::map<int, State, std::less<int> > StateMap;

class FSM
{
	StateMap m_map;
	int m_iCurrentState;

public:
	FSM(int iStateID); //
	~FSM(); //

	int getCurrentState(); //
	void setCurrentState(int iStateID); //

	State& getState(int iStateID); //
	void addState(State& pState); //
	void deleteState(int iStateID); //

	int stateTransition(int iInput); //
};

#endif