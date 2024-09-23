#include "Debug.h"


std::vector<__int64> Debug::m_idRenderModelGuiPtrsVec = {};


std::string Debug::getCurrentMovementModeStr(){
	auto idplayer = idGameLocalManager::getIdPlayer();
	if (MemHelper::isBadReadPtr(idplayer)) {
		return "Current Movement: BAD PTR";
	}
	char* idplayerCharPtr = (char*)idplayer;
	char* idPlayerVolatile = idplayerCharPtr + 0x4EE0;
	int curMovement = *(int*)(idPlayerVolatile + 0x8E4);
	return "Current Movement index: " + std::to_string(curMovement);

}


std::string movementModeToString(int mode) {
	switch (mode) {
	case MOVEMENT_MODE_STANDING: return "MOVEMENT_MODE_STANDING";
	case MOVEMENT_MODE_CROUCHED: return "MOVEMENT_MODE_CROUCHED";
	case MOVEMENT_MODE_WANDERER: return "MOVEMENT_MODE_WANDERER";
	case MOVEMENT_MODE_GROUNDCOMBAT: return "MOVEMENT_MODE_GROUNDCOMBAT";
	case MOVEMENT_MODE_CRAWLSPACE: return "MOVEMENT_MODE_CRAWLSPACE";
	case MOVEMENT_MODE_ACTIVATION: return "MOVEMENT_MODE_ACTIVATION";
	case MOVEMENT_MODE_ACTIVATION_EXIT: return "MOVEMENT_MODE_ACTIVATION_EXIT";
	case MOVEMENT_MODE_JUMPING_OVER_STUFF: return "MOVEMENT_MODE_JUMPING_OVER_STUFF";
	case MOVEMENT_MODE_PRONE: return "MOVEMENT_MODE_PRONE";
	case MOVEMENT_MODE_LADDER: return "MOVEMENT_MODE_LADDER";
	case MOVEMENT_MODE_MIDNIGHT_LIMITVIEW_NARROW: return "MOVEMENT_MODE_MIDNIGHT_LIMITVIEW_NARROW";
	case MOVEMENT_MODE_MIDNIGHT_LIMITVIEW_WIDE: return "MOVEMENT_MODE_MIDNIGHT_LIMITVIEW_WIDE";
	case MOVEMENT_MODE_MIDNIGHT_TAKEDOWN: return "MOVEMENT_MODE_MIDNIGHT_TAKEDOWN";
	case MOVEMENT_MODE_WARTABLE: return "MOVEMENT_MODE_WARTABLE";
	case MOVEMENT_MODE_MIDNIGHT_KAMPFHUND_CLINCH: return "MOVEMENT_MODE_MIDNIGHT_KAMPFHUND_CLINCH";
	case MOVEMENT_MODE_PLAYERCONTROLLED: return "MOVEMENT_MODE_PLAYERCONTROLLED";
	case MOVEMENT_MODE_SWIMMING_UNDER_SURFACE: return "MOVEMENT_MODE_SWIMMING_UNDER_SURFACE";
	case MOVEMENT_MODE_SPRINT_SLIDE: return "MOVEMENT_MODE_SPRINT_SLIDE";
	case MOVEMENT_MODE_WHEELCHAIR: return "MOVEMENT_MODE_WHEELCHAIR";
	case MOVEMENT_MODE_WHEELCHAIR_ARMED: return "MOVEMENT_MODE_WHEELCHAIR_ARMED";
	case MOVEMENT_MODE_FIRE_EXTINGUISHER: return "MOVEMENT_MODE_FIRE_EXTINGUISHER";
	case MOVEMENT_MODE_HEAD_IN_A_JAR: return "MOVEMENT_MODE_HEAD_IN_A_JAR";
	case MOVEMENT_MODE_TURRET: return "MOVEMENT_MODE_TURRET";
	case MOVEMENT_MODE_PERISCOPE: return "MOVEMENT_MODE_PERISCOPE";
	case MOVEMENT_MODE_GROUND_POUND: return "MOVEMENT_MODE_GROUND_POUND";
	case MOVEMENT_MODE_LEVER: return "MOVEMENT_MODE_LEVER";
	case MOVEMENT_MODE_MIDNIGHT_TAKEDOWN_WHEELCHAIR: return "MOVEMENT_MODE_MIDNIGHT_TAKEDOWN_WHEELCHAIR";
	case MOVEMENT_MODE_SWIMMING_ON_SURFACE: return "MOVEMENT_MODE_SWIMMING_ON_SURFACE";
	case MOVEMENT_MODE_NUM: return "MOVEMENT_MODE_NUM";
	default: return "Unknown Movement Mode";
	}
}



void Debug::AddidRenderModelGuiPtrInStretchPicFuncToVec(__int64 idRenderModelGuiPtr) {

	for (size_t i = 0; i < m_idRenderModelGuiPtrsVec.size(); i++)
	{
		if (idRenderModelGuiPtr == m_idRenderModelGuiPtrsVec[i]) return;
	}
	m_idRenderModelGuiPtrsVec.push_back(idRenderModelGuiPtr);
}

void Debug::printidRenderModelGuiPtrs() {
	logInfo("printidRenderModelGuiPtrs: ");
	for (size_t i = 0; i < m_idRenderModelGuiPtrsVec.size(); i++)
	{
		__int64 ptr = m_idRenderModelGuiPtrsVec[i];
		if (!MemHelper::isBadReadPtr((void*)ptr)) {
			__int64 nameAddr = ptr + 0x48;
			if (!MemHelper::isBadReadPtr((void*)nameAddr)) {
				const char* nameStr = *(const char**)(nameAddr);		
				logInfo("ptr: %p name: %s", (void*)ptr, nameStr);
			}
		}
	}
}

int Debug::gethudStateFlagsInt() {
	auto idplayer = idGameLocalManager::getIdPlayer();
	if (MemHelper::isBadReadPtr(idplayer)) {
		return -1;
	}
	char* idplayerCharPtr = (char*)idplayer;
	char* idPlayerVolatile = idplayerCharPtr + 0x4EE0;
	auto idHudInfoAddr = idPlayerVolatile + 0x7718;
	auto idPlayerHudAddr = idPlayerVolatile + 0x3BC0;


	auto hudGameFlagsAddr = idPlayerHudAddr + 0x18;
	if (!MemHelper::isBadReadPtr((void*)hudGameFlagsAddr)) {
		return *(int*)hudGameFlagsAddr;
	}
	else {
		return -1;
	}

}


std::string Debug::getHUDFlagsString(int hudFlags) {
	std::stringstream ss;

	if (hudFlags == HUDFLAG_NONE) ss << "HUDFLAG_NONE\n";
	if (hudFlags & HUDFLAG_FADEOUTHUD) ss << "HUDFLAG_FADEOUTHUD\n";
	if (hudFlags & HUDFLAG_FADEINHUD) ss << "HUDFLAG_FADEINHUD\n";
	if (hudFlags & HUDFLAG_FADEDOUT) ss << "HUDFLAG_FADEDOUT\n";
	if (hudFlags & HUDFLAG_FADEDIN) ss << "HUDFLAG_FADEDIN\n";
	if (hudFlags & HUDFLAG_FADERESET) ss << "HUDFLAG_FADERESET\n";
	if (hudFlags & HUDFLAG_FADEACC) ss << "HUDFLAG_FADEACC\n";
	if (hudFlags & HUDFLAG_DELAYED) ss << "HUDFLAG_DELAYED\n";
	if (hudFlags & HUDFLAG_HIDECROSSHAIR) ss << "HUDFLAG_HIDECROSSHAIR\n";
	if (hudFlags & HUDFLAG_HIDEUSEBUTTON) ss << "HUDFLAG_HIDEUSEBUTTON\n";
	if (hudFlags & HUDFLAG_HIDEHEALTHARMOR) ss << "HUDFLAG_HIDEHEALTHARMOR\n";
	if (hudFlags & HUDFLAG_HIDEWPNWHEEL) ss << "HUDFLAG_HIDEWPNWHEEL\n";
	if (hudFlags & HUDFLAG_HIDEWEAPONAMMO) ss << "HUDFLAG_HIDEWEAPONAMMO\n";
	if (hudFlags & HUDFLAG_HIDEGRENADEAMMO) ss << "HUDFLAG_HIDEGRENADEAMMO\n";
	if (hudFlags & HUDFLAG_HIDETHROWWPNAMMO) ss << "HUDFLAG_HIDETHROWWPNAMMO\n";
	if (hudFlags & HUDFLAG_HIDECOMBATHUD) ss << "HUDFLAG_HIDECOMBATHUD\n";
	if (hudFlags & HUDFLAG_HIDECOMBATHUD_PH) ss << "HUDFLAG_HIDECOMBATHUD_PH\n";
	if (hudFlags & HUDFLAG_SHOWINFONOT) ss << "HUDFLAG_SHOWINFONOT\n";
	if (hudFlags & HUDFLAG_NOTAPPLIED) ss << "HUDFLAG_NOTAPPLIED\n";
	if (hudFlags & HUDFLAG_INTERACT_TUTORIAL) ss << "HUDFLAG_INTERACT_TUTORIAL\n";
	if (hudFlags & HUDFLAG_TIMER) ss << "HUDFLAG_TIMER\n";
	if (hudFlags & HUDFLAG_SHOWCHALLENGEHUD) ss << "HUDFLAG_SHOWCHALLENGEHUD\n";
	if (hudFlags & HUDFLAG_SHOWSCORE) ss << "HUDFLAG_SHOWSCORE\n";
	if (hudFlags & HUDFLAG_SHOWHINTFADEIN) ss << "HUDFLAG_SHOWHINTFADEIN\n";
	if (hudFlags & HUDFLAG_SHOWHINTFADEOUT) ss << "HUDFLAG_SHOWHINTFADEOUT\n";
	if (hudFlags & HUDFLAG_SWEEPMARKER) ss << "HUDFLAG_SWEEPMARKER\n";
	if (hudFlags & HUDFLAG_FLAGSPROCESSED) ss << "HUDFLAG_FLAGSPROCESSED\n";
	if (hudFlags & HUDFLAG_SHOWADDHEALTHBAR) ss << "HUDFLAG_SHOWADDHEALTHBAR\n";
	if (hudFlags & HUDFLAG_HIDESUBTITLES) ss << "HUDFLAG_HIDESUBTITLES\n";
	if (hudFlags & HUDFLAG_HIDERESTOFHUD) ss << "HUDFLAG_HIDERESTOFHUD\n";
	if (hudFlags & HUDFLAG_FREEZE_OPTIONS) ss << "HUDFLAG_FREEZE_OPTIONS\n";
	if (hudFlags & HUDFLAG_FREEZE_OPTIONS_RESET) ss << "HUDFLAG_FREEZE_OPTIONS_RESET\n";
	return ss.str();
}

void Debug::printPlayerInfoOnKeyPress() {
	auto idplayer = idGameLocalManager::getIdPlayer();
	if (MemHelper::isBadReadPtr(idplayer)) {
		logErr("PrintIdPlayerInfo: idplayer is bad ptr returning");
		return;
	}
	char* idplayerCharPtr = (char*)idplayer;
	char* idPlayerVolatile = idplayerCharPtr + 0x4EE0;
	auto idHudInfoAddr = idPlayerVolatile + 0x7718;
	auto idHudReticleInfoAddr = idHudInfoAddr + 0x930;
	auto scopedEventFlagsAddr = idPlayerVolatile + 0x890;


	logInfo("idPlayer::idPlayerVolatile addr: %p", (idPlayerVolatile));
	logInfo("idPlayer::idPlayerVolatile: controlledEntities addr: %p", (idPlayerVolatile + 0x9B78));
	logInfo("idPlayer::idPlayerVolatile: idPlayerHud addr: %p", (idPlayerVolatile + 0x3BC0));
	logInfo("idPlayer::idPlayerVolatile: idHudInfo addr: %p", (idPlayerVolatile + 0x7718));
	logInfo("idPlayer::idPlayerVolatileUnsaved addr: %p", (idplayerCharPtr + 0x20380));

	logInfo("idEntity:playerController addr: %p", (idplayerCharPtr + 0x310));
	logInfo("idEntity:midnightHandle addr: %p", (idplayerCharPtr + 0x848));

	logInfo("scopedEventFlagsAddr : %p", (scopedEventFlagsAddr));

	auto gameIntroActiveAddr = idHudInfoAddr + 0x5AE;
	if (!MemHelper::isBadReadPtr((void*)gameIntroActiveAddr)) {
		bool gameIntroActive = *(bool*)(gameIntroActiveAddr);
		if (gameIntroActive) {
			logInfo("gameIntro is Active");
		}
		else {
			logInfo("gameIntro NOT Active");
		}
	}

	auto reticleFlagAddr = idHudReticleInfoAddr + 0x28;
	if (!MemHelper::isBadReadPtr((void*)reticleFlagAddr)) {
		int reticleFlags = *(int*)reticleFlagAddr;
		logInfo("reticleFlags: %d", reticleFlags);
	}

	auto targetIndicationAddr = idHudReticleInfoAddr + 0x64;
	if (!MemHelper::isBadReadPtr((void*)targetIndicationAddr)) {
		float targetIndicationf = *(float*)targetIndicationAddr;
		logInfo("targetIndicationf: %.2f", targetIndicationf);
	}


	
}


void Debug::printLivePlayerInfo()
{
	static int lasthudFlags = -1;
	static int lasthudState = -1;
	static int lasthudScriptFlag = -1;
	static int lasthudGameFlag = -1;
	static byte lastplayerInhibited = 0;
	static byte lastgameIntroActive = 0;
	static byte lastrenderingUseIcon = 0;
	static byte lastIsInCombat = -1;
	static int lasthudStateFlagsV2 = -1;


	auto idplayer = idGameLocalManager::getIdPlayer();
	if (MemHelper::isBadReadPtr(idplayer)) {
		return;
	}
	char* idplayerCharPtr = (char*)idplayer;
	char* idPlayerVolatile = idplayerCharPtr + 0x4EE0;
	auto idHudInfoAddr = idPlayerVolatile + 0x7718;
	auto idPlayerHudAddr = idPlayerVolatile + 0x3BC0;





	auto hudStateFlagsAddr = idPlayerHudAddr + 0x1C;
	if (!MemHelper::isBadReadPtr((void*)hudStateFlagsAddr)) {
		int hudStateFlagsV2 = *(int*)hudStateFlagsAddr;
		if (hudStateFlagsV2 != lasthudStateFlagsV2) {
			lasthudStateFlagsV2 = hudStateFlagsV2;
			auto stateStr = getHUDFlagsString(lasthudStateFlagsV2);
			logInfo("printLivePlayerInfo: hudStateFlagsV2 has changed to: %s", stateStr.c_str());
		}
	}
	

	
}



