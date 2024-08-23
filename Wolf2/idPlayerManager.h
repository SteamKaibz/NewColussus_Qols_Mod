#pragma once
#include "GeneratedClasses.h"
#include "timescaleManager.h"
#include "idGameLocalManager.h"



/// <summary>
/// just a way to check mainly if idPlayer has changed.
/// </summary>
class idPlayerManager
{
private:
	static idPlayer* m_lastIdPlayerPtr;
	static inline uint64_t last_com_adaptiveTickCmdSetMs = 0;

public:
	static idHudInfo* getIdHudInfo();
	static idPlayer_animSysEvents_t getPreMoveEvent();
	
	//! band aid system to fix the issue where player will bet stuck by very small obstacles if framerate is higher than 60
	static void triggerHighFramerateMvtFix();
	static void checkForHighFramerateMvtFixTimerEnd();

	static void handleChange(idPlayer* idPlayerPtr);
};

