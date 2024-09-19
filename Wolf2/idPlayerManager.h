#pragma once
#include "GeneratedClasses.h"
#include "timescaleManager.h"
#include "idGameLocalManager.h"
#include "TypeInfoManager.h"



/// <summary>
/// just a way to check mainly if idPlayer has changed.
/// </summary>
class idPlayerManager
{
private:
	static idPlayer* m_lastIdPlayerPtr;
	static inline uint64_t last_com_adaptiveTickCmdSetMs = 0;

	//static inline bool m_isOffsetsInitialized = false;
	//static inline unsigned int m_idPlayerVolatileOffset = 0;

private:	

public:

	//static bool initOffsets();

	static idHudInfo* getIdHudInfo();
	static idPlayer_animSysEvents_t getPreMoveEvent();
	
	//! band aid system to fix the issue where player will bet stuck by very small obstacles if framerate is higher than 60
	static void triggerHighFramerateMvtFix();
	static void checkForHighFramerateMvtFixTimerEnd();
	static void handleChange(idPlayer* idPlayerPtr);	
	static bool isLeaning();

	static bool isDualWielding();
	static bool isDualWielding(idPlayer* idplayerPtr);

	//static bool isDualWielding();

	static std::string getAnimSysEventsDgbStrForImgui();	
	static void Dbg_LogPreMoveAdd();

};

