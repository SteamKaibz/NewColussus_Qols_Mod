#include "autoItemPickUpManager.h"


autoItemPickUpFeedback autoItemPickUpManager::m_autoItemPickUpFeedback = unknown;
autoItemPickUpFeedback autoItemPickUpManager::m_lastAutoItemPickUpFeedback = unknown;

int autoItemPickUpManager::m_debugLastcrosshairItemCount = -1;
int autoItemPickUpManager::m_debugcrosshairInfoState = -1;
std::string autoItemPickUpManager::m_ImgGuidebugFocusEntityString = "???";


const int autoItemPickUpManager::m_idFocusTracker_PlayerOffset = 0x22DE8;
const int autoItemPickUpManager::m_idHudHealthIndicatorInfoOffset = 0xCF98;
const int autoItemPickUpManager::m_declEntityDefPtrOffset = 0x4A8;
const int autoItemPickUpManager::m_inheritStrOffset = 0x70;
const int autoItemPickUpManager::m_itemCountTextOffset = 0x3E8;
const int autoItemPickUpManager::m_iconStateOffset = 0x3EC; // 0x3A8 + 0x44  

//bool autoItemPickUpManager::m_isDebug = true;

bool autoItemPickUpManager::m_isUseKeyAutoPressFlag = false;
uint64_t autoItemPickUpManager::m_lastAutoUseKeyPressMs = 0;
const int autoItemPickUpManager::m_autoUseKeyPressMinIntervalMs = 100;

const char* autoItemPickUpManager::m_pickUpCategories[] = { "health", "armor", "ammo", "weapon", "grenade" };
const char* autoItemPickUpManager::m_pickUpPrefix = "prop/pickup/";
size_t autoItemPickUpManager::m_pickUpPrefixLen = strlen(m_pickUpPrefix);

__int64 autoItemPickUpManager::m_gameTimeSnapshot = 0;


__int64 autoItemPickUpManager::m_currentFocusedEntityPtr = 0;




int autoItemPickUpManager::debugGetLastcrosshairItemCount() {
	return m_debugLastcrosshairItemCount;
}


int autoItemPickUpManager::debugGetLastcrosshairInfoState() {
	return m_debugcrosshairInfoState;
}

std::string autoItemPickUpManager::debugGetEntityName()
{
	return m_ImgGuidebugFocusEntityString;
}




bool autoItemPickUpManager::isMaxHealth(idPlayer* idplayer)
{
	if (!idplayer) {
		return true; //! not sure what to return here but this seems the best choice.
	}
	idHudHealthIndicatorInfo* idHudHealthIndicatorInfoPtr = (idHudHealthIndicatorInfo*)((char*)idplayer + m_idHudHealthIndicatorInfoOffset);
	bool isMaxHealth = idHudHealthIndicatorInfoPtr->health >= idHudHealthIndicatorInfoPtr->healthMax;
	/*if (isMaxHealth) {
		logInfo("isMaxHealth: health is max or overcharge, not auto picking up health item");
	}*/
	return isMaxHealth;

}

bool autoItemPickUpManager::isMaxArmor(idPlayer* idplayer)
{
	if (!idplayer) {
		return true; //! not sure what to return here but this seems the best choice.
	}
	idHudHealthIndicatorInfo* idHudHealthIndicatorInfoPtr = (idHudHealthIndicatorInfo*)((char*)idplayer + m_idHudHealthIndicatorInfoOffset);
	bool isMaxArmor = idHudHealthIndicatorInfoPtr->armor >= idHudHealthIndicatorInfoPtr->armorMax;
	//if (isMaxArmor) {
	//	//logInfo("isMaxArmor: armor is max, not auto pressing use key");
	//}
	return isMaxArmor;
}

//bool autoItemPickUpManager::isMaxAmmo(idPlayer* idplayer) {
//	weaponAmmoInfo_ammoInfo_t* ammoInfo_t_Ptr = (weaponAmmoInfo_ammoInfo_t*)((char*)idplayer + 0x5E8);
//	logInfo("isMaxAmmo debug");
//
//}




void autoItemPickUpManager::acquirreCurrentlyFocusedEntity(idFocusTracker_Player* ptr, __int64 idPlayerAddr) {

	auto focusEntityPtr = ptr->focusUsableEntityPtr;
	if (!focusEntityPtr) {
		m_currentFocusedEntityPtr = 0;
	}
	else {
		m_currentFocusedEntityPtr = focusEntityPtr;
	}
}

 __int64 autoItemPickUpManager::getCurrentFocusedEntityPtr() {
	 if (MemHelper::isBadReadPtr((void*)m_currentFocusedEntityPtr)) {
		 m_currentFocusedEntityPtr = 0;
	 }
	 return m_currentFocusedEntityPtr;
}






bool autoItemPickUpManager::isUseKeyAutoPressFlag() {
	return m_isUseKeyAutoPressFlag;
}

void autoItemPickUpManager::setUseKeyAutoPressFlag(bool isFlag)
{
	m_isUseKeyAutoPressFlag = isFlag;
}





void autoItemPickUpManager::forceAutoPickUpItem() {
	auto idplayer = idGameLocalManager::getIdPlayer();
	if (!idplayer) return;
	m_gameTimeSnapshot = idGameLocalManager::getCurrentGameTime();

	if (!m_gameTimeSnapshot)return;

	typedef bool(__fastcall* idPlayer_UseProp_FEA010)(
		idPlayer* idPlayer_a1,
		unsigned int a2,
		__int64* AddrOfGameTimeUnique_t_time_a3);

	//! result: matches @ 0xFEA010, sig direct: 48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC 20 83 B9
	auto propFuncAddr = MemHelper::getFuncAddr(0xFEA010);
	if (MemHelper::isBadReadPtr((void*)propFuncAddr)) {
		logErr("forceAutoPickUpItem propFuncAddr is bad ptr: %p", (void*)propFuncAddr);
		return;
	}

	auto usePropFunc = reinterpret_cast<idPlayer_UseProp_FEA010>(propFuncAddr);
	logInfo("forceAutoPickUpItem: idPlayer: %p, &m_gameTimeSnapshot: %p", idplayer, &m_gameTimeSnapshot);

	usePropFunc(idplayer, (unsigned int)0, &m_gameTimeSnapshot);


	/*typedef __int64(__fastcall* idCVarSystemLocal__FindInternal)(__int64 addr, const char* a2);
	auto cvarFindFunc = reinterpret_cast<idCVarSystemLocal__FindInternal>(m_idCVarSystemLocal_FindInternalFuncAddr);
	idCVar* cvarPtr = (idCVar*)(cvarFindFunc(m_idCVarSystemLocal, cvarStr.c_str()));
	if (MemHelper::isBadReadPtr((void*)cvarPtr)) {
		logWarn("getCvarPtr: cvarPtr for input: %s is bad ptr: %p returning nullptr", cvarStr.c_str(), cvarPtr);
		return nullptr;
	}*/

}



void autoItemPickUpManager::LogFocusedEntity(idPlayer* idPlayerArg) {

	static __int64 lastEntityPtr = 0;

	m_ImgGuidebugFocusEntityString = "???";	

	if (!idPlayerArg) return;

	idFocusTracker_Player* focusTracker = (idFocusTracker_Player*)((char*)(idPlayerArg)+m_idFocusTracker_PlayerOffset);

	if (!focusTracker) {		
		return ;
	}

	if (!focusTracker->focusUsableEntityPtr) {
		m_ImgGuidebugFocusEntityString = "No focusable entity";
		return;
	}


	auto focusEntityPtr = focusTracker->focusUsableEntityPtr;
	auto declEntityDefPtr = focusEntityPtr + m_declEntityDefPtrOffset;
	auto declEntityDef = *(__int64*)declEntityDefPtr;
	if (!declEntityDef) {
		m_ImgGuidebugFocusEntityString = "No Decl entity Def";
		return ;
	}

	const char* inheritStr = *(const char**)(declEntityDef + m_inheritStrOffset);
	if (!inheritStr) {
		m_ImgGuidebugFocusEntityString = "No inheritStr";
		return;
	}
	

	if (focusEntityPtr != lastEntityPtr) {
		lastEntityPtr = focusEntityPtr;
		logInfo("LogFocusedEntity: focusEntityPtr: %p name: %s", (void*)focusEntityPtr, inheritStr);
	}

	m_ImgGuidebugFocusEntityString = "Entity Ptr " + K_Utils::intToHexString(focusEntityPtr) + " Name: " + inheritStr;	

}



//? not using this anymore
__int64 autoItemPickUpManager::getAutoPickUpEntAddrV4(idPlayer* idPlayerArg) {

	m_debugLastcrosshairItemCount = -1;
	m_debugcrosshairInfoState = -1;	


	/*if (ModSettingsManager::isAutoPickItem(none)) {
		debugUpdate(autoPickUpItemSettingNone);
		return 0;
	}*/

	if (!idPlayerArg) return 0;

	idFocusTracker_Player* focusTracker = (idFocusTracker_Player*)((char*)(idPlayerArg)+m_idFocusTracker_PlayerOffset);

	if (!focusTracker) {
		debugUpdate(noFocusTrackerPtr);
		return 0;
	}


	if (!focusTracker->focusUsableEntityPtr) {
		debugUpdate(noFocusUsableEntityPtr);
		return 0;
	}

	int crosshairItemCount = *(int*)((char*)focusTracker + m_itemCountTextOffset);
	m_debugLastcrosshairItemCount = crosshairItemCount;
	int crosshairInfoState = *(int*)((char*)focusTracker + m_iconStateOffset);
	m_debugcrosshairInfoState = crosshairInfoState;


	//! maxed out handled here:
	if (crosshairInfoState & CROSSHAIRINFOICON_MAXED) {
		debugUpdate(maxedOut);
		return 0;
	}


	auto focusEntityPtr = focusTracker->focusUsableEntityPtr;
	auto declEntityDefPtr = focusEntityPtr + m_declEntityDefPtrOffset;
	auto declEntityDef = *(__int64*)declEntityDefPtr;
	if (!declEntityDef) {
		debugUpdate(nodeclEntityDef);
		return 0;
	}


	const char* inheritStr = *(const char**)(declEntityDef + m_inheritStrOffset);
	if (inheritStr) {
		

		//logInfo("checking inheritStr");
		if (strncmp(inheritStr, m_pickUpPrefix, m_pickUpPrefixLen) == 0) {
			const char* subStr = inheritStr + m_pickUpPrefixLen;

			//const char* categories[] = { "health", "armor", "ammo", "weapon", "grenade" };
			for (const auto& category : m_pickUpCategories) {
				if (strstr(subStr, category) != nullptr) {
					//logInfo("checking cats");
					if (ModSettingsManager::isAutoPickItem(health) && (strcmp(category, "health") == 0)) {
						if (!isMaxHealth(idPlayerArg)) {
							debugUpdate(pickingUp);							
							return focusEntityPtr;
						}
						debugUpdate(maxHealth);
						return 0;
					}
					if (ModSettingsManager::isAutoPickItem(armor) && (strcmp(category, "armor") == 0)) {
						/*if (!isMaxArmor(idPlayerArg)) {
							return focusEntityPtr;
						}
						return 0;	*/
						debugUpdate(pickingUp);
						return focusEntityPtr;
					}
					/*if (ModSettingsManager::isAutoPickItem(weapon) && (strcmp(category, "weapon") == 0)) {
						debugUpdate(pickingUp);
						return focusEntityPtr;
					}*/
					if (ModSettingsManager::isAutoPickItem(ammo) && (strcmp(category, "ammo") == 0)) {
						debugUpdate(pickingUp);
						return focusEntityPtr;
					}
					//! nade will be considered ammo.
					if (ModSettingsManager::isAutoPickItem(ammo) && (strcmp(category, "grenade") == 0)) {
						//logInfo("checking nades returning focusEntityPtr : %p", (void*)focusEntityPtr);
						debugUpdate(pickingUp);
						return focusEntityPtr;
					}
				}
			}
		}
	}

	debugUpdate(noConditionMet);
	return 0;
}



//bool autoItemPickUpManager::isPressUseRequired(idPlayer* idPlayerArg) {
//
//
//
//}










//! it does work if triggered throug calling EB1360.
//? however it did crash when i went from looking at nade box to look at weapon rack.
void autoItemPickUpManager::forceAutoPickUpItem_EB1360() {
	auto idplayer = idGameLocalManager::getIdPlayer();
	if (!idplayer) {
		logErr("forceAutoPickUpItem_EB1360 idPlayer bad ptr returning");
		return;
	}
	if (!getCurrentFocusedEntityPtr()) {
		logWarn("m_currentFocusedEntityPtr is bad ptr returning");
		return;
	}


	typedef __int64(__fastcall* attemptToPickUpItem_EB1360)(__int64 idProp2_a1, idPlayer* idPlayer_a2, unsigned int a3, int a4);
	//! result: matches @ 0xEB1360, sig direct: 44 89 44 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 C7 45
	auto funcAddr = MemHelper::getFuncAddr(0xEB1360);
	if (MemHelper::isBadReadPtr((void*)funcAddr)) {
		logErr("forceAutoPickUpItem_EB1360 funcAddr is bad ptr: %p", (void*)funcAddr);
		return;
	}

	auto fp = reinterpret_cast<attemptToPickUpItem_EB1360>(funcAddr);
	//! well...it seems that seting 3rd arg to 0 fixed the crashing issues !!!!!!
	fp(getCurrentFocusedEntityPtr(), idplayer, 0, 0); //? trying 0 for 3rd argument by curiosity
	//fp(getCurrentFocusedEntityPtr(), idplayer, 4, 0); //? crashing somethimes with this



}


//? this is just not working unfortunately, too unreliable and source or crashing.
//void autoItemPickUpManager::pickUpEntity(__int64 ent, idPlayer* idPlayerArg) {
//	typedef __int64(__fastcall* attemptToPickUpItem_EB1360)(__int64 idProp2_a1, idPlayer* idPlayer_a2, unsigned int a3, int a4);
//	auto funcAddr = MemHelper::getFuncAddr(0xEB1360);
//	if (MemHelper::isBadReadPtr((void*)funcAddr)) {
//		logErr("forceAutoPickUpItem_EB1360 funcAddr is bad ptr: %p", (void*)funcAddr);
//		return;
//	}
//
//	auto fp = reinterpret_cast<attemptToPickUpItem_EB1360>(funcAddr);
//
//	//? this is, from my live debuging the source of the crash,
//	//x well...it seems that seting 3rd arg to 0 fixed the crashing issues !!!!!!
//	fp(ent, idPlayerArg, 0, 0); 
//}



void autoItemPickUpManager::debugUpdate(autoItemPickUpFeedback feedback)
{
	m_autoItemPickUpFeedback = feedback;

	if (feedback != m_lastAutoItemPickUpFeedback) {
		m_lastAutoItemPickUpFeedback = feedback;
	}

}

std::string autoItemPickUpManager::convertToString(autoItemPickUpFeedback feedback) {
	switch (feedback) {
	case unknown:
		return "unknown";
	case autoPickUpItemSettingNone:
		return "autoPickUpItemSettingNone";
	case noFocusTrackerPtr:
		return "noFocusTrackerPtr";
	case noFocusUsableEntityPtr:
		return "noFocusUsableEntityPtr";
	case nodeclEntityDef:
		return "nodeclEntityDef";			
	case activatorOrTakedownPrompt:
		return "activatorOrTakedownPrompt";
	case ammoBoxLike:
		return "ammoBoxLike";
	case maxedOut:
		return "maxedOut";
	case maxHealth:
		return "maxHealth";
	case pickingUp:
		return "pickingUp";
	case noConditionMet:
		return "noConditionMet";
	default:
		return "Unknown Feedback";
	}
}

std::string autoItemPickUpManager::getDebugFeedback()
{
	return  convertToString(m_autoItemPickUpFeedback);
}

std::string autoItemPickUpManager::getLastDebugFeedback()
{
	return convertToString(m_lastAutoItemPickUpFeedback);

}
