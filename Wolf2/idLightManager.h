#pragma once

#include <cstdint>
#include "../K_Utils/K_Utils.h"
#include "idLib.h"
#include "../ModSettings/ModSettingsManager.h"
#include "idMaterialManager.h"
#include "idGameLocalManager.h"








typedef char (__fastcall* setLightOn_E926A0)(idLight* idLightPtr);
typedef char(__fastcall* setLightLighOff_E92730)(idLight* idLightPtr);
typedef __int64(__fastcall* refreshLight_E92230)(idLight* idLightPtr);
typedef __int64(__fastcall* setMaterial_E924B0)(idLight* idLightPtr, const char* materialName);

//typedef char(__fastcall* idInternalCVar__Set)(idCVar* a1, const char* a2, char a3);

class idLightManager
{

private:

	static const int m_headLightptrOffset;

	//static bool m_isSetLightOnFlag;
	//static bool m_isToggleHeadLightStateFlag;
	
	//static uint64_t m_lastCheckMs;

	static const char* m_headLightEntityName;
	static __int64 debugLastHeadLightPtr;

	static const char* m_headLighMaterialName;
	static __int64 m_headLighMaterialPtr;

	//static bool m_isLastKnowLightStateOff;

	//static bool m_isRefreshLightFlag; //! raising it when out of menu and it will trigger only if light is already on.

	//! we're only going to use it to compare it with another ptr so i guess the state here is okish
	//static idLight* m_lastKnowHeadLightPtr;
	static idLight* m_debug_lastKnowHeadLightPtr;

	static setLightOn_E926A0 m_setLightOnFp;

	static setLightLighOff_E92730 m_setLightOffFp;

	static refreshLight_E92230 m_refreshLightFp;

	static setMaterial_E924B0 m_setMaterialFp;

	//! preventing scope glare
	static const float m_defautlLightStartX;
	static const float m_inScopelLightStartX;

	//! used to keep track if we should put the flashlight back on once out of the enigman/wartable/recharge
	static bool m_wasFlashlightOn;

	//! the map where the flashlight is actually on by default
	//static const std::string m_mapBonusRiversideName;

	

	//! instead of using those i'm now changing spotLight.lightStart.x instead.
	//static const float m_headlightSpecularScope;
	//static const float m_headlightSpecularDefault;


	//? unreliabel to id entities:
	//static const int m_headLightSpawnId;


public:

	static idLight* getHeadLightPtr();

	static idLight* getHeadLightPtr(idPlayer* idPlayerPtr);

	static void logChangedHeadLightPtr(idLight* headlighPtr);

	//static bool isHeadLightPtr(idLight* headlighPtr);

	//static void setHeadlighOnFlag(bool isOn);

	//static void raiseToggleHeadlightState();

	static void debugGetLastHeadLightPtr();

	static void getCurrentMapHeadLighMaterialPtr();

	//static bool isLastKnownHeadLightStateOff();

	//static void setRefreshFlag(bool isOn);

	//static bool isRefreshFlag();

	static const std::vector<unsigned char> InstantSwitchLightVec;
	static const std::vector<unsigned char> FadeLightVecVec;

	static void setHeadlightOn(idLight* headlightPtr);
	static void setHeadlightOff(idLight* headlightPtr);

	static void toggleHeadLight();

	//! this calls the fp but unfortunately it does not update the light intensity
	static void refreshHeadLight(idLight* headlightPtr);

	//! this should be called when we get out of menu so we make sure light is set up as user wants and it will togle it on=>off=>on if it's on.
	static void updateHeadLight();

	//! so we don't get glare in scope but still see the light when we touch a wall when not ads
	static void adjustLightStartX(idPlayer* idPlayerPtr);

	//! adjustLightStartX and toggle light if we're using Enigma like state or warTable :
	static void AdjustLight(idPlayer* idPlayerPtr);

	//! don't want flashlith is certain situations
	static bool shouldFlashLightBeOff(movementMode_t curMovementMode);

	//! this version if to be used by the toggle light key system which happens in a specific hook
	static bool shouldFlashLightBeOff();

	//! reset of a state to prevent issues hopefully.
	static void resetWasFlashlightOn();
	//static void adjustHeadLigthSpecular(idPlayer* idPlayerPtr);

	//static void adjustHeadLigthSpecularV2();

	static bool isHeadLightColorBlack(idLight* headlightPtr);	
	
	//! this is used mainly by the headlight icon gui:
	static bool isHeadLightOn();

	//! use to check when we get out of menu if material has been applied, this is mainly used as we're using the mod by loading it with Xenos, but should not happen with xinput.dll
	//static bool isHeadLightMaterial();

	//! will change the material for the list of available light mats on this map
	static bool setSpotLighMaterial(std::string matName);

	//! will go through list a material names candidates
	static bool setLightMaterialFromVec();

	//! checking if the current map is the map which already have a headlight and which will crash the game if we force our.
	static bool isCurrentMapRiversideBonus(idPlayer* idPlayerPtr);

	static bool isCurrentMapRiversideBonus();

	static void debugSetLightMaterialFromVec();

};

