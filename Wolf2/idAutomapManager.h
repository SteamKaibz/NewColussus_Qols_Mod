#pragma once

#include "../MemHelper/Patcher.h"



class idAutomapManager
{
private:
	//! result: matches @ 0x4DA599, sig direct: C7 81 ? ? ? ? ? ? ? ? 44 88 B9	
	//! orig: C7 81 68 02 00 00 00 00 80 41 
	//! new:  C7 81 68 02 00 00 00 00 00 41     mov     dword ptr [rcx+268h], 41000000h
	

	static const std::vector<unsigned char> m_setDefaultZoomToMinVec;
	static const std::vector<unsigned char> m_setDefaultZoomToOrigValueVec;

public:

	static void setAutoMapDefaultZoomToMinZoom(bool isSetToMaxZoom);

};

