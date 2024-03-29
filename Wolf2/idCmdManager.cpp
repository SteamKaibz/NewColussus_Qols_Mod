#include "idCmdManager.h"

__int64 idCmdManager::m_idCmdSystemLocalAddr = 0;
__int64 idCmdManager::m_idCmdExecuteFuncAddr = 0;

bool idCmdManager::acquireIdCmdSystemLocalPtr(__int64 idCmdSystemLocalPtr) {
	if (MemHelper::isBadReadPtr((void*)idCmdSystemLocalPtr)) {
		logErr("acquireidCmdSystemLocalPtr: failed to handleChange idCmdSystemLocalPtr (bad ptr): %p", (void*)idCmdSystemLocalPtr);
		m_idCmdSystemLocalAddr = 0;
		return false;
	}
	__int64 idCmdSystemLocalAddr = *(__int64*)idCmdSystemLocalPtr;
	if (MemHelper::isBadReadPtr((void*)idCmdSystemLocalAddr)) {
		logErr("acquireidCmdSystemLocalPtr: failed to handleChange idCmdSystemLocalAddr (bad ptr): %p", (void*)idCmdSystemLocalAddr);
		m_idCmdSystemLocalAddr = 0;
		return false;
	}
	m_idCmdSystemLocalAddr = idCmdSystemLocalAddr;
	logInfo("acquireidCmdSystemLocalPtr: Succes acquirring idCmdSystemLocalAddr, m_idCmdSystemLocalAddr: %p", (void*)m_idCmdSystemLocalAddr);
	return true;

}

bool idCmdManager::acquireIdCmdExecuteFuncAddr(__int64 funcAddr)
{
	if (MemHelper::isBadReadPtr((void*)funcAddr)) {
		logErr("acquireIdCmdExecuteFuncAddr: failed to handleChange funcAddr (bad ptr): %p", (void*)funcAddr);
		m_idCmdExecuteFuncAddr = 0;
		return false;
	}
	m_idCmdExecuteFuncAddr = funcAddr;
	return true;
}


void idCmdManager::executeCmd(std::string cmdStr) {
	//logInfo("debug executeCmd 1");

	if (MemHelper::isBadReadPtr((void*)m_idCmdSystemLocalAddr)) {
		logErr("executeCmd: m_idCmdSystemLocalAddr is bad ptr: %p returning", (void*)m_idCmdSystemLocalAddr);
		return;
	}
	if (!m_idCmdExecuteFuncAddr) {
		logErr("executeCmd: m_idCmdExecuteFuncAddr is null returning");
		return;
	}
	logInfo("executeCmd: m_idCmdExecuteFuncAddr: %p", (void*)m_idCmdExecuteFuncAddr);
	auto execCmdFunc = reinterpret_cast<idCmdSystemLocal__ExecuteCmd>(m_idCmdExecuteFuncAddr);
	auto result = execCmdFunc(m_idCmdSystemLocalAddr, cmdStr.c_str());
	//logInfo("debug executeCmd 2");

}

//void idCmdManager::testCmd(std::string cmdStr)
//{
//	__int64 idCmdSystemLocal = MemHelper::getAddr(0x4104420);
//	if (MemHelper::isBadReadPtr((void*)idCmdSystemLocal)) {
//		logErr("testCmd: idCmdSystemLocal is bad ptr: %p returning", (void*)idCmdSystemLocal);
//		return;
//	}
//	/*auto idCmdSystemLocal = *(__int64*)idCmdSystemLocalPtr;
//	if (MemHelper::isBadReadPtr((void*)idCmdSystemLocal)) {
//		logErr("testCmd: idCmdSystemLocal is bad ptr: %p returning", (void*)idCmdSystemLocal);
//		return;
//	}*/
//	logInfo("testCmd: idCmdSystemLocal: %p", (void*)idCmdSystemLocal);
//	//return;
//		
//	//auto execCmdFuncAddr = MemHelper::getAddr(0x1265150); // this is not cmd execute i think. Crash.
//	//auto execCmdFuncAddr = MemHelper::getAddr(0x1264D60); // vtbl + 0x40 just like DE. Crash.
//	auto execCmdFuncAddr = MemHelper::getAddr(0x12653E0); //! vtbl + 0x88. I thought it didn't output anything to the console but it actually does, i just needed to be in a level to have listInventory work for example.
//	if (MemHelper::isBadReadPtr((void*)execCmdFuncAddr)) {
//		logErr("testCmd: execCmdFuncAddr is bad ptr: %p returning", (void*)execCmdFuncAddr);
//		return;
//	}
//	auto execCmdFunc = reinterpret_cast<idCmdSystemLocal__ExecuteCmd>(execCmdFuncAddr);
//	auto result = execCmdFunc(idCmdSystemLocal, cmdStr.c_str());
//	logInfo("testCmd: result: %p", (void*)result);
//	/*auto cvarSys = reinterpret_cast<idCVarSystemLocal__FindInternal>(getCvarFuncAddr);
//	idCVar* cvarPtr = (idCVar*)(cvarSys(cvarSystem, cvarStr.c_str()));*/
//	
//
//}

void idCmdManager::findDecription(std::string cmdStr)
{
	//! result: matches @ 0x4104420, sig direct: 18 86 E6 3B F7 7F
	__int64 idCmdSystemLocal = MemHelper::getAddr(0x4104420);
	if (MemHelper::isBadReadPtr((void*)idCmdSystemLocal)) {
		logErr("findDecription: idCmdSystemLocal is bad ptr: %p returning", (void*)idCmdSystemLocal);
		return;
	}	
	logInfo("findDecription: idCmdSystemLocal: %p", (void*)idCmdSystemLocal);
	
	//! result: matches @ 0x1264EB0, sig direct: 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 83 B9
	auto findDescriptionFuncAddr = MemHelper::getAddr(0x1264EB0);
	if (MemHelper::isBadReadPtr((void*)findDescriptionFuncAddr)) {
		logErr("testCmd: findDescriptionFuncAddr is bad ptr: %p returning", (void*)findDescriptionFuncAddr);
		return;
	}
	auto findDescriptionFunc = reinterpret_cast<findDescription_MB>(findDescriptionFuncAddr);
	auto result = findDescriptionFunc(idCmdSystemLocal, cmdStr.c_str());
	if (MemHelper::isBadReadPtr((void*)result)) {
		logErr("testCmd: result is bad ptr: %p returning", (void*)result);
		return;
	}
	logInfo("findDecription: result: %s", result);
}

void idCmdManager::listAllCmds()
{
	//! result: matches @ 0x4104420, sig direct: 18 86 E6 3B F7 7F
	__int64 idCmdSystemLocal = MemHelper::getAddr(0x4104420);
	if (MemHelper::isBadReadPtr((void*)idCmdSystemLocal)) {
		logErr("findDecription: idCmdSystemLocal is bad ptr: %p returning", (void*)idCmdSystemLocal);
		return;
	}
	logInfo("findDecription: idCmdSystemLocal: %p", (void*)idCmdSystemLocal);

	__int64 v3 = 0x28i64;
	if (!*(DWORD*)(idCmdSystemLocal + 0x200B8))
		v3 = 8i64;
	if (!(*(int*)(v3 + idCmdSystemLocal + 8) > 0)) {
		//! check inspiration func: 0x1264EB0 for more context
		logErr("listAllCmds: code error relative to original func, returning");
		return;
	}


}

void idCmdManager::listAllCmdsV2()
{
	std::vector<CmdData> results; // Create a vector to store the results
	//! result: matches @ 0x4104420, sig direct: 18 86 E6 3B F7 7F
	__int64 idCmdSystemLocal = MemHelper::getAddr(0x4104420);
	if (MemHelper::isBadReadPtr((void*)idCmdSystemLocal)) {
		logErr("listAllCmdsV2: idCmdSystemLocal is bad ptr: %p returning", (void*)idCmdSystemLocal);
		return;
	}
	logInfo("listAllCmdsV2: idCmdSystemLocal: %p", (void*)idCmdSystemLocal);
		

	__int64 v3 = (*(DWORD*)(idCmdSystemLocal + 0x200B8) != 0) ? 0x28i64 : 8i64;
	int numElements = *(int*)(v3 + idCmdSystemLocal + 8);
	logInfo("listAllCmdsV2: numElements: %d", numElements);
	__int64 cmdListAddr = *(__int64*)(v3 + idCmdSystemLocal);
	//char*** v4 = *(char****)(v3 + idCmdSystemLocal);

	for (int i = 0; i < numElements; ++i) {

		if (MemHelper::isBadReadPtr((void*)cmdListAddr)) {
			logErr("listAllCmdsV2: found bad ptr: %p breaking", (void*)cmdListAddr);
			break;
		}
		__int64 CmdDataPtr = *(__int64*)cmdListAddr;
		CmdData result = *(CmdData*)CmdDataPtr;
		results.push_back(result);
		cmdListAddr += 8;
	}

	logInfo("listAllCmdsV2: found %zu CmdData results: ", results.size());
	for (size_t i = 0; i < results.size(); i++)
	{
		__int64 funcOffset = (uintptr_t)results[i].callBackPtr - MemHelper::getModuleBaseAddr();
		logInfo("name: %s callFuncPtr offset: %p", results[i].name, (void*)funcOffset);
	}
	
}

//? this crashes which is not surprising.
__int64 idCmdManager::mdnt_list_active_F69400() {

	logInfo("mdnt_list_active_F69400");

	_QWORD* v0; // r12
	__int64 v1; // rcx
	__int64 result; // rax
	__int64 v3; // r13
	unsigned int v4; // ebp
	__int64 v5; // r15
	__int64 v6; // r14
	unsigned int v7; // edi
	//__int64(__fastcall * **v9)(_QWORD); // rax
	//__int64(__fastcall * **v10)(_QWORD); // rbx
	__int64 i; // [rsp+68h] [rbp+10h]
	__int64 v14; // [rsp+70h] [rbp+18h]

	// Access the TEB (Thread Environment Block)
	auto teb = NtCurrentTeb();

	// Calculate the address of ThreadLocalStoragePointer
	ULONGLONG* tlsPointer = (ULONGLONG*)((BYTE*)teb + 0x58);

	// Calculate the address of the TLS slot (adjust the offset as needed)
	ULONGLONG* tlsSlot = (ULONGLONG*)(*tlsPointer + 0x8i64);

	v0 = tlsSlot;
	v1 = *tlsSlot;
	result = *(_QWORD*)(v1 + 0x108);
	v14 = result + 0x10i64 * *(int*)(v1 + 0x110);

	for (i = result; result != v14; i = result)
	{
		v3 = *(_QWORD*)(result + 8);
		logInfo("- '%s' (%d)\n", *(const char**)(*(_QWORD*)(v3 + 8) + 8i64), *(unsigned int*)(v3 + 0xE8));
		v4 = 0;
		if (*(int*)(v3 + 0xE8) > 0)
		{
			v5 = 0i64;
			do
			{
				v6 = v5 + *(_QWORD*)(v3 + 0xE0);
				logInfo("%2d # %s (%d)\n", v4, *(const char**)v6, *(unsigned int*)(v6 + 0x18));
				v7 = 0;
				
				++v4;
				v5 += 0x50i64;
			} while ((signed int)v4 < *(DWORD*)(v3 + 0xE8));
		}
		result = i + 0x10;
	}

	return result;
}