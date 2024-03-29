#pragma once
#include <vector>
#include "GeneratedClasses.h"
#include "idResourceManager.h"
#include "../MemHelper/MemHelper.h"
#include "../ModSettings/ModSettings.h"
#include "../ModSettings/ModSettingsManager.h"








/// <summary>
/// configuring the fov and sens when zoomed and an option to disable the headlight when zoomed as there might be a glare/reflection atm, which could may be be fixec btw once we finally get to see and analyse the flashlight used in the very last mission. 
/// </summary>
class weaponsManager
{
private:

	
	//! list i gather manually by checking the name of the decl when equipping it. May be we'll miss some but i'll update the list as i go.
	static std::vector<std::string> m_modifiableDeclsStrVec;
	static void printInfo(idDeclWeapon* declWeaponPtr);

	static const std::string m_handgunName;
	static const std::string m_smg;
	static const std::string m_battlerifleName;
	static const std::string m_battlerifle_marksmanName;
	static const std::string m_shotgunName;
	static const std::string m_lkwName;
	static const std::string m_lkwName;
	static const std::string m_lkw_scopeName;
	static const std::string m_kampfpistolName;
	static const std::string m_heavyweaponName;
	static const std::string m_lasergewehrName;
	static const std::string m_ubergewehrName;


public:

	static void updateDeclWeapons();

	static bool updateDeclWeapon(idDeclWeapon* weapdeclPtr, const ModSettings& modSettingsRef);

	static void printAllPlayerDeclWeaponsInfo();
	//static void giveWeapon(std::string weaponDeclName);

};

