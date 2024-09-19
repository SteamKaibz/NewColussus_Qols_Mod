#pragma once

//#include "Wolf2/cachedCvarsManager.h"
//#include "ModSettings/ModSettingsManager.h"
//#include "Wolf2/hudManager.h"
#include "hudManager.h"
#include "weaponStateManager.h"





/// <summary>
/// this is at least, to set the pm_animCamAmount cvar back to its defaut value during cutscene so we don't get bugs like the whellchair+wife rescue sequence where we get stuck as long as pm_animCamAmount is not at the value it should be.
/// </summary>
class cameraManager
{
private:

	static const float camAnimDefaultValF;

public:

	static inline bool Dbg_isPostFiring = false;
	//static void updateAnimCamAmount();
	

	static inline int Dbg_updateAnimCamAmountCondRef = -1;

	//! we can't be on a timer here anymore as we need to update this value very often as we realised the cam anim value is used for recoil, headbob and potentially many other things so we have to update it as often as possible.
	//static void updateAnimCamAmount_OnTimer(idPlayer* idPlayerPtr, uint64_t updateFreqsMs);

	//static std::string getDgbStrForImgui();

	static void updateAnimCamAmount(idPlayer* idPlayerPtr);
	static void updateAnimCamAmountV2(idPlayer* idPlayerPtr);
	static std::string animCamChangeReasonStr(AnimCamAmountChangeReson value);
	static std::string getAnimCamAmountDbgStrForImgui();
};

