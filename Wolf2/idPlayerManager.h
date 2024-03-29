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

public:
	static idHudInfo* getIdHudInfo();
	static void handleChange(idPlayer* idPlayerPtr);
};

