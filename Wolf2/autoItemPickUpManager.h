#pragma once


#include <windows.h>
#include "../Config/Config.h"
#include "../K_Utils/K_Utils.h"
#include "idGameLocalManager.h"
#include "../ModSettings/ModSettingsManager.h"




enum autoItemPickUpFeedback {
	unknown,
	autoPickUpItemSettingNone,
	noFocusTrackerPtr,
	noFocusUsableEntityPtr,
	nodeclEntityDef,
	activatorOrTakedownPrompt,
	ammoBoxLike,
	maxedOut,
	maxHealth,
	pickingUp,
	noConditionMet
};


class autoItemPickUpManager
{
private:

	static std::string m_ImgGuidebugFocusEntityString;
	static int m_debugLastcrosshairItemCount;
	static int m_debugcrosshairInfoState;
	//static std::string m_debugAutoPickUpInfoStr;

	static autoItemPickUpFeedback m_autoItemPickUpFeedback;
	static autoItemPickUpFeedback m_lastAutoItemPickUpFeedback;


	static const int m_idFocusTracker_PlayerOffset;
	static const int m_idHudHealthIndicatorInfoOffset;
	static const int m_declEntityDefPtrOffset;
	static const int m_inheritStrOffset;	
	static const int m_itemCountTextOffset; // for ex if you look a ammo on ground it will be the actual ammo text next to ammo icon.
	static const int m_iconStateOffset;

	//static bool m_isDebug;
	static bool m_isUseKeyAutoPressFlag;
	static uint64_t m_lastAutoUseKeyPressMs;
	static const int m_autoUseKeyPressMinIntervalMs;
	static const char* m_pickUpPrefix;
	static size_t m_pickUpPrefixLen;
	static const char* m_pickUpCategories[];

	static __int64 m_gameTimeSnapshot; //! used for the function pointer.

	static __int64 m_currentFocusedEntityPtr;

	

public:
	static bool isMaxHealth(idPlayer* idPlayerAddr);

	static bool isMaxArmor(idPlayer* idPlayerAddr);

	//bool isForcePickUp();

	//static void update(idFocusTracker_Player* ptr, __int64 idPlayerAddr);

	//static void debug(idFocusTracker_Player* ptr, __int64 idPlayerAddr);

	static void debugUpdate(autoItemPickUpFeedback feedback);

	static std::string convertToString(autoItemPickUpFeedback feedback);

	static std::string getDebugFeedback();

	static std::string getLastDebugFeedback();

	static int  debugGetLastcrosshairItemCount();

	static int debugGetLastcrosshairInfoState();

	static std::string debugGetEntityName();

	static void LogFocusedEntity(idPlayer* idPlayerArg);

	static void acquirreCurrentlyFocusedEntity(idFocusTracker_Player* ptr, __int64 idPlayerAddr);

	static __int64 getCurrentFocusedEntityPtr();

	static void forceAutoPickUpItem_EB1360();

	static bool isUseKeyAutoPressFlag();

	static void setUseKeyAutoPressFlag(bool isFlag);

	static void forceAutoPickUpItem();

	//! will return 0 if not auto pick up mode or not ent to pickup
	static __int64 getAutoPickUpEntAddr(idPlayer* idPlayerArg);

	//static __int64 getAutoPickUpEntAddrV2(idPlayer* idPlayerArg); //? this one crashes eventually no idea why.

	static __int64 getAutoPickUpEntAddrV3(idPlayer* idPlayerArg);

	static __int64 getAutoPickUpEntAddrV4(idPlayer* idPlayerArg);

	//static bool isPressUseRequired(idPlayer* idPlayerArg);

	//static void pickUpEntity(__int64 ent, idPlayer* idPlayerArg);

};

