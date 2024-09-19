#pragma once

#include <Windows.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <psapi.h>
#include "../Config/Config.h"


struct MatchPathSeparator
{
	bool operator()(char ch) const
	{
		return ch == '\\' || ch == '/';
	}
};



const int monitoredWeaponMinIndex = 1;   
const int monitoredWeaponMaxIndex = 7;   

class MemHelper
{
private:
	uintptr_t m_idPlayerAddr = 0;
	__int64 m_idHud_WeaponInfoPtr = 0;

	const int m_iceNadeSelected = 1;
	const int m_normalNadeSelected = 2;
	

	

	static std::string basename(std::string const& pathname);
	static std::string GetGameExeNameToLower();



		
	std::vector<uintptr_t>m_ownedItemPtrsVec{};          
	std::vector<unsigned int>m_ownedGrenadeTypeIdsVec{};
	uintptr_t  m_idInventoryCollectionPtr = 0;
	const unsigned int m_inventoryMaxItemsCount = 256;                                          
	 
	uintptr_t  m_idPlayerPtr = 0;
	const std::string m_unknowWeapon = "Unknown Weapon";
	

	
	

public:
	MemHelper()
	{
	}
	

	
	
	
	static bool isBadReadPtr(void* ptr);
	static uintptr_t FindPtrAddress(uintptr_t addr, std::vector<unsigned int>& offsets);
	static __int64 FindPtrFromRelativeOffset(uintptr_t funcStartAddress, int instructionOffset1, int instructionOffset2);
	static int FindHardcodedOffset(uintptr_t funcStartAddress, const int instructionOffset);
	bool isGameFileNameValid(std::string fileName);	
	static uintptr_t getModuleBaseAddr();
	static uintptr_t getFuncAddr(uintptr_t offset);
	static uintptr_t getAddr(uintptr_t offset);
	static bool overwriteInstruction(std::string refStr, const uintptr_t instructionAddr, std::vector<unsigned char> newInstructionVec);
	static bool overwriteInstructionIfNotEqual(std::string refStr, const uintptr_t instructionAddr, std::vector<unsigned char> newInstructionVec);
	static bool isSameByteArrays(const BYTE* array1, const BYTE* array2, size_t length);
	static DWORD64 PatternScan(const char* szModule, const char* signature);
	static DWORD64 ModulePatternScan(std::string scanFriendlyName, const char* signature);
	//static DWORD64 ModulePatternScan(std::string moduleName, std::string scanFriendlyName, const char* signature);

	static DWORD64 PatternScanForCurrentModule(const char* signature);

	

	

};

