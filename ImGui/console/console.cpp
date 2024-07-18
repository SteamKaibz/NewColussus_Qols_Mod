#include <Windows.h>

#include <fstream>

#include "console.hpp"

#include "../hooks/hooks.hpp"
#include "../../Loguru/loguru.hpp"
#include "../../Config/Config.h"


//! comment or uncomment this to enable/disable debug console
#define DISABLE_LOGGING_CONSOLE


void Console::Enable( ) {
#ifndef DISABLE_LOGGING_CONSOLE

	loguru::g_preamble_thread = false;
	loguru::g_preamble_date = false;
	loguru::g_preamble_uptime = false;
	loguru::g_stderr_verbosity = loguru::Verbosity_INFO;

	bool isConsoleAlreadyExist = false;

	if (!GetConsoleWindow()) {
		AllocConsole();
		SetConsoleTitleA("Mod - Debug Console");

		freopen_s(reinterpret_cast<FILE**>(stdin), "conin$", "r", stdin);
		freopen_s(reinterpret_cast<FILE**>(stdout), "conout$", "w", stdout);
		freopen_s(reinterpret_cast<FILE**>(stderr), "conout$", "w", stderr);
	}
	else {
		isConsoleAlreadyExist = true;
	}

	::ShowWindow(GetConsoleWindow(), SW_SHOW);

#endif
}

void Console::Hide( ) {
#ifndef DISABLE_LOGGING_CONSOLE
	::ShowWindow(GetConsoleWindow(), SW_HIDE);

#endif
}
