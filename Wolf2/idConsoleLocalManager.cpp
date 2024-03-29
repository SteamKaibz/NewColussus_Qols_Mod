#include "idConsoleLocalManager.h"


__int64 idConsoleLocalManager::m_idConsoleLocal = 0;
unsigned int idConsoleLocalManager::m_isConsoleOpenedOffset = 0xD8;
idConsoleState idConsoleLocalManager::m_consoleState = idConsoleState::consoleStateUnknown;


bool idConsoleLocalManager::acquirreIdConsoleLocal(__int64 addr) {
	if (MemHelper::isBadReadPtr((void*)addr)) {
		logErr("acquirreIdConsoleLocal: failed to handleChange IdConsoleLocal");
		m_idConsoleLocal = 0;
		return false;
	}

	m_idConsoleLocal = addr;
	logInfo("acquirreIdConsoleLocal: m_idConsoleLocal set to: %p", (void*)m_idConsoleLocal);
	return true;
}


std::string idConsoleLocalManager::idConsoleStateToString(idConsoleState state) {
	switch (state) {
	case consoleStateUnknown: return "unknown";
	case consoleStateClosed: return "closed";
	case consoleStateOpened: return "opened";
	default: return "invalid";
	}
}

bool idConsoleLocalManager::isConsoleOpened()
{
	if (m_idConsoleLocal) {
		int isOpened = *(int*)(m_idConsoleLocal + m_isConsoleOpenedOffset);

		/*idConsoleState consoleState = (idConsoleState)isOpened;
		if (consoleState != m_consoleState) {
			std::string oldState = idConsoleStateToString(m_consoleState);
			std::string newState = idConsoleStateToString(consoleState);
			logInfo("console State: console state has changed from %s to %s", oldState.c_str(), newState.c_str());
			m_consoleState = consoleState;
		}	*/
		return isOpened == 1;
	}
	logErr("isConsoleOpened m_idConsoleLocal is 0 returning true to let user use the console");
	return true; // returning true by default so user can alway use the console if an error happens.
}

