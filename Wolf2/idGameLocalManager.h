#pragma once

#include "../MemHelper/MemHelper.h"
#include "GeneratedClasses.h"




class idGameLocalManager
{
private:

	static __int64 m_idGameLocalPtr;
	static __int64 m_debuglastIdPlayerAdd;
	//static __int64 m_gameTimeSnapshot; //! using this just to be sure it will not crash the func pointer we use this for.

public:

	static bool acquireIdGameLocalPtr(__int64 idGameSystemLocalPtr);


	static idPlayer* getIdPlayer();
	static __int64 getIdWorldspawn();
	static __int64 getCurrentGameTime(); //! for auto pickup func
	static std::string getCurrentMapName();
};

