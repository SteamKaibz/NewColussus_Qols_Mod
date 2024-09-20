#include "idGameLocalManager.h"


__int64 idGameLocalManager::m_idGameLocalPtP = 0;
__int64 idGameLocalManager::m_debuglastIdPlayerAdd = 0;


bool idGameLocalManager::acquireIdGameLocalPtP(__int64 idGameLocalPtP)
{
	if (MemHelper::isBadReadPtr((void*)idGameLocalPtP)) {
		logErr("acquireIdGameLocalPtP: failed to handleChange idGameLocalPtP (bad ptr): %p", (void*)idGameLocalPtP);
		m_idGameLocalPtP = 0;
		return false;
	}
	else {
		m_idGameLocalPtP = idGameLocalPtP;
		logInfo("acquireIdGameLocalPtP: Succes acquirring idGameLocalPtP: %p", (void*)idGameLocalPtP);
		return true;
	}
}


//! 20/9/24 from my logs i can see that gamestate will be:
//! GAMESTATE_ACTIVE when in game or pause menu,
//! GAMESTATE_NOMAP when in main menu
//! GAMESTATE_UNINITIALIZED or GAMESTATE_STARTUP or GAMESTATE_SHUTDOWN when loading or going back to main menu.
//! Bear in mind though that we get GAMESTATE_UNINITIALIZED for nullptr but i don't see how to be more accurate than that.
gameState_t idGameLocalManager::getGameState()
{
	if (!m_idGameLocalPtP) {
		logErr("getGameState: m_idGameLocalPtP is nullptr");
		return GAMESTATE_UNINITIALIZED;
	}

	idGameLocal* gameLocal = (idGameLocal *) *(__int64*)m_idGameLocalPtP;
	if (!gameLocal) {
		//logWarn("getGameState: gameLocal is nullptr");
		return GAMESTATE_UNINITIALIZED;
	}

	return gameLocal->gamestate;	
}


//? will have to may be get the offset another way...
idPlayer* idGameLocalManager::getIdPlayer()
{
	if(MemHelper::isBadReadPtr((void*)m_idGameLocalPtP)){
		return 0;
	}
	__int64 idGameLocal = *(__int64*)m_idGameLocalPtP;
	//logInfo("getIdPlayer: debug idGameLocal: %p ", (void*)idGameLocal);
	__int64 idPlayerPtrToPtr = idGameLocal + 0x56A90;
	//logInfo("getIdPlayer: debug idPlayerPtrToPtr: %p ", (void*)idPlayerPtrToPtr);
	if (MemHelper::isBadReadPtr((void*)idPlayerPtrToPtr)) {
		return 0;
	}
	__int64 idPlayerPtr = *(__int64*)idPlayerPtrToPtr;
	if (MemHelper::isBadReadPtr((void*)idPlayerPtr)) {
		return 0;
	}
	__int64 idPlayerAdd = *(__int64*)idPlayerPtr;
	if (idPlayerAdd != m_debuglastIdPlayerAdd) {
		m_debuglastIdPlayerAdd = idPlayerAdd;
		logInfo("getIdPlayer: idPlayerAdd has changed to %p", (void*)idPlayerAdd);
	}
	if (MemHelper::isBadReadPtr((void*)idPlayerAdd)) {
		return 0;
	}
	return (idPlayer*)idPlayerAdd;
}

__int64 idGameLocalManager::getIdWorldspawn()
{
	if (MemHelper::isBadReadPtr((void*)m_idGameLocalPtP)) {
		return 0;
	}
	__int64 idGameLocal = *(__int64*)m_idGameLocalPtP;

	__int64 IdWorldspawnPtr = idGameLocal + 0x56160;
	if (MemHelper::isBadReadPtr((void*)IdWorldspawnPtr)) {
		logErr("getIdWorldspawn failed for IdWorldspawnPtr: bad ptr");
		return 0;
	}

	__int64 IdWorldspawn = *(__int64*)IdWorldspawnPtr;
	if (MemHelper::isBadReadPtr((void*)IdWorldspawn)) {
		logErr("getIdWorldspawn failed for IdWorldspawn: bad ptr");
		return 0;
	}
	return IdWorldspawn;
}


__int64 idGameLocalManager::getCurrentGameTime() {
	if (MemHelper::isBadReadPtr((void*)m_idGameLocalPtP)) {
		return 0;
	}
	__int64 idGameLocal = *(__int64*)m_idGameLocalPtP;
	//__int64 gameTimeVal = idGameLocal + 0xEC618 + 0x18;
	auto gameTimeValAddr = idGameLocal + 0xEC650;
	if (MemHelper::isBadReadPtr((void*)gameTimeValAddr)) {
		return 0;
	}
	__int64 gameTimeVal = *(__int64*)gameTimeValAddr;
	//__int64 timeVal = idGameLocal + 0xEC618 + 0x60;
	logInfo("getCurrentGameTimeAddr: gameTimeVal: %llX", gameTimeVal);
	return gameTimeVal;

}

std::string idGameLocalManager::getCurrentMapName() {
	std::string result = "map unknown";
	if (MemHelper::isBadReadPtr((void*)m_idGameLocalPtP)) {
		return result;
	}
	__int64 idGameLocal = *(__int64*)m_idGameLocalPtP;
	//const char* mapName = (const char*)(idGameLocal + 0xD0C98);
	//! from  11AF128:
	return *(const char**)(*(__int64*)(idGameLocal + 0x6080) + 0x30i64);

	//return (const char*)(idGameLocal + 0xD0C98);

}


idPlayerMetrics* idGameLocalManager::getidPlayerMetrics() {

	if (MemHelper::isBadReadPtr((void*)m_idGameLocalPtP)) {
		return nullptr;
	}

	idGameLocal* gameLocal = (idGameLocal*)*(__int64*)m_idGameLocalPtP;
	if (!gameLocal) {
		return nullptr;
	}

	if (!gameLocal->gameMetrics) {
		return nullptr;
	}

	return gameLocal->gameMetrics->players;

}