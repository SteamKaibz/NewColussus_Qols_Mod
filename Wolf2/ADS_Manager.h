#pragma once
#include <vector>
#include "../MemHelper/MemHelper.h"
#include "../MemHelper/Patcher.h"
#include "../ModSettings/ModSettingsManager.h"


//#include "MemHelper/Patcher.h"
//#include "ModSettings/ModSettingsManager.h"




enum AdsZoomCheckInstructionState {
	zoomCodeUnknown,
	zoomCodeOriginal,
	zoomCodePatched
};

//! handles ADS key toggle system is user has enabled it in the options 
class ADS_Manager
{

private:

	static AdsZoomCheckInstructionState m_zoomInstructionState;
	static __int64 m_zoomBtnReleaseCheckAddr;
	static bool m_isToggleFlag;
	static bool m_isZoomInTrigger;
	static bool m_isZoomBtnReleasedFlag;


public:

	static bool acquireZoomBtnReleaseInsctructionAddr(__int64 instructAddr);

	static void checkZoomBtnState();

	static void reset();

	static void raiseToggleFlag();

	static bool isToggleFlag();

	static void Toggle(bool isInScope);

	//! these will patch instructions
	static void restoreZoomBtnReleaseCheck();
	static void preventZoomBtnReleaseCheck();

	static AdsZoomCheckInstructionState getPatchState();

};


//.text:0000000000FED0D6 D1 E8                                         shr     eax, 1
//.text : 0000000000FED0D8 A8 01                                         test    al, 1
//.text : 0000000000FED0DA 74 2B                                         jz      short loc_FED107
static const std::vector<unsigned char> ZoomBtnReleaseCheckInstructionVec = { 0xD1, 0xE8, 0xA8, 0x01, 0x74, 0x2B };
static const std::vector<unsigned char> PreventZoomBtnReleaseNewInstructionVec = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
