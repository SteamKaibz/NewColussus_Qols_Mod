#pragma once

#include "../MemHelper/MemHelper.h"
#include "GeneratedEnums.h"


enum menuState_K
{
	undefined,
	uninitialized,
	inDevMenu, //! which is what we use to display the mod settings as an overlay
	inMenu,
	NotInMenu // in fps, loading level and even being in the "map menu" as well
};




class MenuStateManager
{

private:
	static __int64 m_idMenuManager_Shell_PtrAddr;
	static menuState_K m_lastMenuState;

public:

	static std::string getMenuStateAsStr(menuState_K menuState);

	static std::string shellScreenToString(shellScreen_t screen);

	static void acquireidMenuManager_ShellPtr(__int64 idMenuManager_Shell_PtrAddr);

	//static void acquireMenuStateFromHook(int  menuStateInt);

	//static menuState_K getLastMenuState();

	static menuState_K get();

	static std::string getAsStr();

	static bool isNotMenu();

	static bool isInMenu();

	static bool isRenderModNameFlag();

	//static gameState_t getGameState();


	//static std::string getGameStateToString();

};

