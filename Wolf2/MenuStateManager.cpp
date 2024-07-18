#include "MenuStateManager.h"

menuState_K MenuStateManager::m_lastMenuState = undefined;
__int64 MenuStateManager::m_idMenuManager_Shell_PtrAddr = 0;


std::string MenuStateManager::getMenuStateAsStr(menuState_K menuState) {
	switch (menuState)
	{
	case undefined:
		return "undefined";
	case uninitialized:
		return "uninitialized";
	case inMenu:
		return "inMenu";
	case NotInMenu:
		return "NotInMenu";
	default:
		return "default (How could this happen?!)";
	}
}


std::string MenuStateManager::shellScreenToString(shellScreen_t screen) {
	switch (screen) {
	case SHELL_SCREEN_START: return "SHELL_SCREEN_START";
	case SHELL_SCREEN_ROOT: return "SHELL_SCREEN_ROOT";
	case SHELL_SCREEN_PAUSE: return "SHELL_SCREEN_PAUSE";
	case SHELL_SCREEN_DEV: return "SHELL_SCREEN_DEV";
	case SHELL_SCREEN_TIMELINE: return "SHELL_SCREEN_TIMELINE";
	case SHELL_SCREEN_MAP_GROUPS: return "SHELL_SCREEN_MAP_GROUPS";
	case SHELL_SCREEN_MAP_GROUP_BROWSER: return "SHELL_SCREEN_MAP_GROUP_BROWSER";
	case SHELL_SCREEN_MAP_LAYERS: return "SHELL_SCREEN_MAP_LAYERS";
	case SHELL_SCREEN_SAS: return "SHELL_SCREEN_SAS";
	case SHELL_SCREEN_CHALLENGE_LEADERBOARDS: return "SHELL_SCREEN_CHALLENGE_LEADERBOARDS";
	case SHELL_SCREEN_EXTRAS: return "SHELL_SCREEN_EXTRAS";
	case SHELL_SCREEN_PROGRESSION_SLOT: return "SHELL_SCREEN_PROGRESSION_SLOT";
	case SHELL_SCREEN_BINKREPLAY: return "SHELL_SCREEN_BINKREPLAY";
	case SHELL_SCREEN_CREDITS: return "SHELL_SCREEN_CREDITS";
	case SHELL_SCREEN_STATISTICS: return "SHELL_SCREEN_STATISTICS";
	case SHELL_SCREEN_COLLECTABLES: return "SHELL_SCREEN_COLLECTABLES";
	case SHELL_SCREEN_COMBAT_SIM: return "SHELL_SCREEN_COMBAT_SIM";
	case SHELL_SCREEN_EMPTY_DUMMY: return "SHELL_SCREEN_EMPTY_DUMMY";
	case SHELL_SCREEN_ANNOUNCEMENTS: return "SHELL_SCREEN_ANNOUNCEMENTS";
	case SHELL_SCREEN_BNET_LOGIN_CREATE: return "SHELL_SCREEN_BNET_LOGIN_CREATE";
	case SHELL_SCREEN_SETTINGS: return "SHELL_SCREEN_SETTINGS";
	case SHELL_SCREEN_CONTROLS: return "SHELL_SCREEN_CONTROLS";
	case SHELL_SCREEN_GAMEPAD: return "SHELL_SCREEN_GAMEPAD";
	case SHELL_SCREEN_GAMEPLAY_SETTINGS: return "SHELL_SCREEN_GAMEPLAY_SETTINGS";
	case SHELL_SCREEN_VIDEO_SETTINGS: return "SHELL_SCREEN_VIDEO_SETTINGS";
	case SHELL_SCREEN_AUDIO: return "SHELL_SCREEN_AUDIO";
	case SHELL_SCREEN_KEYBOARD: return "SHELL_SCREEN_KEYBOARD";
	case SHELL_SCREEN_RESOLUTION: return "SHELL_SCREEN_RESOLUTION";
	case SHELL_SCREEN_PC_CONTROLS: return "SHELL_SCREEN_PC_CONTROLS";
	case SHELL_SCREEN_BRIGHTNESS: return "SHELL_SCREEN_BRIGHTNESS";
	case SHELL_SCREEN_DIFFICULTY: return "SHELL_SCREEN_DIFFICULTY";
	case SHELL_SCREEN_LOAD_GAME: return "SHELL_SCREEN_LOAD_GAME";
	case SHELL_SCREEN_LOAD_GAME_FROM_DEATH: return "SHELL_SCREEN_LOAD_GAME_FROM_DEATH";
	case SHELL_SCREEN_SAVE_GAME: return "SHELL_SCREEN_SAVE_GAME";
	case SHELL_SCREEN_SNAPMAP_MAIN: return "SHELL_SCREEN_SNAPMAP_MAIN";
	case SHELL_SCREEN_CHRONICLES: return "SHELL_SCREEN_CHRONICLES";
	case SHELL_SCREEN_CHRONICLE_VOLUMES: return "SHELL_SCREEN_CHRONICLE_VOLUMES";
	case SHELL_SCREEN_STOREFRONT: return "SHELL_SCREEN_STOREFRONT";
	case SHELL_SCREEN_GAMESTARTS: return "SHELL_SCREEN_GAMESTARTS";
	case SHELL_SCREEN_MODESELECT: return "SHELL_SCREEN_MODESELECT";
	case NUM_SHELL_SCREENS: return "NUM_SHELL_SCREENS";
	default: return "Unknown Shell Screen"; //!  (may be in game)
	}
}



void MenuStateManager::acquireidMenuManager_ShellPtr(__int64 idMenuManager_Shell_PtrAddr) {
	if (m_idMenuManager_Shell_PtrAddr != idMenuManager_Shell_PtrAddr) {
		logInfo("setState: idMenuManager_Shell_PtrAddr has changed from %p to %p", (void*)m_idMenuManager_Shell_PtrAddr, (void*)idMenuManager_Shell_PtrAddr);
		m_idMenuManager_Shell_PtrAddr = idMenuManager_Shell_PtrAddr;
	}
}

//void MenuStateManager::acquireMenuStateFromHook(int menuStateInt) {
//	if (menuStateInt < 0) {
//		m_lastMenuState = NotInMenu;
//	}
//	else if (menuStateInt == 3) {
//		m_lastMenuState = inDevMenu;
//	}
//	else {
//		m_lastMenuState = inMenu;
//	}
//
//
//}


//! attempt to prevent mod load crash by not using the cached m_idMenuManager_Shell_PtrAddr
//menuState_K MenuStateManager::getLastMenuState() {
//
//
//
//
//	return m_lastMenuState;
//}


//! we use at the start to check if menu has been initiatlized
menuState_K MenuStateManager::get()
{
	//logInfo("debug: MenuStateManager::get() called");
	menuState_K menuState = uninitialized;
	int currentMenuIndex = -2; //? arbitrary value to indicate unitialized

	if (!MemHelper::isBadReadPtr((void*)m_idMenuManager_Shell_PtrAddr)) {
		//! idMenuManager_Shell_a1 + 0x30 is activeScreen index(shellScreen_t)
		//__int64 menuIndexAddr = m_idMenuManager_Shell_PtrAddr + 0x30;
		//! from logs it never is a bad ptr
		/*if (MemHelper::isBadReadPtr((void*)menuIndexAddr)) {
			logErr("debug menuIndexAddr is bad ptr: %p", (void*)menuIndexAddr);
		}*/

		//shellScreen_t shellScreenIndex = *(shellScreen_t*)(m_idMenuManager_Shell_PtrAddr + 0x30);


		currentMenuIndex = *(int*)(m_idMenuManager_Shell_PtrAddr + 0x30);
		if (currentMenuIndex < 0) {
			menuState = NotInMenu;
		}
		else if (currentMenuIndex == 3) {
			menuState = inDevMenu;
		}
		else {
			menuState = inMenu;
		}







	}	

	if (menuState != m_lastMenuState) {
		auto lastMenuStateStr = getMenuStateAsStr(m_lastMenuState);
		auto menuStateStr = getMenuStateAsStr(menuState);
		logInfo("menuState has changed from: %s (%d) to %s (%d)", lastMenuStateStr.c_str(), (int)m_lastMenuState, menuStateStr.c_str(), (int)menuState);
		m_lastMenuState = menuState;
	}

	return menuState;
}


std::string MenuStateManager::getAsStr()
{
	auto menuState = get();
	//auto menuState = getLastMenuState();
	return getMenuStateAsStr(menuState);
}

bool MenuStateManager::isNotMenu()
{
	return get() == menuState_K::NotInMenu;
	//return getLastMenuState() == menuState_K::NotInMenu;
}

bool MenuStateManager::isInMenu() {
	return get() == menuState_K::inMenu;
}


bool MenuStateManager::isRenderModNameFlag()
{
	//auto state = getLastMenuState();
	auto state = get();
	return (state == menuState_K::inMenu) || (state == menuState_K::inDevMenu);
}


//void MenuStateManager::setState(__int64 idMenuManager_Shell_PtrAddr, int idMenuManager_currentScreen)
//{
//
//	logInfo("setState: test trigger...");
//
//	if (m_idMenuManager_Shell_PtrAddr != idMenuManager_Shell_PtrAddr) {
//		logInfo("setState: idMenuManager_Shell_PtrAddr has changed from %p to %p", (void*)m_idMenuManager_Shell_PtrAddr, (void*)idMenuManager_Shell_PtrAddr);
//		m_idMenuManager_Shell_PtrAddr = idMenuManager_Shell_PtrAddr;
//	}
//
//	menuState_K menuState = uninitialized;
//	
//	if (idMenuManager_currentScreen < 0) {
//		menuState = NotInMenu;
//	}
//	else {
//		menuState = inMenu;
//	}
//
//	if (menuState != m_menuState) {
//		m_menuState = menuState;
//		std::string stateStr = getMenuStateAsStr(menuState);
//		logInfo("MenuStateManager::setState: debug: menuState has changed to: %s", stateStr.c_str());
//	}
//
//	m_menuState = menuState;
//}


//gameState_t GameStateManager::get()
//{
//	__int64 idGameLocalPtr = MemHelper::getAddr(0x3C7CD40);
//	if (MemHelper::isBadReadPtr((void*)idGameLocalPtr)) {
//		logErr("update: idGameLocalPtr is bad ptr returning GAMESTATE_UNINITIALIZED");
//		return gameState_t::GAMESTATE_UNINITIALIZED;
//	}
//	//logInfo("update: idGameLocalPtr: %p", (void*)idGameLocalPtr);
//
//	__int64 idGameLocal = *(__int64*)idGameLocalPtr;
//	if (MemHelper::isBadReadPtr((void*)idGameLocal) || MemHelper::isBadReadPtr((void*)(idGameLocal + 0xD2D10))) {
//		logErr("update: idGameLocal is bad ptr returning GAMESTATE_UNINITIALIZED");
//		return gameState_t::GAMESTATE_UNINITIALIZED;
//	}
//	return *(gameState_t*)(idGameLocal + 0xD2D10);
//
//}
//
//
//std::string GameStateManager::getGameStateToString() {
//
//    auto state = get();
//
//    switch (state) {
//    case GAMESTATE_UNINITIALIZED:
//        return "GAMESTATE_UNINITIALIZED";
//    case GAMESTATE_NOMAP:
//        return "GAMESTATE_NOMAP";
//    case GAMESTATE_STARTUP:
//        return "GAMESTATE_STARTUP";
//    case GAMESTATE_ACTIVE:
//        return "GAMESTATE_ACTIVE";
//    case GAMESTATE_PLAYVIDEO:
//        return "GAMESTATE_PLAYVIDEO";
//    case GAMESTATE_SHUTDOWN:
//        return "GAMESTATE_SHUTDOWN";
//    case GAMESTATE_RESETDEMOSTATE:
//        return "GAMESTATE_RESETDEMOSTATE";
//    default:
//        return "Unknown";
//    }
//}
