#pragma once

#include "../MemHelper/MemHelper.h"



enum idConsoleState
{
	consoleStateUnknown = -1,
	consoleStateClosed = 0,
	consoleStateOpened = 1
};

class idConsoleLocalManager
{
private:

	static __int64 m_idConsoleLocal;
	static unsigned int m_isConsoleOpenedOffset;

	static idConsoleState m_consoleState;

public:


	static bool acquirreIdConsoleLocal(__int64);

	static std::string idConsoleStateToString(idConsoleState state);

	static bool isConsoleOpened();

};

