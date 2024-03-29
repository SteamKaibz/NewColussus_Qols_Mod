#pragma once


#include "../MemHelper/MemHelper.h"


enum loadScreenState {
	Unknow,
	Active,
	NotActive
};


/// <summary>
/// this could be used as a way to detect if we are in loadscreen or not, as many times before we had crashes during loadscreen.
/// </summary>
class idLoadScreenManager
{

private :
	//! i know it's related but can't get actual naming/typeinfo
	static __int64 m_loadScreenRelatedPtr;

	//! ptr to renderWorld which will be null during loadscreen AND until we press 'F to continue'
	static const int m_renderWorlPtrOffset;

	//! when we are in loading screen there is a ptr to a renderModelGui related to loadscreen, when out of loadscreen it is null
	static const int m_renderModelGuiLoadScreenPtrOffset;

public:

	static bool acquireIdLoadScreenRelatedPtr(__int64 addr);

	static loadScreenState getLoadScreenState();


};

