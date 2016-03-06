#include "FSM.h"


FSM::FSM(int iStateID)
{
	m_iCurrentState = iStateID;
}


FSM::~FSM()
{
	m_map.clear();
}

int FSM::getCurrentState(){
	return m_iCurrentState;
}

void FSM::setCurrentState(int iStateID){
	m_iCurrentState = iStateID;
}


State& FSM::getState(int iStateID){
	StateMap::iterator it;

	//if (!m_map.empty()){
	//	it = m_map.find(iStateID);
	//	if (it != m_map.end()){
	//		return (*it).second;
	//	}
	//}
	return State(1,2);
}

void FSM::addState(State& pNewState){
	StateMap::iterator it;

	if (!m_map.empty()){
		it = m_map.find(pNewState.getID());
		if (it != m_map.end())
			return;
	}

	m_map.insert(std::make_pair(pNewState.getID(), pNewState));
}

void FSM::deleteState(int iStateID){
	StateMap::iterator it;

	if (!m_map.empty()){
		it = m_map.find(iStateID);

		if (it != m_map.end())
			m_map.erase(it);
	}

}

int FSM::stateTransition(int iInput){

	State pState = getState(m_iCurrentState);
	//if (pState == nullptr){
	//	m_iCurrentState = 0;
	//	return m_iCurrentState;
	//}

	//m_iCurrentState = pState->getOutput(iInput);
	return m_iCurrentState;
}