#include "MemHelper.h"



bool MemHelper::isGameFileNameValid(std::string gameFileNameToLower)
{
	std::string exeNameToLower = GetGameExeNameToLower();
	if (exeNameToLower != gameFileNameToLower) {
		logErr("MemHelper::isGameFileNameValid(): wrong module name, was expecting %s got: %s.", gameFileNameToLower.c_str(), exeNameToLower.c_str());
		return false;
	}
	return true;
}

std::string MemHelper::basename(std::string const& pathname)
{
	return std::string(
		std::find_if(pathname.rbegin(), pathname.rend(),
			MatchPathSeparator()).base(),
		pathname.end()); 
}

std::string MemHelper::GetGameExeNameToLower()
{
	const int fnLenMax = 200;
	char fnPtr[fnLenMax];
	auto fnLen = GetModuleFileNameA(0, fnPtr, fnLenMax);

	auto fileName = basename(std::string(fnPtr, fnLen));
	std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);
	return fileName;	
}


//? 20/9/24 adding check for build type to make the mod more performant in release build. especially for gui stuffs.
bool MemHelper::isBadReadPtr(void* ptr) {

//! macro defined only for the default Debug build.
#ifdef _DEBUG
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	if (::VirtualQuery(ptr, &mbi, sizeof(mbi)))
	{
		DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
		bool b = !(mbi.Protect & mask);
		// check the page is not a guard page
		if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;

		return b;
	}
	return true;
#else
	return ptr == nullptr;
#endif

}


//bool MemHelper::isBadReadPtr(void* ptr)
//{
//	MEMORY_BASIC_INFORMATION mbi = { 0 };
//	if (::VirtualQuery(ptr, &mbi, sizeof(mbi)))
//	{
//		DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
//		bool b = !(mbi.Protect & mask);
//		if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;
//
//		return b;
//	}
//	return true;
//}

uintptr_t MemHelper::getModuleBaseAddr() {
	logDebug("getModuleBaseAddr");

	return (uintptr_t)GetModuleHandle(NULL);

}

uintptr_t MemHelper::getFuncAddr(uintptr_t offset) {

	return (getModuleBaseAddr() + offset);
}

uintptr_t MemHelper::getAddr(uintptr_t offset)
{
	logDebug("getAddr");

	return (getModuleBaseAddr() + offset);
}


bool MemHelper::overwriteInstruction(std::string refStr, const uintptr_t instructionAddr, std::vector<unsigned char> newInstructionVec)
{
	logDebug("overwriteInstruction");
	if (isBadReadPtr((void*)instructionAddr)) {
		logErr("overwriteInstruction: %s :can not overwrite cause instructionAddr is bad ptr: %p", refStr.c_str(), (void*)instructionAddr);		
	}
	try
	{
		DWORD old_protection;
		VirtualProtect((LPVOID)instructionAddr, newInstructionVec.size(), PAGE_EXECUTE_READWRITE, &old_protection);

		memcpy((LPVOID)instructionAddr, newInstructionVec.data(), newInstructionVec.size());
	
		VirtualProtect((LPVOID)instructionAddr, newInstructionVec.size(), old_protection, &old_protection);

		logInfo("succes overwriting Instruction for %s at instructionAddr: %p", refStr.c_str(), (void*)instructionAddr);
		return true;
	}
	catch (const std::exception& ex)
	{
		logErr("overwriteInstruction: ERROR: %s %s overwrite has failed", refStr.c_str(), ex.what());
	}
	return false;
	
}

 bool MemHelper::overwriteInstructionIfNotEqual(std::string refStr, const uintptr_t instructionAddr, std::vector<unsigned char> newInstructionVec)
{

	if (isBadReadPtr((void*)instructionAddr)) {
		logErr("overwriteInstruction: %s :can not overwrite cause instructionAddr is a bad ptr: %p", refStr.c_str(), (void*)instructionAddr);
		return false;
	}
	try
	{
		std::vector<unsigned char> currentInstructionVec(newInstructionVec.size());
		memcpy(currentInstructionVec.data(), (LPVOID)instructionAddr, newInstructionVec.size());

		if (currentInstructionVec == newInstructionVec) {
			if (!refStr.empty()) {
				logInfo("Instruction for %s at instructionAddr: %p is already equal to the desired value, no overwrite needed.", refStr.c_str(), (void*)instructionAddr);
			}		
			return true;           
		}

		DWORD old_protection;
		VirtualProtect((LPVOID)instructionAddr, newInstructionVec.size(), PAGE_EXECUTE_READWRITE, &old_protection);

		memcpy((LPVOID)instructionAddr, newInstructionVec.data(), newInstructionVec.size());

		VirtualProtect((LPVOID)instructionAddr, newInstructionVec.size(), old_protection, &old_protection);

		if (!refStr.empty()) {
			logInfo("Successfully overwritten Instruction for %s at instructionAddr: %p", refStr.c_str(), (void*)instructionAddr);
		}		
		return true;
	}
	catch (const std::exception& ex)
	{
		logErr("overwriteInstructionIfNotEqual: ERROR: %s %s overwrite has failed", refStr.c_str(), ex.what());
	}
	return false;
}



bool MemHelper::isSameByteArrays(const BYTE* array1, const BYTE* array2, size_t length)
{
	logDebug("isSameByteArrays called ");
	return std::memcmp(array1, array2, length) == 0;
}






uintptr_t MemHelper::FindPtrAddress(uintptr_t addr, std::vector<unsigned int>& offsets)
{
	logDebug("FindPtrAddress");

	for (unsigned int i = 0; i < offsets.size(); i++) {
		if (isBadReadPtr((void*)addr)) {
			logWarn("MemHelper::FindPtrAddress: found BadReadPtr for addr: %p returning", (void*)addr);
			return 0;
		}
		addr = *(uintptr_t*)addr + offsets[i];
	}
	return addr;
}

__int64 MemHelper::FindPtrFromRelativeOffset(uintptr_t instructionStartAddress, const int instructionOffset, const int nextInstructionOffset) {
	logDebug("FindPtrFromRelativeOffset");

	logInfo("FindPtrFromRelativeOffset instructionStartAddress is %p", (void*)instructionStartAddress);
	__int64 relativeOffsetAddr = instructionStartAddress + instructionOffset;
	HANDLE hProcess = GetCurrentProcess();	
	uint8_t buffer[4];         	
	SIZE_T bytesRead;
	int relativeOffsetValue = 0;
	if (ReadProcessMemory(hProcess, (LPCVOID)relativeOffsetAddr, buffer, sizeof(buffer), &bytesRead)) {
		if (bytesRead == sizeof(buffer)) {
			int relativeOffsetValue = *reinterpret_cast<int*>(buffer);
			__int64 nextInstructionAddress = instructionStartAddress + nextInstructionOffset;
			__int64 ptr = nextInstructionAddress + relativeOffsetValue;
			logInfo("FindPtrFromRelativeOffset found ptr : %p", (void*)ptr);
			return ptr;
		}
		else {
			logErr("FindPtrFromRelativeOffset ReadProcessMemory did not read the expected number of bytes returning 0");
		}
	}
	else {
		logErr("FindPtrFromRelativeOffset Failed to read process memory. Error code: %d returning 0", GetLastError());
		
	}
	return 0;
}

int MemHelper::FindHardcodedOffset(uintptr_t instructionStartAddress, const int instructionOffset) {
	logDebug("FindHardcodedOffset");

	logInfo("FindHardcodedOffset instructionStartAddress is %p", (void*)instructionStartAddress);
	__int64 relativeOffsetAddr = instructionStartAddress + instructionOffset;
	HANDLE hProcess = GetCurrentProcess();
	uint8_t buffer[4];         	
	SIZE_T bytesRead;
	if (ReadProcessMemory(hProcess, (LPCVOID)relativeOffsetAddr, buffer, sizeof(buffer), &bytesRead)) {
		if (bytesRead == sizeof(buffer)) {
			int hardcodedOffset = *reinterpret_cast<int*>(buffer);
			logInfo("FindHardcodedOffset returning hardcodedOffset : 0x%X", hardcodedOffset);
			return hardcodedOffset;
		}
		else {
			logErr("FindHardcodedOffset ReadProcessMemory did not read the expected number of bytes returning 0");
		}
	}
	else {
		logErr("FindHardcodedOffset Failed to read process memory. Error code: %d returning 0", GetLastError());
	}
	return 0;

}


//! update 14/9/24 this should get rid of the "argument': conversion from 'unsigned long' to '_Ty', possible loss of data" build warning:
static auto pattern_to_byte = [](const char* pattern)
	{
		auto bytes = std::vector<char>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?')
					++current;
				bytes.push_back('\?');
			}
			else
			{
				// Cast the result of strtoul to char to avoid the warning
				bytes.push_back(static_cast<char>(strtoul(current, &current, 16)));
			}
		}
		return bytes;
	};


DWORD64 MemHelper::PatternScan(const char* szModule, const char* signature)
{
	logDebug("PatternScan");

	MODULEINFO mInfo;
	HMODULE hModule = GetModuleHandleA(szModule);

	if (hModule == nullptr)
	{
		logErr("GetModuleHandleA failed to find the module: %s returning", szModule);
		return 0;            
	}

	K32GetModuleInformation(GetCurrentProcess(), hModule, &mInfo, sizeof(MODULEINFO));
	DWORD64 base = (DWORD64)mInfo.lpBaseOfDll;
	DWORD64 sizeOfImage = (DWORD64)mInfo.SizeOfImage;
	auto patternBytes = pattern_to_byte(signature);

	DWORD64 patternLength = patternBytes.size();
	auto data = patternBytes.data();

	for (DWORD64 i = 0; i < sizeOfImage - patternLength; i++)
	{
		bool found = true;
		for (DWORD64 j = 0; j < patternLength; j++)
		{
			char a = '\?';
			char b = *(char*)(base + i + j);
			found &= data[j] == a || data[j] == b;
		}
		if (found)
		{
			DWORD64 result = base + i;
			logInfo("PatternScan Success. Found Addr: %p", (void*)result);
			return result;
		}
	}

	logErr("!!! PatternScan failed !!!");
	return 0;
}

//! New version 12/9/24
DWORD64 MemHelper::ModulePatternScan(std::string scanFriendlyName, const char* signature)
{

	MODULEINFO mInfo;
	//HMODULE hModule = GetModuleHandleA(Config::getCurrentModuleNameStrToLower().c_str());
	HMODULE hModule = GetModuleHandleA(GetGameExeNameToLower().c_str());

	if (hModule == nullptr)
	{
		logErr("ModulePatternScan: failed to find the module: %s returning", GetGameExeNameToLower().c_str());
		return 0;
	}

	K32GetModuleInformation(GetCurrentProcess(), hModule, &mInfo, sizeof(MODULEINFO));
	DWORD64 base = (DWORD64)mInfo.lpBaseOfDll;
	DWORD64 sizeOfImage = (DWORD64)mInfo.SizeOfImage;
	auto patternBytes = pattern_to_byte(signature);

	DWORD64 patternLength = patternBytes.size();
	const char* data = patternBytes.data();

	for (DWORD64 i = 0; i <= sizeOfImage - patternLength; i++)
	{
		const char* scanAddr = (const char*)(base + i);
		bool found = true;

		for (DWORD64 j = 0; j < patternLength; j++)
		{
			if (data[j] != '\?' && data[j] != scanAddr[j])
			{
				found = false;
				break; // Early exit on mismatch
			}
		}

		if (found)
		{
			DWORD64 result = (DWORD64)scanAddr;
			logInfo("ModulePatternScan: PatternScan Success for %s Found Addr: %p", scanFriendlyName.c_str(), (void*)result);
			return result;
		}
	}

	logErr("ModulePatternScan: !!! PatternScan failed for: %s", scanFriendlyName.c_str());
	return 0;
}


DWORD64 MemHelper::PatternScanForCurrentModule(const char* signature)
{
	logDebug("PatternScan");

	MODULEINFO mInfo;
	HMODULE hModule = GetModuleHandle(nullptr);

	if (hModule == nullptr)
	{
		logErr("GetModuleHandle failed to find the module");
		return 0;            
	}

	K32GetModuleInformation(GetCurrentProcess(), hModule, &mInfo, sizeof(MODULEINFO));
	DWORD64 base = (DWORD64)mInfo.lpBaseOfDll;
	DWORD64 sizeOfImage = (DWORD64)mInfo.SizeOfImage;
	auto patternBytes = pattern_to_byte(signature);

	DWORD64 patternLength = patternBytes.size();
	auto data = patternBytes.data();

	for (DWORD64 i = 0; i < sizeOfImage - patternLength; i++)
	{
		bool found = true;
		for (DWORD64 j = 0; j < patternLength; j++)
		{
			char a = '\?';
			char b = *(char*)(base + i + j);
			found &= data[j] == a || data[j] == b;
		}
		if (found)
		{
			DWORD64 result = base + i;
			logInfo("PatternScan Success. Found Addr: %p", (void*)result);
			return result;
		}
	}

	logErr("!!! PatternScan failed !!!");
	return 0;
}






