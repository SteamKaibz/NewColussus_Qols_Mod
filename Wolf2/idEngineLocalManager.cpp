#include "idEngineLocalManager.h"


__int64 idEngineLocalManager::m_idEngineLocalPtr = 0;

bool idEngineLocalManager::m_debugLastIsGameActive = false;


__int64 idEngineLocalManager::getidEngineLocalPtr()
{
	return m_idEngineLocalPtr;
}


__int64 idEngineLocalManager::getIdRenderSystemLocal(){
	if (!m_idEngineLocalPtr) {
		logErr("m_idEngineLocalPtr is null returning 0");
		return 0;
	}
	__int64 ptr = *(__int64*) (m_idEngineLocalPtr + 0x20);
	if (!MemHelper::isBadReadPtr((void*)ptr)) {
		return ptr;
	}
	logErr("idEngineLocalManager::getIdRenderSystemLocal(): bad ptr: %p returning 0", (void*)ptr);
	return 0;
}


__int64 idEngineLocalManager::getidCVarSystemLocalPtr() {
	if (m_idEngineLocalPtr) {
		return m_idEngineLocalPtr + 0x40;
	}
	logErr("getidCVarSystemLocalPtr::m_idEngineLocalPtr is null returning 0");
	return 0;
}

__int64 idEngineLocalManager::getidCmdSystemLocalPtr() {
	if (m_idEngineLocalPtr) {
		return m_idEngineLocalPtr + 0x48;
	}
	logErr("getidCmdSystemLocalPtr::m_idEngineLocalPtr is null returning 0");
	return 0;
}

__int64 idEngineLocalManager::getTypeInfoToolPtr()
{
	if (m_idEngineLocalPtr) {
		return m_idEngineLocalPtr + 0x80;
	}
	logErr("getTypeInfoToolPtr::m_idEngineLocalPtr is null returning 0");
	return 0;
}


bool idEngineLocalManager::acquireidEngineLocalPtr(__int64 idEngineLocalPtr)
{
	if (MemHelper::isBadReadPtr((void*)idEngineLocalPtr)) {
		logErr("acquireidEngineLocalPtr: failed to handleChange idEngineLocalPtr (bad ptr): %p", (void*)idEngineLocalPtr);
		m_idEngineLocalPtr = 0;
		return false;
	}
	m_idEngineLocalPtr = idEngineLocalPtr;
	logInfo("acquireidEngineLocalPtr: Succes acquirring idEngineLocalPtr, m_idEngineLocalPtr: %p", (void*)m_idEngineLocalPtr);
	return true;   
}





 bool idEngineLocalManager::isGameActive()
 {
	 __int64 idRenderSystemLocalPtr = getIdRenderSystemLocal();
	 if (idRenderSystemLocalPtr) {
		 bool isActive = *(bool*)(idRenderSystemLocalPtr + 0x1D0);
		 if (isActive != m_debugLastIsGameActive) {
			 m_debugLastIsGameActive = isActive;
			 if (isActive) {
				 logInfo("isGameActive: game is now Active");
			 }
			 else {
				 logInfo("isGameActive: game is now PAUSED");
			 }
		 }
		 return isActive;
	 }
	 return false;
 }