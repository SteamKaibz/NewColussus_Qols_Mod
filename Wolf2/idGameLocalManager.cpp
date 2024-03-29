#include "idGameLocalManager.h"


__int64 idGameLocalManager::m_idGameLocalPtr = 0;
__int64 idGameLocalManager::m_debuglastIdPlayerAdd = 0;


bool idGameLocalManager::acquireIdGameLocalPtr(__int64 idGameLocalPtr)
{
	if (MemHelper::isBadReadPtr((void*)idGameLocalPtr)) {
		logErr("acquireIdGameLocalPtr: failed to handleChange idGameLocalPtr (bad ptr): %p", (void*)idGameLocalPtr);
		m_idGameLocalPtr = 0;
		return false;
	}
	else {
		m_idGameLocalPtr = idGameLocalPtr;
		logInfo("acquireIdGameLocalPtr: Succes acquirring idGameLocalPtr: %p", (void*)idGameLocalPtr);
		return true;
	}
}


//? will have to may be get the offset another way...
idPlayer* idGameLocalManager::getIdPlayer()
{
	if(MemHelper::isBadReadPtr((void*)m_idGameLocalPtr)){
		return 0;
	}
	__int64 idGameLocal = *(__int64*)m_idGameLocalPtr;
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
	if (MemHelper::isBadReadPtr((void*)m_idGameLocalPtr)) {
		return 0;
	}
	__int64 idGameLocal = *(__int64*)m_idGameLocalPtr;

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
	if (MemHelper::isBadReadPtr((void*)m_idGameLocalPtr)) {
		return 0;
	}
	__int64 idGameLocal = *(__int64*)m_idGameLocalPtr;
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
	if (MemHelper::isBadReadPtr((void*)m_idGameLocalPtr)) {
		return result;
	}
	__int64 idGameLocal = *(__int64*)m_idGameLocalPtr;
	//const char* mapName = (const char*)(idGameLocal + 0xD0C98);
	//! from  11AF128:
	return *(const char**)(*(__int64*)(idGameLocal + 0x6080) + 0x30i64);

	//return (const char*)(idGameLocal + 0xD0C98);

}
