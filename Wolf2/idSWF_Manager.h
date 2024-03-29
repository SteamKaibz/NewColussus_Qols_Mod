#pragma once

#include <windows.h>
#include <mutex>
#include <string>

#include "GeneratedClasses.h"
#include "../MemHelper/MemHelper.h"
#include "../K_Utils/K_Utils.h"
#include "cachedCvarsManager.h"
#include "../ModSettings/ModSettingsManager.h"






class idSWF_Manager
{
private:

	static bool m_debug_IsMercuryLogComplete;
	static const char* m_mercuryHudFileName; //! name of the in-game hud with ammo, health...
	static idSWF* m_mercuryHudIdSWFPtr;

	//! it seems that this value will be 1080 even when the screen height is 1440....So we have to get that value from the game everytime resolution is changed. May be this value is always 1080p, we have to check with lower res
	static float inline m_idSWF_frameHeightForThisRes = 0.0f;


	static std::vector<std::string>m_debug_AllMercuryHudSpriteInstStrVec;
	//! this one will be filled manually by key press to add names to it for testing if they make some hud elements disapear or not
	static std::vector<std::string>m_debug_TestingHudSpriteInstStrVec;

	static bool isFillAllMercuryHudFlag;

	static std::mutex g_mutex; //! suggested by gpt and it actually prevented crashes.
	


	//static std::vector<std::string> m_debugAllHudSpriteInstancesNames;


public:

	static const int armorTextInstanceHash;
	static const int healthTextInstanceHash;
	static const int devMenuTextInstanceHash;
	static const int devMenuLvlLoadedTextInstanceHash;

	static const int maxedOutSwfHash;
	static const int alarmIconsSwfHash;
	static const int simulationTopHudScoreTextHash;
	static const float swfScaleDefault;

	static const swfColorRGBA_t m_defaultHudTextColor;
	static const swfColorRGBA_t m_orangeHudTextColor;
	static const swfColorRGBA_t m_redHudTextColor;



	

	//static void acquireMercuryHudidSWFPtr(idSWF* idSWF_Ptr);

	//! no check for mercury cause it's done in the hook
	static void acquireMercuryHudidSWFPtrFast(idSWF* idSWF_Ptr);

	//static void offsetHudr(float frameHeight, float scale);

	static void setCustomHudPosAndScale(idSWF* idSWF_Ptr);

	static void resetHudPosAndScaleToDefault(idSWF* idSWF_Ptr);

	//static void scaleHud(float scale);

	//! smooth change between colors
	static void lerp(idSWFTextInstance* textInst);

	static void blink(idSWFTextInstance* textInst);

	static bool isBlink(int blinkFreqMillis);

	static void setOrangeColor(idSWFTextInstance* textInst);

	static void setDefaultColor(idSWFTextInstance* textInst);

	static float smoothlyChangingFloat(float speed);


	static void debug_LogUniqueTextInstances(idSWFTextInstance* textInst);


	static void debug_LogMercuryHudDictionary();
	static void debug_changeidSWFShapeChannelScale(idSWFDictionaryEntry* entry);

	static void debug_AllMercuryHudNamesInVec();

	static void debug_offsetSpriteInstances(idSWF* idSWF_Ptr, idSWFSpriteInstance* spriteInstPtr);

	static std::vector<std::string> getTestingInstNamesVec();


	static bool addMercuryHudSpriteInstanceNameToVec(idSWF* idSWF_Ptr, idSWFSpriteInstance* spriteInstPtr);

	static void TestHudElements();


};

