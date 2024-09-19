#pragma once


#include "../MemHelper/MemHelper.h"
#include "idLib.h"


struct __declspec(align(8)) cvarCallback_t {
	//Offset 0x0,	 size 8
	struct idCallback* callback;
	//Offset 0x8,	 size 8
	cvarCallback_t* next;
};


struct __declspec(align(8)) idCVar {

	//Offset 0x0,	 size 48
	idStr valueString;
	//Offset 0x30,	 size 4
	int valueInteger;
	//Offset 0x34,	 size 4
	float valueFloat;
	//Offset 0x38,	 size 4 idTypesafeTime < float, secondUnique_t, 1 > valueSeconds;
	int valueSeconds;
	//Offset 0x3C,	 size 4
	//idTypesafeTime < int, millisecondUnique_t, 1000 > valueMilliseconds;
	int valueMilliseconds;
	//Offset 0x40,	 size 8
	//idTypesafeTime < long long, microsecondUnique_t, 1000000 > valueMicroseconds;
	long long valueMicroseconds;
	//Offset 0x48,	 size 8
	char* name;
	//Offset 0x50,	 size 8
	char* resetString;
	//Offset 0x58,	 size 8
	char* description;
	//Offset 0x60,	 size 4
	int flags;
	//Offset 0x64,	 size 4
	//! most of the time min/max vals are 0 but sometimes they're not like for swf_safeFrame.
	float valueMin;
	//Offset 0x68,	 size 4
	float valueMax;
	//Offset 0x70,	 size 8
	char** valueStrings;
	//Offset 0x78,	 size 8
	//void(idAutoComplete& autoComplete)* valueCompletion;
	void* valueCompletion;
	//Offset 0x80,	 size 8
	cvarCallback_t* onChange;
	//Offset 0x88,	 size 8
	idCVar* next;
};


typedef char(__fastcall* idInternalCVar__Set)(idCVar* a1, const char* a2, char a3);

//! __int64 __fastcall idCVarSystemLocal__FindInternalMB_1239700(__int64 a1, char* a2)
//typedef __int64(__fastcall* idCVarSystemLocal__FindInternal)(__int64 addr, const char* a2);

//! char __fastcall idInternalCVar::Set_MB_1239140(__int64 a1, char *a2, char a3)
//typedef char(__fastcall* idInternalCVar__Set)(idCVar* a1, const char* a2, char a3);

class idCvarManager
{

private:

	static __int64 m_idCVarSystemLocal;
	static __int64 m_idCVarSystemLocal_FindInternalFuncAddr;
	static __int64 m_idCVarSystemLocal_SetInternalFuncAddr;

	static idInternalCVar__Set m_setCvarFp;


	//static inline const float swf_safeFrameMax = 0.93f;
	static inline const float timeScaleMax = 50.0f; //! default max is 10 so we unlock it for faster game speed.

	


public:

	
	static bool acquireIdCVarSystemLocalPtr(__int64 add);
	static bool acquireFindInternalFuncPtr(__int64 funcAddr);
	static bool acquireSetInternalFuncAddr(__int64 funcAddr);

	static __int64 getCVarSystemLocal();

	static idList* getCVarlist();

	static idCVar* getCvarPtr(std::string cvarStr);

	static int getCvarInt(std::string cvarStr);

	static float getCvarFloat(std::string cvarStr);

	static std::string getCvarString(std::string cvarStr);

	//? not using this anymore as using a cmd is safer. i suppose the cmd actually triggers callbacks, sets the correct flags and such, which setCvar does not do.
	//static bool setCvar(std::string cvarStr, std::string val);

	//static bool setCvarFast(idCVar* cvar, const char* valStr);

	//static bool setModInitCvars();

	//! ensuring the mod works as it should. triggers when mod loads and when user exits the console.
	//static bool setCriticalCvars();

	

	static void init();

	static void setValueMaxFloat(const char* cvarName, float maxValue);

	//! has it's own method to make sure the max value has been updated
	//static void setSafeFrame(float safeFrameFloat);


	//static bool cacheCriticalCvars();

	//static float getFov();

	//void testGetCvar(std::string cvarStr);

	//void testWriteCvar(std::string cvarStr, std::string val);
	


};

