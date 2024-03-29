#include "idKisculeNodeActionMidnightControlManager.h"

__int64 idKisculeManager::m_currentidKisculeNodeActionMidnightControlThisPtr = 0;
//__int64 idKisculeManager::m_idKisculeNodeActionMidnightControlVtb = 0;
//__int64 idKisculeManager::m_idKisculeGraphNodeDefinitionVtb = 0;


//bool idKisculeManager::acquireVtb(__int64 vtb)
//{
//	if (MemHelper::isBadReadPtr((void*)vtb)) {
//		logErr("acquirePtr: failed to acquire vtb (bad ptr): %p", (void*)vtb);
//		m_idKisculeNodeActionMidnightControlVtb = 0;
//		return false;
//	}
//	//__int64 addr = idKisculeNodeActionMidnightControlPtr;
//	//m_idKisculeNodeActionMidnightControlPtr = &addr;
//	m_idKisculeNodeActionMidnightControlVtb = vtb;
//	logWarn("acquirePtr: Succes acquirring vtb, m_idKisculeNodeActionMidnightControlVtb: %p BUT what we want is adddess of so &m_idKisculeNodeActionMidnightControlVtb is : %p", (void*)m_idKisculeNodeActionMidnightControlVtb, &m_idKisculeNodeActionMidnightControlVtb);
//	return true;
//}



//bool idKisculeManager::acquireVtb(__int64 idKisculeGraphNodeDefinitionVtb)
//{
//	if (MemHelper::isBadReadPtr((void*)idKisculeGraphNodeDefinitionVtb)) {
//		logErr("acquirePtr: failed to acquire idKisculeGraphNodeDefinitionVtb (bad ptr): %p", (void*)idKisculeGraphNodeDefinitionVtb);
//		m_idKisculeGraphNodeDefinitionVtb = 0;
//		return false;
//	}
//	//__int64 addr = idKisculeNodeActionMidnightControlPtr;
//	//m_idKisculeNodeActionMidnightControlPtr = &addr;
//	m_idKisculeGraphNodeDefinitionVtb = idKisculeGraphNodeDefinitionVtb;
//	logWarn("acquirePtr: Succes acquirring idKisculeGraphNodeDefinitionVtb, m_idKisculeGraphNodeDefinitionVtb: %p BUT what we want is adddess of so &m_idKisculeGraphNodeDefinitionVtb is : %p", (void*)m_idKisculeGraphNodeDefinitionVtb, &m_idKisculeGraphNodeDefinitionVtb);
//	return true;
//}



//bool idKisculeManager::acquireVtb(__int64 idKisculeNodeActionMidnightControlVtb)
//{
//	if (MemHelper::isBadReadPtr((void*)idKisculeNodeActionMidnightControlVtb)) {
//		logErr("acquirePtr: failed to acquire idKisculeNodeActionMidnightControlVtb (bad ptr): %p", (void*)idKisculeNodeActionMidnightControlVtb);
//		m_idKisculeNodeActionMidnightControlVtb = 0;
//		return false;
//	}
//	//__int64 addr = idKisculeNodeActionMidnightControlPtr;
//	//m_idKisculeNodeActionMidnightControlPtr = &addr;
//	m_idKisculeNodeActionMidnightControlVtb = idKisculeNodeActionMidnightControlVtb;
//	logWarn("acquirePtr: Succes acquirring idKisculeNodeActionMidnightControlVtb, m_idKisculeNodeActionMidnightControlVtb: %p BUT what we want is adddess of so &m_idKisculeNodeActionMidnightControlVtb is : %p", (void*)m_idKisculeNodeActionMidnightControlVtb, &m_idKisculeNodeActionMidnightControlVtb);
//	return true;
//}


//__int64 idKisculeManager::getVtb() {
//	return m_idKisculeNodeActionMidnightControlVtb;
//}

void idKisculeManager::aquirreCurrentIdKisculeNodeActionMidnightControlThisPtr(__int64 ptr)
{
	if (!MemHelper::isBadReadPtr((void*)ptr)) {
		m_currentidKisculeNodeActionMidnightControlThisPtr = ptr;
	}
	else {
		m_currentidKisculeNodeActionMidnightControlThisPtr = 0;
	}
}

//? doesn't work game will crash.
void idKisculeManager::skipToNextScene()
{
	//! result: matches @ 0x987BF0, sig direct: 48 83 EC 28 8B 51 40 85 D2 74 4F
	auto skipToNextSceneFuncAddr = MemHelper::getAddr(0x987BF0);
	if (MemHelper::isBadReadPtr((void*)skipToNextSceneFuncAddr)) {
		logErr("skipCutscene: skipToNextSceneFuncAddr is bad ptr: %p returning", (void*)skipToNextSceneFuncAddr);
		return;
	}
	if (MemHelper::isBadReadPtr((void*)m_currentidKisculeNodeActionMidnightControlThisPtr)) {
		logErr("skipCutscene: m_currentidKisculeNodeActionMidnightControlThisPtr is bad ptr: %p returning", (void*)m_currentidKisculeNodeActionMidnightControlThisPtr);
		return;
	}

	//logInfo("skipToNextScene: m_currentidKisculeNodeActionMidnightControlThisPtr: %p NOT trigering skip !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", (void*)m_currentidKisculeNodeActionMidnightControlThisPtr);
	//return; //? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	//! char __fastcall idKisculeNodeActionMidnightControl_SkipToNextScene_MB__987BF0(__int64 a1)
    typedef char(__fastcall* idKisculeNodeActionMidnightControl_SkipToNextScene)(__int64 a1);

	auto skipToNextSceneFunc = reinterpret_cast<idKisculeNodeActionMidnightControl_SkipToNextScene>(skipToNextSceneFuncAddr);
	skipToNextSceneFunc(m_currentidKisculeNodeActionMidnightControlThisPtr);
}


void idKisculeManager::stopMidnight() {

	//! result: matches @ 0x9878E0, sig direct: 40 53 48 83 EC 20 83 79 40 00 48 8B D9
	auto stopMidnightFuncAddr = MemHelper::getAddr(0x9878E0);
	if (MemHelper::isBadReadPtr((void*)stopMidnightFuncAddr)) {
		logErr("stopMidnight: stopMidnight is bad ptr: %p returning", (void*)stopMidnightFuncAddr);
		return;
	}
	if (MemHelper::isBadReadPtr((void*)m_currentidKisculeNodeActionMidnightControlThisPtr)) {
		logErr("stopMidnight: m_currentidKisculeNodeActionMidnightControlThisPtr is bad ptr: %p returning", (void*)m_currentidKisculeNodeActionMidnightControlThisPtr);
		return;
	}

	//logInfo("skipToNextScene: m_currentidKisculeNodeActionMidnightControlThisPtr: %p NOT trigering skip !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", (void*)m_currentidKisculeNodeActionMidnightControlThisPtr);
	//return; //? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//! char __fastcall idKisculeNodeActionMidnightControl_SkipToNextScene_MB__987BF0(__int64 a1)
	typedef char(__fastcall* idKisculeNodeActionMidnightControl_Stop)(__int64 a1);

	auto stopMidnightFunc = reinterpret_cast<idKisculeNodeActionMidnightControl_Stop>(stopMidnightFuncAddr);
	stopMidnightFunc(m_currentidKisculeNodeActionMidnightControlThisPtr);
}