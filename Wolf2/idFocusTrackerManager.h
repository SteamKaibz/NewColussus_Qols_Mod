#pragma once
#include "GeneratedEnums.h"
#include <string>
#include <unordered_map>
#include "GeneratedClasses.h"
#include "idGameLocalManager.h"
#include "idResourceManager.h"
#include "../ModSettings/ModSettingsManager.h"







/// <summary>
/// this could/should have been use for the auto pick up system but was created later so it'll be user mainly to check if custom hud should prevent the rendering of maxed out text or not
/// </summary>


class idFocusTrackerManager
{

private:

	static idPlayer* m_idPlayerPtr; //! yeah it's state i don't like it but i need it atm...

	static const int m_iconStateOffset; //! it's just simpler that way....

	static crosshairInfoIconState_t m_lastCrosshairInfoIconState;

	//! this is to identify all the possible ui materials so can decide when trigger auto pick up or not
	static std::vector<std::string> m_debugCrosshairInfoMaterialsNamesVec;

	static const char* m_grenadeMatrSuffix;
	static const size_t m_grenadeMatrSuffixLen;

	static const char* m_axeMatrSuffix;
	static const size_t m_axeMatrSuffixLen;

	static const char* m_hatchetMatrSuffix;
	static const size_t m_hatchetMatrSuffixLen;

	static const char* m_enigmaMatrSuffix;
	static const size_t m_enigmaMatrSuffixLen;

	static const char* m_hudIconMatrPrefix;
	static const size_t m_hudIconMatrPrefixLen;

	static const char* m_crosshairInfoTextUse;
	static const char* m_crosshairInfoTextMelee;


public:

	static bool shouldItemBePickedUp(idPlayer* idPlayerPtr);

	static bool isMaxHealth(idPlayer* idplayer);

	static void acquirecrosshairInfoDataForDebug(idPlayer* idPlayer_a1);

	static std::string debug_getLastcrosshairInfoIconStateStr();

	static std::string getCrosshairInfoIconStateStr(crosshairInfoIconState_t crosshairInfoIconState);


	static bool islastFocusedCrosshairIconStateMaxedOut();

	static std::string getCrosshairInfoIconStateStr();


	static std::string getCrosshairInfoStr();

	static void debug_LogAll_CROSSHAIRINFOICON_SINGLE_Materials(idResource* resPtr, void* crosshairInfoAddr);

};

