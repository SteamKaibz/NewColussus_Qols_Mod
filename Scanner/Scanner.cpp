#include "Scanner.h"
#include "../Wolf2/idLoadScreenManager.h"




bool Scanner::fastGetAddressesAndPatch() {

	logInfo("fastGetAddressesAndPatch: Started...");

	if (!Patcher::patchIfNeeded("UnrestrictIdConsole1", (MemHelper::getFuncAddr(0xA8DB77) + 6), UnrestrictIdConsoleNewInstructionVec)) {
		logErr("failed for unlockConsole_1Sig");
		return false;
	}

	if (!Patcher::patchIfNeeded("UnrestrictIdConsole2", (MemHelper::getFuncAddr(0xA8DB83) + 1), UnrestrictIdConsoleNewInstructionVec)) {
		logErr("failed for unlockConsole_2Sig");
		return false;
	}

	if (!Patcher::patchIfNeeded("PreventForcedAntiAliasingForHdrDebug1", MemHelper::getFuncAddr(0x1121DC3), PreventForceAntialiasingForHdrDebugInstructionVec)) {
		logErr("failed for PreventForcedAntiAliasingForHdrDebug1");
		return false;
	}

	
	if (!idGameLocalManager::acquireIdGameLocalPtr(MemHelper::getAddr(0x3C7CD40))){
		logErr("failed for IdGameLocalPtr");
		return false;
	}

	if (!idEngineLocalManager::acquireidEngineLocalPtr(MemHelper::getAddr(0x50B0A90))) {
		logErr("failed for idEngineLocal");
		return false;
	}


	if (!TypeInfoManager::acquireTypeInfoTools(idEngineLocalManager::getTypeInfoToolPtr())) {
		return false;
	}
	
		
	if (!idCvarManager::acquireIdCVarSystemLocalPtr(idEngineLocalManager::getidCVarSystemLocalPtr())) {
		return false;
	}

	if (!idCmdManager::acquireIdCmdSystemLocalPtr(idEngineLocalManager::getidCmdSystemLocalPtr())) {
		return false;
	}


	if (!idCvarManager::acquireFindInternalFuncPtr(MemHelper::getFuncAddr(0x1239700))) {
		logErr(" failed for FindInternal");
		return false;
	}

	if (!idCvarManager::acquireSetInternalFuncAddr(MemHelper::getFuncAddr(0x1239140))) {
		logErr("failed for setCvarInternalFunc");
		return false;
	}

	if (!idCmdManager::acquireIdCmdExecuteFuncAddr(MemHelper::getFuncAddr(0x12653E0))) {
		logErr("failed for executeCmdFunc");
		return false;
	}


	if (!cachedCvarsManager::cacheCriticalCvars()) {
		logErr("fail to cache critical Cvars");
		return false;
	}


	if (!TypeInfoManager::acquirreFindClassInfoFuncPtr(MemHelper::getFuncAddr(0x1285C80))) {
		logErr(" failed for classInfoFunc");
		return false;
	}

	if (!TypeInfoManager::acquirreFindEnumInfoFuncPtr(MemHelper::getFuncAddr(0x1285200))) {
		logErr("failed for enumInfoFuncSig");
		return false;
	}


	if (!idRenderModelGuiManager::acquireDrawStretchPicFuncAddr(MemHelper::getAddr(0x3AB8E0))) {
		return false;
	}

	if (!idConsoleLocalManager::acquirreIdConsoleLocal(MemHelper::getAddr(0x3CA1460))) {
		return false;
	}

	if (!idResourceManager::acquireGetResListForClsNameFp(MemHelper::getFuncAddr(0xABBE60))) {
		return false;
	}


	if (!ADS_Manager::acquireZoomBtnReleaseInsctructionAddr(MemHelper::getAddr(0xFED0D6))) {
		return false;
	}

	if (!idLoadScreenManager::acquireIdLoadScreenRelatedPtr(MemHelper::getAddr(0x3CB86E0))) {
		return false;
	}



	logInfo("fastGetAddressesAndPatch: Sucess !");
	return true;
}



bool Scanner::scanForAddressesAndPatch()
{

	logInfo("scanForAddressesAndPatch: Pattern Scans Started...");

	static const std::vector<unsigned char> UnrestrictConsoleNewInstructionVec = { 0x00 };

	const char unlockConsole_1Sig[] = "C7 05 ? ? ? ? ? ? ? ? EB 0C BA ? ? ? ? 49 8B CF";
	if (!Patcher::patchIfNeeded("UnrestrictIdConsole1", ((uintptr_t)MemHelper::ModulePatternScan("unlockConsole_1Sig", unlockConsole_1Sig) + 6), UnrestrictIdConsoleNewInstructionVec)) {
		logErr("scanForAddressesAndPatch failed for unlockConsole_1Sig");
		return false;
	}

	const char unlockConsole_2Sig[] = "BA ? ? ? ? 49 8B CF FF 50 18";
	if (!Patcher::patchIfNeeded("UnrestrictIdConsole2", ((uintptr_t)MemHelper::ModulePatternScan( "unlockConsole_2Sig", unlockConsole_2Sig) + 1), UnrestrictIdConsoleNewInstructionVec)) {
		logErr("scanForAddressesAndPatch failed for unlockConsole_2Sig");
		return false;
	}


	const char idGameLocalPtrSig[] = "48 8B 05 ? ? ? ? 48 8B 08 48 8D 15 ? ? ? ? 4C 8B 41 48 48 3B CA 0F 85";
	if (!idGameLocalManager::acquireIdGameLocalPtr(MemHelper::FindPtrFromRelativeOffset(((uintptr_t)MemHelper::ModulePatternScan( "GetidGameLocalPtr", idGameLocalPtrSig)), 3, 7))) {
		logErr("scanForAddressesAndPatch failed for idGameLocalPtrSig");
		return false;
	}


	const char idEngineLocalSig[] = "48 8B 05 ? ? ? ? 48 8D 0D ? ? ? ? 48 3B C1 75 09 4C 8D 25";	
	if (!idEngineLocalManager::acquireidEngineLocalPtr(MemHelper::FindPtrFromRelativeOffset(((uintptr_t)MemHelper::ModulePatternScan( "GetidEngineLocal", idEngineLocalSig)), 3, 7))){
		logErr("scanForAddressesAndPatch failed for idEngineLocal_Sig");
		return false;
	}	

	if (!TypeInfoManager::acquireTypeInfoTools(idEngineLocalManager::getTypeInfoToolPtr())) {
		return false;
	}

	if (!idCvarManager::acquireIdCVarSystemLocalPtr(idEngineLocalManager::getidCVarSystemLocalPtr())) {
		return false;
	}

	if (!idCmdManager::acquireIdCmdSystemLocalPtr(idEngineLocalManager::getidCmdSystemLocalPtr())) {
		return false;
	}

	const char findCvarInternalFuncSig[] = "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 4C 89 74 24 ? 41 57 48 83 EC 20 4C 8B 0D";
	if (!idCvarManager::acquireFindInternalFuncPtr((uintptr_t)MemHelper::ModulePatternScan( "findCvarInternalFuncSig", findCvarInternalFuncSig))) {
		logErr("scanForAddressesAndPatch failed for findCvarInternalFuncSig");
		return false;
	}

	const char setCvarInternalFuncSig[] = "40 57 B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 C7 44 24 ? ? ? ? ? 48 89 9C 24 ? ? ? ? 48 89 B4 24 ? ? ? ? 48 8B FA 48 8B D9";
	if (!idCvarManager::acquireSetInternalFuncAddr((uintptr_t)MemHelper::ModulePatternScan( "setCvarInternalFuncSig", setCvarInternalFuncSig))) {
		logErr("scanForAddressesAndPatch failed for setCvarInternalFuncSig");
		return false;
	}

	const char executeCmdFuncSig[] = "40 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 C7 45 ? ? ? ? ? 48 89 9C 24 ? ? ? ? 48 89 B4 24 ? ? ? ? 48 89 BC 24 ? ? ? ? 4C 89 A4 24 ? ? ? ? 48 8B DA";
	if (!idCmdManager::acquireIdCmdExecuteFuncAddr((uintptr_t)MemHelper::ModulePatternScan( "executeCmdFuncSig", executeCmdFuncSig))) {
		logErr("scanForAddressesAndPatch failed for executeCmdFuncSig");
		return false;
	}

	const char classInfoFuncSig[] = "4C 89 44 24 ? 48 89 54 24 ? 48 89 4C 24 ? 55 56 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 C7 44 24";
	if (!TypeInfoManager::acquirreFindClassInfoFuncPtr((uintptr_t)MemHelper::ModulePatternScan( "FindClassInfoFuncPtrSig", classInfoFuncSig))) {
		logErr("scanForAddressesAndPatch failed for classInfoFuncSig");
		return false;
	}

	const char enumInfoFuncSig[] = "48 89 5C 24 ? 56 0F B6 02";
	if (!TypeInfoManager::acquirreFindEnumInfoFuncPtr((uintptr_t)MemHelper::ModulePatternScan( "FindEnumInfoFuncPtrSig", enumInfoFuncSig))) {
		logErr("scanForAddressesAndPatch failed for enumInfoFuncSig");
		return false;
	}
	
	
	if (!idRenderModelGuiManager::acquireWhiteMaterialAddr(MemHelper::getAddr(0x2F120D0))) {
		return false;
	}

	if (!idRenderModelGuiManager::acquireDrawStretchPicFuncAddr(MemHelper::getAddr(0x3AB8E0))) {
		return false;
	}

	if (!idConsoleLocalManager::acquirreIdConsoleLocal(MemHelper::getAddr(0x3CA1460))) {
		return false;
	}

	if (!idResourceManager::acquireGetResListForClsNameFp(MemHelper::getFuncAddr(0xABBE60))) {
		return false;
	}
	




	logInfo("scanForAddressesAndPatch: Pattern Scans sucess !");
	return true;
}
