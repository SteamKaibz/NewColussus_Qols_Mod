#pragma once

#include "../MemHelper/MemHelper.h"



class idEngineLocalManager
{
private:

	static __int64 m_idEngineLocalPtr;
	static bool m_debugLastIsGameActive;

public:

	static __int64 getidEngineLocalPtr();
	static __int64 getIdRenderSystemLocal();
	static __int64 getTypeInfoToolPtr();
	static __int64 getidCmdSystemLocalPtr();
	static __int64 getidCVarSystemLocalPtr();
	static bool acquireidEngineLocalPtr(__int64 idEngineLocalPtr);

	static bool isGameActive();

};

