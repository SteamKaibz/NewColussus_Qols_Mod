#include "hintManager.h"


bool hintManager::m_wasHintBtnPressed = false;

void hintManager::setHintBtnPressState(bool wasPressed)
{
	static bool lastwasHintBtnPressed = false;

	if (wasPressed != lastwasHintBtnPressed) {
		lastwasHintBtnPressed = wasPressed;
		logInfo("setHintBtnPressState debug setting m_wasHintBtnPressed to %d", wasPressed);
	}	
	m_wasHintBtnPressed = wasPressed;
}

bool hintManager::wasHintBtnPressed() {
	return m_wasHintBtnPressed;
}
