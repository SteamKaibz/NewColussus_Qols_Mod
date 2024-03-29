#include "weaponsManager.h"



std::vector<std::string> m_modifiableDeclsStrVec{
	"weapon/player/sp/handgun", // Pistole (names from the weapon menu in game)
	"weapon/player/sp/smg", // Maschinenpistole
	"weapon/player/sp/battlerifle", // Sturmgewehr
	"weapon/player/sp/battlerifle_marksman", // Sturmgewehr scope
	"weapon/player/sp/shotgun", // Schockhammer
	//"weapon/player/sp/dkw", // Dieselkraftwerk
	"weapon/player/sp/lkw", 
	"weapon/player/sp/lkw_scope", 
	"weapon/player/sp/kampfpistol", // kampfpistol
	"weapon/player/sp/heavyweapon", 
	"weapon/player/sp/lasergewehr", 
	"weapon/player/sp/ubergewehr" 
};


const std::string weaponsManager::m_handgunName = "weapon/player/sp/handgun";
const std::string weaponsManager::m_smg = "weapon/player/sp/smg";
const std::string weaponsManager::m_battlerifleName = "weapon/player/sp/battlerifle";
const std::string weaponsManager::m_battlerifle_marksmanName = "weapon/player/sp/battlerifle_marksman" ;
const std::string weaponsManager::m_shotgunName = "weapon/player/sp/shotgun" ;
const std::string weaponsManager::m_lkwName = "weapon/player/sp/lkw" ;
const std::string weaponsManager::m_lkw_scopeName = "weapon/player/sp/lkw_scope" ;
const std::string weaponsManager::m_kampfpistolName = "weapon/player/sp/kampfpistol";
const std::string weaponsManager::m_heavyweaponName = "weapon/player/sp/heavyweapon";
const std::string weaponsManager::m_lasergewehrName = "weapon/player/sp/lasergewehr";
const std::string weaponsManager::m_ubergewehrName = "weapon/player/sp/ubergewehr";


void weaponsManager::updateDeclWeapons() {

	auto modSettings = ModSettingsManager::get();
	int counter = 0;

	auto declWeaponForCurrentMapVec = idResourceManager::getResPtrsVecForClsName("idDeclWeapon");
	for (size_t i = 0; i < declWeaponForCurrentMapVec.size(); i++)
	{
		if (updateDeclWeapon((idDeclWeapon*)declWeaponForCurrentMapVec[i], modSettings)) counter++;
	}
	logInfo("updateDeclWeapons: found %d decl weapons", counter);
}


bool weaponsManager::updateDeclWeapon(idDeclWeapon* weapdeclPtr, const ModSettings& modSettingsRef) {

	//logWarn("updateDeclWeapon: called that should not be happening as we're checking for bugs!!!");

	if (!weapdeclPtr) return false;
	if (idResourceManager::getDeclName((idResource*)weapdeclPtr) == m_handgunName) {
		weapdeclPtr->ironSightZoom.zoomedFOV = modSettingsRef.handgunAdsFov;
		weapdeclPtr->ironSightZoom.sensitivity_scale_mouse = modSettingsRef.handgunAdsFovSensMultiplier;
		return true;
	}
	else if(idResourceManager::getDeclName((idResource*)weapdeclPtr) == m_smg) {
		weapdeclPtr->ironSightZoom.zoomedFOV = modSettingsRef.smgAdsFov;
		weapdeclPtr->ironSightZoom.sensitivity_scale_mouse = modSettingsRef.smgAdsFovSensMultiplier;
		return true;
	}
	else if (idResourceManager::getDeclName((idResource*)weapdeclPtr) == m_battlerifleName) {
		weapdeclPtr->ironSightZoom.zoomedFOV = modSettingsRef.battlerifleAdsFov;
		weapdeclPtr->ironSightZoom.sensitivity_scale_mouse = modSettingsRef.battlerifleAdsFovSensMultiplier;
		return true;
	}
	else if (idResourceManager::getDeclName((idResource*)weapdeclPtr) == m_battlerifle_marksmanName) {
		weapdeclPtr->ironSightZoom.zoomedFOV = modSettingsRef.battlerifleScopeFov;
		weapdeclPtr->ironSightZoom.sensitivity_scale_mouse = modSettingsRef.battlerifleScopeFovSensMultiplier;
		return true;
	}
	else if (idResourceManager::getDeclName((idResource*)weapdeclPtr) == m_shotgunName) {
		weapdeclPtr->ironSightZoom.zoomedFOV = modSettingsRef.shotgunAdsFov;
		weapdeclPtr->ironSightZoom.sensitivity_scale_mouse = modSettingsRef.shotgunAdsFovSensMultiplier;
		return true;
	}
	else if (idResourceManager::getDeclName((idResource*)weapdeclPtr) == m_lkwName) {
		weapdeclPtr->ironSightZoom.zoomedFOV = modSettingsRef.lkwAdsFov;
		weapdeclPtr->ironSightZoom.sensitivity_scale_mouse = modSettingsRef.lkwAdsFovSensMultiplier;
		return true;
	}
	else if (idResourceManager::getDeclName((idResource*)weapdeclPtr) == m_lkw_scopeName) {
		weapdeclPtr->ironSightZoom.zoomedFOV = modSettingsRef.lkwscopeFov;
		weapdeclPtr->ironSightZoom.sensitivity_scale_mouse = modSettingsRef.lkwscopeFovSensMultiplier;
		return true;
	}
	else if (idResourceManager::getDeclName((idResource*)weapdeclPtr) == m_kampfpistolName) {
		weapdeclPtr->ironSightZoom.zoomedFOV = modSettingsRef.kampfpistolAdsFov;
		weapdeclPtr->ironSightZoom.sensitivity_scale_mouse = modSettingsRef.kampfpistolAdsFovSensMultiplier;
		return true;
	}
	else if (idResourceManager::getDeclName((idResource*)weapdeclPtr) == m_heavyweaponName) {
		weapdeclPtr->ironSightZoom.zoomedFOV = modSettingsRef.heavyweaponAdsFov;
		weapdeclPtr->ironSightZoom.sensitivity_scale_mouse = modSettingsRef.heavyweaponAdsFovSensMultiplier;
		return true;
	}
	else if (idResourceManager::getDeclName((idResource*)weapdeclPtr) == m_lasergewehrName) {
		weapdeclPtr->ironSightZoom.zoomedFOV = modSettingsRef.lasergewehrAdsFov;
		weapdeclPtr->ironSightZoom.sensitivity_scale_mouse = modSettingsRef.lasergewehrAdsFovSensMultiplier;
		return true;
	}
	else if (idResourceManager::getDeclName((idResource*)weapdeclPtr) == m_ubergewehrName) {
		weapdeclPtr->ironSightZoom.zoomedFOV = modSettingsRef.ubergewehrAdsFov;
		weapdeclPtr->ironSightZoom.sensitivity_scale_mouse = modSettingsRef.ubergewehrAdsFovSensMultiplier;
		return true;
	}
	return false;

}


void weaponsManager::printAllPlayerDeclWeaponsInfo()
{
	auto resVec = idResourceManager::getResPtrsVecForClsName("idDeclWeapon");
	for (size_t i = 0; i < resVec.size(); i++)
	{
		printInfo((idDeclWeapon*)resVec[i]);
	}

}

//void weaponsManager::giveWeapon(std::string weaponDeclName)
//{
//
//}

void weaponsManager::printInfo(idDeclWeapon* declWeaponPtr)
{
	if (MemHelper::isBadReadPtr(declWeaponPtr)) {
		logErr("printInfo: declWeaponPtr is bad ptr: %p", declWeaponPtr);
		return;
	}
	std::string weaponName = idResourceManager::getDeclName((idResource*)declWeaponPtr);
	if (!weaponName.starts_with("weapon/ai")) {
		logInfo("weaponName: %s", weaponName.c_str());
		logInfo("decl ptr: %p", declWeaponPtr);
		logInfo("sensitivityWhileFiring: %.2f", declWeaponPtr->sensitivityWhileFiring);
		logInfo("zoomedFOV: %.2f", declWeaponPtr->ironSightZoom.zoomedFOV);
		logInfo("ads controller sens: %.2f", declWeaponPtr->ironSightZoom.sensitivity_scale_controller);
		logInfo("ads mouse sens sens: %.2f", declWeaponPtr->ironSightZoom.sensitivity_scale_mouse);
		logInfo("");
	}	

}
