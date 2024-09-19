#include "idCvarManager.h"
#include "../ModSettings/ModSettingsManager.h"

//! from wold2Lib

__int64 idCvarManager::m_idCVarSystemLocal = 0;
__int64 idCvarManager::m_idCVarSystemLocal_FindInternalFuncAddr = 0;
//__int64 idCvarManager::m_idCVarSystemLocal_SetInternalFuncAddr = 0;

idInternalCVar__Set idCvarManager::m_setCvarFp = nullptr;




bool idCvarManager::acquireIdCVarSystemLocalPtr(__int64 idCVarSystemLocalPtr) {
	if (MemHelper::isBadReadPtr((void*)idCVarSystemLocalPtr)) {
		logErr("acquirreIdCVarSystemLocalPtr: failed to handleChange idCVarSystemLocalPtr (bad ptr): %p", (void*)idCVarSystemLocalPtr);		
		m_idCVarSystemLocal = 0;
		return false;
	}
	__int64 idCVarSystemLocalAddr = *(__int64*)idCVarSystemLocalPtr;
	if (MemHelper::isBadReadPtr((void*)idCVarSystemLocalAddr)) {
		logErr("acquirreIdCVarSystemLocalPtr: failed to handleChange idCVarSystemLocalAddr (bad ptr): %p", (void*)idCVarSystemLocalAddr);
		m_idCVarSystemLocal = 0;
		return false;
	}
	m_idCVarSystemLocal = idCVarSystemLocalAddr;
	logInfo("acquireIdCVarSystemLocalPtr: Succes acquirring idCVarSystemLocal, m_idCVarSystemLocal: %p", (void*)m_idCVarSystemLocal);
	return true;
}

bool idCvarManager::acquireFindInternalFuncPtr(__int64 funcAddr) {
	if (MemHelper::isBadReadPtr((void*)funcAddr)) {
		logErr("acquireFindInternalFuncPtr: failed to handleChange funcAddr (bad ptr): %p", (void*)funcAddr);
		m_idCVarSystemLocal_FindInternalFuncAddr = 0;
		return false;
	}
	m_idCVarSystemLocal_FindInternalFuncAddr = funcAddr;
	return true;
}

bool idCvarManager::acquireSetInternalFuncAddr(__int64 funcAddr) {
	if (MemHelper::isBadReadPtr((void*)funcAddr)) {
		logErr("acquireSetInternalFuncAddr: failed to handleChange funcAddr (bad ptr): %p", (void*)funcAddr);
		//m_idCVarSystemLocal_SetInternalFuncAddr = 0;
		return false;
	}
	//m_idCVarSystemLocal_SetInternalFuncAddr = funcAddr;
	m_setCvarFp = reinterpret_cast<idInternalCVar__Set>(funcAddr);
	return true;
}


__int64 idCvarManager::getCVarSystemLocal() {

	return m_idCVarSystemLocal;
}

//! assuming it's an idList by checking in CE at m_idCVarSystemLocal + 8. i checked the count (3256).
idList* idCvarManager::getCVarlist() {

	if (!m_idCVarSystemLocal) {
		return nullptr;
	}

	return (idList * )(m_idCVarSystemLocal + 0x8);
}


idCVar* idCvarManager::getCvarPtr(std::string cvarStr) {
	//logInfo("debug getCvarPtr 1");
	if (MemHelper::isBadReadPtr((void*)m_idCVarSystemLocal)) {
		logErr("getCvarPtr: m_idCVarSystemLocal is bad ptr: %p returning", (void*)m_idCVarSystemLocal);
		return nullptr;
	}
	if (!m_idCVarSystemLocal_FindInternalFuncAddr) {
		logErr("getCvarPtr: m_idCVarSystemLocal_FindInternalFuncAddr is null, returning");
		return nullptr;
	}
	typedef __int64(__fastcall* idCVarSystemLocal__FindInternal)(__int64 addr, const char* a2);
	auto cvarFindFunc = reinterpret_cast<idCVarSystemLocal__FindInternal>(m_idCVarSystemLocal_FindInternalFuncAddr);
	idCVar* cvarPtr = (idCVar*)(cvarFindFunc(m_idCVarSystemLocal, cvarStr.c_str()));
	if (MemHelper::isBadReadPtr((void*)cvarPtr)) {
		logWarn("getCvarPtr: cvarPtr for input: %s is bad ptr: %p returning nullptr", cvarStr.c_str(), cvarPtr);
		return nullptr;
	}
	//logInfo("debug getCvarPtr 2");
	return cvarPtr;
}


int idCvarManager::getCvarInt(std::string cvarStr) {
	auto cvarPtr = getCvarPtr(cvarStr);
	if (cvarPtr) {
		return cvarPtr->valueInteger;
	}
	logErr("getCvarInt: bad ptr: returning 0");
	return 0;
}



float idCvarManager::getCvarFloat(std::string cvarStr) {
	auto cvarPtr = getCvarPtr(cvarStr);
	if (cvarPtr) {
		return cvarPtr->valueFloat;
	}
	logErr("getCvarFloat: bad ptr: returning 0");
	return 0.0f;
}


std::string idCvarManager::getCvarString(std::string cvarStr) {
	auto cvarPtr = getCvarPtr(cvarStr);
	if (cvarPtr) {
		return cvarPtr->valueString.data;
	}
	logErr("getCvarString: bad ptr: returning empty str");
	return std::string();
}




//bool idCvarManager::setCvar(std::string cvarStr, std::string val) {
//	if (MemHelper::isBadReadPtr((void*)m_idCVarSystemLocal)) {
//		logErr("setCvar: m_idCVarSystemLocal is bad ptr: %p returning", (void*)m_idCVarSystemLocal);
//		return false;
//	}	
//	idCVar* cvarPtr = getCvarPtr(cvarStr);	
//	if (cvarPtr) {		
//		m_setCvarFp(cvarPtr, val.c_str(), 1);
//		return true;
//	}
//	else {
//		logErr("setCvar failed to find cvar: %s", cvarStr.c_str());
//		return false;
//	}	
//}


//bool idCvarManager::setCvarFast(idCVar* cvar, const char* valStr) {
//	if (cvar && m_setCvarFp) {
//		return m_setCvarFp(cvar, valStr, 1);
//	}
//	return false;
//}

//! cvars that need to be in a specific state when mod loads.
//bool idCvarManager::setModInitCvars() {
//	logInfo("enforcing mod load Cvars");
//
//	bool isError = false;
//
//	
//	isError =  !setCvar("in_unlockMouseInMenus", "0") || isError;
//	isError = !setCvar("view_showWorldMarkers", "1") || isError;
//
//	if (isError) {
//		logErr("setModInitCvars: Error some setCvar calls failed (?!)");
//	}
//
//	return !isError;
//}


//bool idCvarManager::setCriticalCvars() {
//	logInfo("enforcing critical Cvars");
//	bool isError = false;
//	
//
//	/*if (Config::IsForceNoModUi) {
//		isError = !setCvar("menu_showOptionForDevMenu", "0") || isError;
//	}*/
//	if(ModSettingsManager::getIsUseImgui()) {
//		isError = !setCvar("menu_showOptionForDevMenu", "1") || isError;
//	}
//	else {
//		isError = !setCvar("menu_showOptionForDevMenu", "0") || isError;
//	}
//	isError = !setCvar("g_showHud", "1") || isError;
//	isError = !setCvar("com_skipGameRenderView", "0") || isError;
//	isError = !setCvar("r_skipGuis", "0") || isError;
//	isError = !setCvar("swf_skipRender", "0") || isError;
//	isError = !setCvar("swf_skipRenderText", "0") || isError;
//
//	//isError = !setCvar("swf_safeFrame", "0.025") || isError;
//	isError = !setCvar("r_vignette", "0") || isError; //! this is noticable only when in simulation levels but still useful.
//	isError = !setCvar("view_showWorldMarkers", "1") || isError;  //! need to make sure it doesn't leave a ghost of itself in some situations.
//
//	idCvarManager::setValueMaxFloat("swf_safeFrame", swf_safeFrameMax); //! this will log.
//
//
//	idCvarManager::setValueMaxFloat("timescale", timeScaleMax); //! so we can fast forward faster...
//
//	if (isError) {
//		logErr("setCriticalCvars: Error some setCvar calls failed (?!)");
//	}
//
//	return !isError;
//}


void idCvarManager::init()
{
	idCvarManager::setValueMaxFloat("timescale", timeScaleMax); //! so we can fast forward faster...
}

//! set the max value the cvar can be set to
void idCvarManager::setValueMaxFloat(const char* cvarName, float maxVal) {
	auto cvar = getCvarPtr(std::string(cvarName));
	if (cvar) {
		cvar->valueMax = maxVal;
		logInfo("setValueMaxFloat cvar: %s valueMax has be changed to %.2f", cvar->name, cvar->valueMax);
	}
	else {
		logErr("setValueMaxFloat: failed to find cvar: %s", cvarName);
	}	
}


//void idCvarManager::setSafeFrame(float safeFrameFloat) {
//	auto safeFrameCvar = getCvarPtr("swf_safeFrame");
//	if (safeFrameCvar) {
//		if (safeFrameCvar->valueMax != .93f) {
//			safeFrameCvar->valueMax = 0.93f;
//		}
//		safeFrameCvar->valueFloat = safeFrameFloat;
//		return;
//	}
//	logErr("setSafeFrame: failed to find cvar");
//}


//void idCvarManager::testGetCvar(std::string cvarStr)
//{
//
//	__int64 cvarSystem = MemHelper::getAddr(0x41244E0);
//	if (MemHelper::isBadReadPtr((void*)cvarSystem)) {
//		logErr("test: cvarSystem is bad ptr returning");
//		return;
//	}
//	logInfo("testWriteCvar: cvarSystem: %p", (void*)cvarSystem);
//
//	/*__int64 cvarVTable = *(__int64*)cvarSystem;
//	if(MemHelper::isBadReadPtr((void*)cvarVTable)) {
//		logErr("test: cvarVTable is bad ptr returning");
//		return;
//	}
//	auto funcAddr = cvarVTable + 0x20;*/
//	auto funcAddr = MemHelper::getAddr(0x1239700);
//	if (MemHelper::isBadReadPtr((void*)funcAddr)) {
//		logErr("test: funcAddr is bad ptr returning");
//		return;
//	}
//	auto cvarSys = reinterpret_cast<idCVarSystemLocal__FindInternal>(funcAddr);
//	//auto result = cvarSys((__int64*)cvarSystemAddr, name);
//	idCVar* cvarPtr = (idCVar*)(cvarSys(cvarSystem, cvarStr.c_str()));
//	if (MemHelper::isBadReadPtr((void*)cvarPtr)) {
//		logErr("test: cvarPtr is bad ptr: %p returning", cvarPtr);
//		return;
//	}
//	logInfo("test: cvar addr: %p cvar name: %s value str: %s value int: %d value float: %.2f &cvarPtr->name: %p &cvarPtr->valueInteger: %p", cvarPtr, cvarPtr->name, cvarPtr->valueString.data, cvarPtr->valueInteger, cvarPtr->valueFloat, &cvarPtr->name, &cvarPtr->valueInteger);
//
//
//}

//void idCvarManager::testWriteCvar(std::string cvarStr, std::string val)
//{
//	__int64 cvarSystem = MemHelper::getAddr(0x41244E0);
//	if (MemHelper::isBadReadPtr((void*)cvarSystem)) {
//		logErr("testWriteCvar: cvarSystem is bad ptr returning");
//		return;
//	}
//	auto getCvarFuncAddr = MemHelper::getAddr(0x1239700);
//	if (MemHelper::isBadReadPtr((void*)getCvarFuncAddr)) {
//		logErr("testWriteCvar: getCvarFuncAddr is bad ptr returning");
//		return;
//	}
//
//	auto cvarSys = reinterpret_cast<idCVarSystemLocal__FindInternal>(getCvarFuncAddr);
//	idCVar* cvarPtr = (idCVar*)(cvarSys(cvarSystem, cvarStr.c_str()));
//
//	if (MemHelper::isBadReadPtr((void*)cvarPtr)) {
//		logErr("testWriteCvar: cvarPtr is bad ptr: %p returning", cvarPtr);
//		return;
//	}
//	auto setCvarFuncAddr = MemHelper::getAddr(0x1239140);
//	if (MemHelper::isBadReadPtr((void*)setCvarFuncAddr)) {
//		logErr("testWriteCvar: setCvarFuncAddr is bad ptr returning");
//		return;
//	}
//	auto setScarFunc = reinterpret_cast<idInternalCVar__Set>(setCvarFuncAddr);
//	setScarFunc(cvarPtr, val.c_str(), 1);
//}



