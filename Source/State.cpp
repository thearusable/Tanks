#include "State.h"

State::State(int iStateID, unsigned usTransistion)
{
	m_usNumbersOfTransistions = usTransistion;
	m_iStateID = iStateID;

	m_piInputs = new int[m_usNumbersOfTransistions];
	for (unsigned i = 0; i < m_usNumbersOfTransistions; ++i)
		m_piInputs[i] = 0;

	m_piOutputState = new int[m_usNumbersOfTransistions];
	for (unsigned i = 0; i < m_usNumbersOfTransistions; ++i)
		m_piOutputState[i] = 0;
}

State::State(State& state) {
	m_usNumbersOfTransistions = state.m_usNumbersOfTransistions;
	m_iStateID = state.m_iStateID;

	m_piInputs = new int[m_usNumbersOfTransistions];
	for (unsigned i = 0; i < m_usNumbersOfTransistions; ++i)
		m_piInputs[i] = state.m_piInputs[i];

	m_piOutputState = new int[m_usNumbersOfTransistions];
	for (unsigned i = 0; i < m_usNumbersOfTransistions; ++i)
		m_piOutputState[i] = state.m_piOutputState[i];
}

State::~State()
{
	delete[] m_piInputs;
	delete[] m_piOutputState;
}

int State::getID() {
	return m_iStateID;
}

void State::addTransistion(int iInput, int iOutputID) {
	for (unsigned i = 0; i < m_usNumbersOfTransistions; ++i) {
		if (m_piOutputState[i] == 0) {
			m_piOutputState[i] = iOutputID;
			m_piInputs[i] = iInput;
			return;
		}
	}
}

void State::deleteTransistion(int iOutputID) {
	unsigned i;
	for (i = 0; i < m_usNumbersOfTransistions; ++i) {
		if (m_piOutputState[i] == iOutputID)
			break;
	}

	if (i >= m_usNumbersOfTransistions)
		return;

	m_piInputs[i] = 0;
	m_piOutputState[i] = 0;

	for (; i < (m_usNumbersOfTransistions - 1); ++i) {
		if (!m_piOutputState[i])
			break;

		m_piInputs[i] = m_piInputs[i + 1];
		m_piOutputState[i] = m_piOutputState[i + 1];
	}
	m_piInputs[i] = 0;
	m_piOutputState[i] = 0;
}

int State::getOutput(int iInput) {
	int outputID = m_iStateID;

	for (unsigned i = 0; i < m_usNumbersOfTransistions; ++i) {
		if (iInput == m_piInputs[i]) {
			outputID = m_piOutputState[i];
			break;
		}
	}
	return outputID;
}