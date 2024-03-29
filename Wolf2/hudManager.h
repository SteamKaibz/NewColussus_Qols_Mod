#pragma once

#include "idResourceManager.h"
#include "../MemHelper/MemHelper.h"
#include "../ModSettings/ModSettingsManager.h"
#include "idPlayerManager.h"






class hudManager
{
private:
	//static idHudInfo* m_debugidHudInfoPtr;
	static const int m_hudDisabledMask;
	//static const uint16_t m_HUD_HIDDEN_FLAG;

public:

	static bool isOrangeArmorTrigger(idHudInfo* idHudInfoPtr);
	static bool isRedArmorTrigger(idHudInfo* idHudInfoPtr);

	static bool isOrangeHealthTrigger(idHudInfo* idHudInfoPtr);
	static bool isRedHealthTrigger(idHudInfo* idHudInfoPtr);

	static bool isHudHidden(idHudInfo* ihHudInfoPtr);

	static bool isHudHiddenAlt();

	//static void acquireidHudInfoPtr(idHudInfo* ptr);

	static void logWarningTriggerVals();


	static std::string inGuiGetDualWieldInfo();

	static std::string imGuiDebugGetidDeclWeaponPtrStatus();

	static std::string imGuiDebugGetidReticlePtrStatus();

	static void setInGameReticleScale(float scaleF);

};

