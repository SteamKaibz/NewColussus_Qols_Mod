#include "hudManager.h"



//idHudInfo* hudManager::m_debugidHudInfoPtr = nullptr;


const int hudManager::m_hudDisabledMask = 0x3E00;
//const uint16_t hudManager::m_HUD_HIDDEN_FLAG = 0x7E40;

bool hudManager::isOrangeArmorTrigger(idHudInfo* idHudInfoPtr) {
	/*if (MemHelper::isBadReadPtr(m_debugidHudInfoPtr)) {
		logWarn("isOrangeArmorTrigger: m_debugidHudInfoPtr is bad ptr returning false.");
		return false;
	}*/
	if (idHudInfoPtr) {
		float armorOrangeTrigger = (float)(idHudInfoPtr->healthIndicator.armorMax * ModSettingsManager::getOrangeArmorTriggerPrct() / 100);
		return idHudInfoPtr->healthIndicator.armor <= armorOrangeTrigger;
	}
	return false;
	
	//return m_debugidHudInfoPtr->healthIndicator.armor <= ModSettingsManager::getOrangeArmorTriggerPrct();
}


bool hudManager::isRedArmorTrigger(idHudInfo* idHudInfoPtr) {
	/*if (MemHelper::isBadReadPtr(m_debugidHudInfoPtr)) {
		logWarn("isRedArmorTrigger: m_debugidHudInfoPtr is bad ptr returning false.");
		return false;
	}*/
	if (idHudInfoPtr) {
		float armorRedTrigger = (float)(idHudInfoPtr->healthIndicator.armorMax * ModSettingsManager::getRedHudArmorTriggerPrct() / 100);
		return idHudInfoPtr->healthIndicator.armor <= armorRedTrigger;
	}
	return false;
	
}



bool hudManager::isOrangeHealthTrigger(idHudInfo* idHudInfoPtr) {
	/*if (MemHelper::isBadReadPtr(m_debugidHudInfoPtr)) {
		logWarn("isOrangeHealthTrigger: m_debugidHudInfoPtr is bad ptr returning false.");
		return false;
	}*/
	if (idHudInfoPtr) {
		float healthOrangeTrigger = (float)(idHudInfoPtr->healthIndicator.healthMax * ModSettingsManager::getOrangeHealthTriggerPrct() / 100);
		return idHudInfoPtr->healthIndicator.health <= healthOrangeTrigger;
	}
	return false;
	
	//return m_debugidHudInfoPtr->healthIndicator.health <= ModSettingsManager::getOrangeHealthTriggerPrct();
}


bool hudManager::isRedHealthTrigger(idHudInfo* idHudInfoPtr) {
	/*if (MemHelper::isBadReadPtr(m_debugidHudInfoPtr)) {
		logWarn("isRedHealthTrigger: m_debugidHudInfoPtr is bad ptr returning false.");
		return false;
	}*/
	if (idHudInfoPtr) {
		float healthRedTrigger = (float)(idHudInfoPtr->healthIndicator.healthMax * ModSettingsManager::getRedHealthTriggerPrct() / 100);
		return idHudInfoPtr->healthIndicator.health <= healthRedTrigger;
	}
	return false;
	
	//return m_debugidHudInfoPtr->healthIndicator.health <= ModSettingsManager::getRedHealthTriggerPrct();
}


void hudManager::logWarningTriggerVals() {
	idHudInfo* idHudInfoPtr = idPlayerManager::getIdHudInfo();
	if (!MemHelper::isBadReadPtr(idHudInfoPtr)) {
		logInfo("debug: logWarningTriggerVals:");
		logInfo("current armor val f: %.2f (max armor int: %d) ", idHudInfoPtr->healthIndicator.armor, idHudInfoPtr->healthIndicator.armorMax);
		logInfo("current health val f: %.2f (max health int: %d) ", idHudInfoPtr->healthIndicator.health, idHudInfoPtr->healthIndicator.healthMax);

		logInfo("OrangeArmorTriggerPrct: %d ", ModSettingsManager::getOrangeArmorTriggerPrct());
		float armorOrangeTrigger = (float)(idHudInfoPtr->healthIndicator.armorMax * ModSettingsManager::getOrangeArmorTriggerPrct() / 100);
		logInfo("current armorOrangeTriggerVal: %.2f ", armorOrangeTrigger);

		logInfo("RedHudArmorTriggerPrct: %d ", ModSettingsManager::getRedHudArmorTriggerPrct());
		float armorRedTrigger = (float)(idHudInfoPtr->healthIndicator.armorMax * ModSettingsManager::getRedHudArmorTriggerPrct() / 100);
		logInfo("current RedHudArmorTriggerVal: %.2f ", armorRedTrigger);

		logInfo("OrangeHealthTriggerPrct: %d ", ModSettingsManager::getOrangeHealthTriggerPrct());
		float healthOrangeTrigger = (float)(idHudInfoPtr->healthIndicator.healthMax * ModSettingsManager::getOrangeHealthTriggerPrct() / 100);
		logInfo("current healthOrangeTriggerVal: %.2f ", healthOrangeTrigger);

		logInfo("RedHealthTriggerPrct: %d ", ModSettingsManager::getRedHealthTriggerPrct());
		float healthRedTrigger = (float)(idHudInfoPtr->healthIndicator.healthMax * ModSettingsManager::getRedHealthTriggerPrct() / 100);
		logInfo("current healthRedTriggerVal: %.2f ", healthRedTrigger);
		

	}
	/*else {
		logWarn("logWarningTriggerVals: idHudInfoPtr is bad ptr can not log");
	}*/
}

bool hudManager::isHudHidden(idHudInfo* ihHudInfoPtr) {
	if (ihHudInfoPtr) {
		bool result = (ihHudInfoPtr->hudFlags & m_hudDisabledMask) != 0;
		//logInfo("isHudHidden: ihHudInfoPtr: %p ihHudInfoPtr->hudFlags: %X  ihHudInfoPtr->hudFlags: %d (dec) result: %d", ihHudInfoPtr, ihHudInfoPtr->hudFlags, ihHudInfoPtr->hudFlags, result);
		 return (ihHudInfoPtr->hudFlags & m_hudDisabledMask) != 0;
	}
	return false;
}

bool hudManager::isHudHiddenAlt() {

	/*if (MemHelper::isBadReadPtr(m_debugidHudInfoPtr)) {
		logWarn("isHudHiddenAlt: m_debugidHudInfoPtr is bad ptr returning false.");
		return false;
	}*/
	idHudInfo* idHudInfoPtr = idPlayerManager::getIdHudInfo();
	if (idHudInfoPtr) {
		bool result = (idHudInfoPtr->hudFlags & m_hudDisabledMask) != 0;
		//logInfo("isHudHiddenAlt: m_debugidHudInfoPtr: %p m_debugidHudInfoPtr->hudFlags: %X  m_debugidHudInfoPtr->hudFlags: %d (dec) result: %d", m_debugidHudInfoPtr, m_debugidHudInfoPtr->hudFlags, m_debugidHudInfoPtr->hudFlags, result);
		return (idHudInfoPtr->hudFlags & m_hudDisabledMask) != 0;
	}
	return false;	
}

//? this seems to no have any data...what you want is forceLeanMode  value in idEnvironmentAnalyzer
//leanMode_t hudManager::getLeanMode() {
//
//	idHudInfo* idHudInfoPtr = idPlayerManager::getIdHudInfo();
//	if (idHudInfoPtr) {
//		return idHudInfoPtr->reticle.leanDirIndication;
//	}
//	logWarn("getLeanMode: failed to get leanmode");
//	return LEANMODE_ANY;
//
//}


//idHudInfo* hudManager::getidHudInfo() {
//	return idPlayerManager::getIdHudInfo();
//}




//void hudManager::acquireidHudInfoPtr(idHudInfo* ptr) {
//
//	m_debugidHudInfoPtr = ptr;
//}


//? 17/9/24 i realized that this function check doen't really check for dual wield, it checks for dual ammo, it DOES NOT MEAN that you have a weapon in each hands it only means that both weapons use the same ammo. (WEAPONAMMO_DUALAMMO). So this func is useless to us atm, i'll just leave it here for education purpose.
std::string hudManager::debug_GetDualAmmoInfoStr() {

	idHudInfo* idHudInfoPtr = idPlayerManager::getIdHudInfo();
	if (idHudInfoPtr) {
		int flags = idHudInfoPtr->weaponAmmoStatus.getFlags();
		bool isDualWield = (idHudInfoPtr->weaponAmmoStatus.getFlags() & weaponAmmoFlags_t::WEAPONAMMO_DUALAMMO) != 0;
		if (isDualWield) {
			return "Hud Info : Dual Ammo Active (Meaning Both weapon are the same). Flags: " + K_Utils::intToHexString(flags);
		}
		else {
			return "Hud Info : single ammo Active. (If holding 2 weaps, they are NOT the same) Flags: " + K_Utils::intToHexString(flags);
		}
	}
	else {
		return "Hud Info : bad ptr !!! ";
	}
}

//? this fails and i don't want to make it better, as we should have a better way to get if dual wield now
//bool hudManager::isDualWielding() {
//
//	idHudInfo* idHudInfoPtr = idPlayerManager::getIdHudInfo();
//	if (idHudInfoPtr) {
//		
//
//		return (*(char*) ((char*)idHudInfoPtr + 0x188)) == 1;
//	}
//	return false;
//
//}


void hudManager::debugLogWeaponInfo() {

	idHudInfo* idHudInfoPtr = idPlayerManager::getIdHudInfo();
	if (idHudInfoPtr) {
		logInfo("debugLogWeaponInfo: &idHudInfoPtr->weaponAmmoStatus: %p", &idHudInfoPtr->weaponAmmoStatus);		
	}

}



//std::string hudManager::imGuiDebugGetidDeclWeaponPtrStatus() {
//	if (MemHelper::isBadReadPtr(m_debugidHudInfoPtr)) {
//		return "NO HUD INFO PTR";
//	}
//	else if (MemHelper::isBadReadPtr(&m_debugidHudInfoPtr->reticle.weaponDecl)){
//		return "DECL WEAPON IS BAD PTR";		
//	}
//	else {
//		auto declWeaponPtr = m_debugidHudInfoPtr->reticle.weaponDecl;
//		if (MemHelper::isBadReadPtr(declWeaponPtr)) {
//			return "DECL WEAPON IS NULL or BAD PTR";
//		}
//		else {
//			auto declWeaponName = idResourceManager::getDeclName((idResource*)declWeaponPtr);
//			std::string result = "Decl Weapon name: " + declWeaponName + " ptr: " + K_Utils::intToHexString((__int64)declWeaponPtr);
//			return result;
//		}		
//	}
//	return "ERROR (why are we here?!)";
//}

//std::string hudManager::imGuiDebugGetidReticlePtrStatus() {
//	if (MemHelper::isBadReadPtr(m_debugidHudInfoPtr)) {
//		return "NO HUD INFO PTR";
//	}
//	else if (MemHelper::isBadReadPtr(&m_debugidHudInfoPtr->reticle.decl)) {
//		return "DECL RETICLE IS BAD PTR";
//	}
//	else {
//		auto declReticlePtr = m_debugidHudInfoPtr->reticle.decl;
//		if (!declReticlePtr) {
//			return "DECL RETICLE IS NULL";
//		}
//		else {
//			auto declReticleName = idResourceManager::getDeclName((idResource*)declReticlePtr);
//			std::string result = "Decl Reticle name: " + declReticleName + " ptr: " + K_Utils::intToHexString((__int64)declReticlePtr);
//			return result;
//		}
//	}
//	return "ERROR (why are we here?!)";
//}




void hudManager::setInGameReticleScale(float scaleF)
{//? doesn't work. somewhow you can not change the scale of reticles in this game compared to DE.
	int counter = 0;
	auto ptrsVec = idResourceManager::getResPtrsVecForClsName("idDeclWeaponReticle");
	for (size_t i = 0; i < ptrsVec.size(); i++)
	{
		auto declWeapPtr = (idDeclWeaponReticle*)ptrsVec[i];
		auto reticleName = idResourceManager::getDeclName((idResource*)declWeapPtr);
		if (declWeapPtr->reticleModelScale != scaleF) {
			declWeapPtr->reticleModelScale = scaleF;
			counter++;
		}
		
	}
	logInfo("setInGameReticleScale: updated the scales of %d reticles to %.2f", counter, scaleF);

}
