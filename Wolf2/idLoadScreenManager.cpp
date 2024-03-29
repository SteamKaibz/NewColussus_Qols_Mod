#include "idLoadScreenManager.h"


__int64 idLoadScreenManager::m_loadScreenRelatedPtr = 0;

const int idLoadScreenManager::m_renderModelGuiLoadScreenPtrOffset = 0x10;

const int idLoadScreenManager::m_renderWorlPtrOffset = 0xF8;




bool idLoadScreenManager::acquireIdLoadScreenRelatedPtr(__int64 addr)
{
	if (MemHelper::isBadReadPtr((void*)addr)) {
		m_loadScreenRelatedPtr = 0;
		return false;
	}
	m_loadScreenRelatedPtr = addr;
	logInfo("acquireIdLoadScreenRelatedPtr: setting m_loadScreenRelatedPtr to %p", (void*)addr);
	return true;
}

loadScreenState idLoadScreenManager::getLoadScreenState()
{
	if (!m_loadScreenRelatedPtr) {
		return loadScreenState::Unknow;
	}	
	if ((*(__int64*)(m_loadScreenRelatedPtr + m_renderModelGuiLoadScreenPtrOffset)) != 0) {
		return loadScreenState::Active;
	}
	return loadScreenState::NotActive;
}
