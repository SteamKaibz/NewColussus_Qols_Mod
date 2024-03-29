#pragma once


#include <string>
#include <cstdint>
#include "../MemHelper/MemHelper.h"
#include "../Wolf2/idEngineLocalManager.h"
#include "../Wolf2/TypeInfoManager.h"
#include "../Wolf2/idGameLocalManager.h"
#include "../Wolf2/idKisculeNodeActionMidnightControlManager.h"
#include "../Wolf2/idCmdManager.h"
#include "../Wolf2/idCvarManager.h"
#include "../MemHelper/Patcher.h"
#include "../Wolf2/idRenderModelGuiManager.h"
#include "../Wolf2/idConsoleLocalManager.h"
#include "../Wolf2/idResourceManager.h"
#include "../Wolf2/idUsercmdGenLocalManager.h"
#include "../Wolf2/ADS_Manager.h"
#include "../Wolf2/cachedCvarsManager.h"






class Scanner
{
private:

public:

	static bool fastGetAddressesAndPatch();

	static bool scanForAddressesAndPatch();

};

static const std::vector<unsigned char> UnrestrictIdConsoleNewInstructionVec = { 0x00 };
static const std::vector<unsigned char> UnrestrictIdConsoleBindsNewInstructionVec = { 0x00 };

static const std::vector<unsigned char> RestrictIdConsoleNewInstructionVec = { 0x01 };
static const std::vector<unsigned char> UnlockMaxNamedIdColorsPatchNewInstructionVec = { 0x02 };

static const std::vector<unsigned char> PreventForceAntialiasingForHdrDebugInstructionVec = { 0x90, 0x90, 0x90, 0x90, 0x90 };

