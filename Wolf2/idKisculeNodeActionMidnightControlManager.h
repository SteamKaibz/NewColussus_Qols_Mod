#pragma once


#include "../MemHelper/MemHelper.h"



class idKisculeManager
{
private:
	//static __int64 m_idKisculeGraphNodeDefinitionVtb;
	//static __int64 m_idKisculeNodeActionMidnightControlVtb;
	static __int64 m_currentidKisculeNodeActionMidnightControlThisPtr;
	//static __int64 m_idKisculeNodeActionMidnightControlControlVtb;

public:

	/*static bool acquireVtb(__int64 Vtb);
	static __int64 getVtb();*/
	static void aquirreCurrentIdKisculeNodeActionMidnightControlThisPtr(__int64 ptr);
	static void skipToNextScene(); //? crash
	static void stopMidnight(); //? crash
};

