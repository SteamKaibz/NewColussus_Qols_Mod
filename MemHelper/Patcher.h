#pragma once



#include <Windows.h>
#include <algorithm>
#include <string>
#include <vector>
#include "../Config/Config.h"
#include "MemHelper.h"

struct Patcher
{
private:

public:

	static bool patch(std::string patchNameStr, uintptr_t addr, const std::vector<unsigned char>& instructionVec);
	

	static bool patchIfNeeded(std::string patchNameStr, uintptr_t addr, const std::vector<unsigned char>& newInstructionVec);
	
};










