#pragma once

#include <Windows.h>
#include <string>
#include "../Config/Config.h"
#include "../MemHelper/MemHelper.h"

using _QWORD = unsigned  long long;

//! __int64 __fastcall idCmdSystemLocal__ExecuteCmd_1265150(__int64 a1, unsigned int *a2)
//typedef __int64(__fastcall* idCVarSystemLocal__FindInternal)(__int64 addr, const char* a2);
typedef __int64(__fastcall* idCmdSystemLocal__ExecuteCmd)(__int64 addr, const char* a2);

//  find cmd description
//! const char *__fastcall sub_1264EB0(__int64 a1, char *a2)
typedef const char* (__fastcall*findDescription_MB)(__int64 a1, const char* a2);

struct CmdData {
	const char* name;
	void* callBackPtr;
	const char* description;
};

class idCmdManager
{
private:
	static __int64 m_idCmdSystemLocalAddr;
	static __int64 m_idCmdExecuteFuncAddr;
	

public:

	static bool acquireIdCmdSystemLocalPtr(__int64 idCmdSystemLocalPtr);
	static bool acquireIdCmdExecuteFuncAddr(__int64 funcAddr);

	static void executeCmd(std::string cmdStr);

	//void testCmd(std::string cmdStr);
	void findDecription(std::string cmdStr);
	void listAllCmds(); // names and callbacks
	void listAllCmdsV2();
	__int64 mdnt_list_active_F69400();
};

