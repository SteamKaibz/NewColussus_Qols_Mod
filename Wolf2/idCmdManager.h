#pragma once

#include <Windows.h>
#include <string>
#include "../Config/Config.h"
#include "../MemHelper/MemHelper.h"
#include "idLib.h"
#include "../ModSettings/ModSettingsManager.h"


using _QWORD = unsigned  long long;

//! __int64 __fastcall idCmdSystemLocal__ExecuteCmd_1265150(__int64 a1, unsigned int *a2)
//typedef __int64(__fastcall* idCVarSystemLocal__FindInternal)(__int64 addr, const char* a2);
typedef __int64(__fastcall* idCmdSystemLocal__ExecuteCmd)(__int64 addr, const char* a2);

//  find cmd description
//! const char *__fastcall sub_1264EB0(__int64 a1, char *a2)
typedef const char* (__fastcall*findDescription_MB)(__int64 a1, const char* a2);

//? this is bs. what you want is commandDef_s
//struct CmdData {
//	const char* name;
//	void* callBackPtr;
//	const char* description;
//};

class idCmdManager
{
private:
	static __int64 m_idCmdSystemLocalAddr;
	static __int64 m_idCmdExecuteFuncAddr;

	static inline const float swf_safeFrameMax = 0.93f;
	

public:

	static bool acquireIdCmdSystemLocalPtr(__int64 idCmdSystemLocalPtr);
	static bool acquireIdCmdExecuteFuncAddr(__int64 funcAddr);

	static idList* getCmdlist();

	static void executeCmd(std::string cmdStr);

	static void executeCmd(std::string cmdStr, std::string argStr);

	static void init();

	static void setCriticalCvars();

	//static void setModInitCvars();

	//static void setCriticalCvars();

	static void setTimeScale(float timeScaleF);

	//void testCmd(std::string cmdStr);
	void findDecription(std::string cmdStr);
	//void listAllCmds(); // names and callbacks
	//void listAllCmdsV2();
	__int64 mdnt_list_active_F69400();
};

