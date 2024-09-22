#pragma once


#include <windows.h>
#include <thread>
#include <string>
#include <iostream>
#include "MinHook.h"
#include "intrin.h"
#include <sstream>   
#include <vector>
#include <cstring>
#include <stdarg.h>
#include "stdafx.h"
#include "Common.h"
#include "SWIP.h"
#include "SWIP.h"

#include "MinHookManager/MinHookManager.h"
#include "../K_Utils/K_Utils.h"
//#include "IniFile/IniFileData.h"
#include "MD5/md5Check.h"


//#include "IniFile/IniFileData.h"
//#include "IniFile/IniFile.h"
#include "Voice/Voice.h"
#include "Config/Config.h"
#include "../System/FileWatcher.h"

#include "ImGui/console/console.hpp"
#include "ImGui/hooks/hooks.hpp"
#include "ImGui/utils/utils.hpp"
#include "ImGui/dependencies/minhook/MinHook.h"

//#include "Rtti/Rtti_Helper.h"
#include "TypeGenerator/ClassDefFileGenerator.h"
#include "TypeGenerator/EnumsDefFileGenerator.h"
#include "ImGui/ImGuiUserConfig.h"
#include "ImGui/dependencies/imgui/imconfig.h"
#include "Scanner/Scanner.h"
#include "Config/ModStatus.h"
#include "TypeGenerator/idLibGenerator.h"
#include "Wolf2/idGameLocalManager.h"
#include "Tests/Tests.h"
#include "Wolf2/idUsercmdGenLocalManager.h"
//#include "TypeGenerator/idaTypesGenerator.h"
#include "Wolf2/idCvarManager.h"
#include "Wolf2/idEventManager.h"
#include "Wolf2/idKisculeNodeActionMidnightControlManager.h"
#include "Wolf2/idCmdManager.h"
#include "Wolf2/timescaleManager.h"
#include "Debug/Debug.h"
#include "Wolf2/MenuStateManager.h"
#include "Wolf2/idConsoleLocalManager.h"
#include "Wolf2/ImGuiManager.h"
#include "ImGui/menu/menu.hpp"
#include "ModSettings/ModSettings.h"
#include "FileOp/FileOp.h"
#include "Wolf2/autoItemPickUpManager.h"
#include "Wolf2/customDotCrosshairManager.h"
#include <cstdarg>
#include "ModSettings/ModSettingsManager.h"
#include "Wolf2/idResourceManager.h"
#include "Wolf2/idLightManager.h"
#include "Wolf2/idMaterialManager.h"
#include "Wolf2/weaponsManager.h"
#include "Wolf2/idInventoryManager.h"
#include "Wolf2/idSWF_Manager.h"
#include "Wolf2/hudManager.h"
#include "Wolf2/idFocusTrackerManager.h"
#include "Wolf2/idPlayerManager.h"
#include "Wolf2/BuildInfo.h"
#include "Wolf2/cameraManager.h"
#include "Wolf2/soundManager.h"
#include "Wolf2/idRenderParmManager.h"
#include "Wolf2/hintManager.h"
#include "Wolf2/languageManager.h"
#include "TypeGenerator/IdaScriptsGen.h"





#if _WIN64 
#pragma comment(lib, "libMinHook.x64.lib")
#else
#pragma comment(lib, "libMinHook.x86.lib")
#endif


const std::wstring sayErrorCheckLog = L"ERROR. Check the mod log file in game directory";
const std::wstring sayWrongGameNameError = L"wrong game file name, mod disabled";
const std::wstring sayHookingError = L"Hooking Error, mod disabled";
const std::wstring sayScanPatternError = L"Pattern Scanning Error, mod disabled";
const std::wstring saySuccesLoadingMod = L"mod levelLoaded";
const std::wstring saySIniFileReLoaded = L"Ini File Reloaded";
const std::wstring sayIniFileParsingError = L"file parsing error, regenerating ini File";
const std::wstring sayIniFileSavingDefault = L"Saving default ini File";
const std::wstring sayConfigExceptionError = L"Config Exception Error";
const std::wstring sayGeneratingTypes = L"Creating Types Files";



swfRect_t debugRect;

bool g_isForceDevMode = false;

bool g_isNexusDebugMode = true;

bool g_debugGiveItemFlag = false;

bool g_isFakeZoomBtnPressed = false;

bool g_isUseKeyPress_1 =  false;
bool g_isUseKeyPress_2 =  false;

bool g_isFakeUseFlagV2 = false;

bool g_isGameInputEnabled = true;

bool g_isFakeUseInputFlag = false;
static uint64_t g_lastAutoUseKeyPressMs = 0;

bool g_isAutoUseKey = false;
bool g_isUseKeyPress = false;
bool g_isUseKeyPressTrigger = false;

bool g_isMinHookInitializeOk = false;

bool g_debugIsReadyToRenderIceNadeIcon = false;

float g_debugScreenWidth = -1;
float g_debugScreenHeight = -1;

bool g_debugIsReticleHide = false;
bool g_debugIsInCinematic = false;
bool g_debugIsDemonPlayer = false;

gameState_t g_lastGameState = GAMESTATE_UNINITIALIZED;

std::string g_debugLastCurrentGameMode = "unknow Game Mode";
unsigned int g_sleepTimeMainLoopMs = 20;

std::string globalVariableString;

bool g_isEnableHook2Triggered = false;

bool g_isGameCrosshairHidden = false;

bool g_isDebugHudEnabled = false;

__int64 g_debugMaterialAddr = 0;


bool g_isGameInitialized = false;
bool g_isDllCalledByGame = false;


uint64_t g_lastGetAsyncKeyPress = 0;

bool g_debugReticleScale = true;

static std::vector<std::string> matrNamesVec;

std::string g_plusSignStr = "+";


//bool g_isForceNoUI = true;

HINSTANCE DllHandle;
HWND hWindow = NULL;

MemHelper mem;
Md5Check md5Check;
ModStatus modStatus;
Tests k_tests;


struct Int128 {
	int64_t high;
	int64_t low;
};


void initImguiV2();





typedef char(__fastcall* idMenuManager_Shell_Update_t)(__int64 idMenuManager_Shell_a1, __int64* a2);
idMenuManager_Shell_Update_t p_idMenuManager_Shell_Update_t = nullptr;
idMenuManager_Shell_Update_t p_idMenuManager_Shell_Update_t_Target = nullptr;

char __fastcall idMenuManager_Shell_Update_Hook(__int64 idMenuManager_Shell_a1, __int64* a2) {

	static bool isMenuInitialized = false;
	static bool last_bShowMenu = false;
	static shellScreen_t lastMenuIndex = shellScreen_t::NUM_SHELL_SCREENS;
	static bool isFirtTimeLogImguiUsage = true;			


	MenuStateManager::acquireidMenuManager_ShellPtr(idMenuManager_Shell_a1);

	timescaleManager::resetSpeed();


	if (!ModSettingsManager::getIsUseImgui()) {
		if (isFirtTimeLogImguiUsage) {
			isFirtTimeLogImguiUsage = false;
			logWarn("idMenuManager_Shell_Update_Hook: user is not using Imgui, mod settings UI is disabled. User will not be able to change any mod setting at runtime, he will have to restart the game for changes to take effect.");
		}
		return p_idMenuManager_Shell_Update_t(idMenuManager_Shell_a1, a2);
	}
	 

	shellScreen_t currentMenuIndex = *(shellScreen_t*)(idMenuManager_Shell_a1 + 0x30);


	if ((currentMenuIndex >= SHELL_SCREEN_START && currentMenuIndex < NUM_SHELL_SCREENS)) {

		ImGuiManager::setIsInitFlag(true);
		if (!isMenuInitialized) {
			logInfo("idMenuManager_Shell_Update_Hook: menu is being initialized, menu index: %d", currentMenuIndex);
		}		
		isMenuInitialized = true;
		
	}
	else if(!isMenuInitialized) {
		logInfo("idMenuManager_Shell_Update_Hook: waiting for menu to initialize...(currentMenuIndex val: %d)", currentMenuIndex);

		return p_idMenuManager_Shell_Update_t(idMenuManager_Shell_a1, a2); //? retuning.
	}


	idCmdManager::executeCmd("menu_showOptionForDevMenu 1");
	
	

	//! temporary to check if users with intel gpu can still use the mod
	/*if (Config::IsForceNoModUi) {
		idCvarManager::setCvar("menu_showOptionForDevMenu", "0");
	}
	else {
		idCvarManager::setCvar("menu_showOptionForDevMenu", "1");
	}*/


	if (currentMenuIndex == SHELL_SCREEN_DEV) {
		idCmdManager::executeCmd("in_unlockMouseInMenus 1");
		//idCvarManager::setCvar("in_unlockMouseInMenus", "1");       
		Menu::bShowMenu = true;
		
	}
	else {
			
		if (!idRenderModelGuiManager::isWhiteMaterialacquired()) {
			idRenderModelGuiManager::acquireWhiteMaterial();
		}
		idCmdManager::executeCmd("in_unlockMouseInMenus 0");
		//idCvarManager::setCvar("in_unlockMouseInMenus", "0");
		Menu::bShowMenu = false;

	}

	if (Menu::bShowMenu != last_bShowMenu) {
		last_bShowMenu = Menu::bShowMenu;
		if (Menu::bShowMenu) {
			logInfo("idMenuManager_Shell_Update_Hook: Menu::bShowMenu is true, mod menu should be visible by the user (currentMenuIndex: %d", (int)currentMenuIndex);
		}
		else {
			logInfo("idMenuManager_Shell_Update_Hook: Menu::bShowMenu is false, mod menu should NOT be visible by the user (currentMenuIndex: %d", (int)currentMenuIndex);
		}		
	}

	if (currentMenuIndex != lastMenuIndex) {
		if (currentMenuIndex == SHELL_SCREEN_DEV) {       
			
		}
		else if (lastMenuIndex == SHELL_SCREEN_DEV) {        
			
			logInfo("user is leaving mod menu");
			Menu::SaveToFile();
			Menu::logChangedJsonFile();
			ModSettingsManager::updateFromImGui(Menu::getSettings());

			weaponsManager::updateDeclWeapons();

			customDotCrosshairManager::setUserInModSettings();				


			hudManager::logWarningTriggerVals();			

		}

		//? 20/9/24 not needed anymore as we use cmdTracker to get inputs
		/*if (lastMenuIndex == SHELL_SCREEN_CONTROLS) {
			logInfo("shell hook: getting out of controls screen: updating cached bound keys...");
			idUsercmdGenLocalManager::updateCurrentUseBtnKeyNum();
			idUsercmdGenLocalManager::tryCacheGameFireKeysBinds();
		}*/

		std::string lastMenuStr = MenuStateManager::shellScreenToString(lastMenuIndex);
		std::string currMenuStr = MenuStateManager::shellScreenToString(currentMenuIndex);
		logInfo("shell hook: shell menu has changed from %s (shellScreen_t: 0x%X) to %s (shellScreen_t: 0x%X)", lastMenuStr.c_str(), (int)lastMenuIndex, currMenuStr.c_str(), (int)currentMenuIndex);

		lastMenuIndex = currentMenuIndex;
	}
	
	return p_idMenuManager_Shell_Update_t(idMenuManager_Shell_a1, a2);
}




//! RVA: 0x528310
//typedef __int64(__fastcall* DrawString_t)(
//	void* idRenderModelGui_a1,
//	float a2,
//	float a3,
//	unsigned __int8* charPtr_a4,
//	__int64 a5,
//	char a6,
//	float a7);
//
//
//DrawString_t p_DrawString_t = nullptr;
//DrawString_t p_DrawString_t_Target = nullptr;
//
//
//__int64 __fastcall DrawString_t_Hook(
//	void* idRenderModelGui_a1,
//	float a2,
//	float a3,
//	unsigned __int8* charPtr_a4,
//	__int64 a5,
//	char a6,
//	float a7) {
//
//
//
//	// Call the original function
//	return p_DrawString_t(idRenderModelGui_a1, a2, a3, charPtr_a4, a5, a6, a7);
//}




typedef void(__fastcall* drawChar_MB_5280B0_t)(__int64 a1, float a2, float a3, unsigned int a4, float a5);
drawChar_MB_5280B0_t p_drawChar_MB_5280B0_t = nullptr;
drawChar_MB_5280B0_t p_drawChar_MB_5280B0_t_Target = nullptr;

void __fastcall drawChar_Hook(__int64 a1, float a2, float a3, unsigned int a4, float a5) {
	
	if (!idConsoleLocalManager::isConsoleOpened()) {
		return;
	}

	p_drawChar_MB_5280B0_t(a1, a2, a3, a4, a5);     
}





typedef __int64(__fastcall* goingFromMainMenuToInGame_t)(__int64 a1);
goingFromMainMenuToInGame_t p_GoingFromMainMenuToInGame = nullptr;
goingFromMainMenuToInGame_t p_GoingFromMainMenuToInGame_Target = nullptr;


__int64 __fastcall goingFromMainMenuToInGame_Hook(__int64 a1) {

	//static int lastFullScreenState = -1;

	/*int fullscreenState = idCvarManager::getCvarInt("r_fullscreen");

	if (fullscreenState != lastFullScreenState) {
		logInfo("fullscreenState has changed from: %d to %d", lastFullScreenState, fullscreenState);
		lastFullScreenState = fullscreenState;
	}*/

	idLightManager::updateHeadLight();
	



	return p_GoingFromMainMenuToInGame(a1);
}




typedef __int16(__fastcall* closeIdConsoleSmth_A8D1E0_t)(__int64 a1, char a2);

closeIdConsoleSmth_A8D1E0_t p_closeIdConsoleSmth_A8D1E0 = nullptr;
closeIdConsoleSmth_A8D1E0_t p_closeIdConsoleSmth_A8D1E0_Target = nullptr;


__int16 __fastcall closeIdConsoleSmth_A8D1E0_Hook(__int64 a1, char a2) {
	
	logInfo("console is closing...");
	//idUsercmdGenLocalManager::updateCurrentUseBtnKeyNum();	

	idCmdManager::setCriticalCvars();

	return p_closeIdConsoleSmth_A8D1E0(a1, a2);
}





typedef void(__fastcall* perfMetricsDrawGraphs_t)(__int64 a1, __int64 idRenderModelGui_a2);
perfMetricsDrawGraphs_t p_perfMetricsDrawGraphs = nullptr;
perfMetricsDrawGraphs_t p_perfMetricsDrawGraphs_Target = nullptr;

void __fastcall  perfMetricsDrawGraphs_Hook(__int64 a1, __int64 idRenderModelGui_a2) {

	
	if (!idEngineLocalManager::isGameActive()) {
		return;
	}

	
	if (ModSettingsManager::isCustomHudEnabled() && ModSettingsManager::isCustomCrosshairEnabled() && customDotCrosshairManager::isVisible()) {

		if (customDotCrosshairManager::isResolutionChanged()) {
			customDotCrosshairManager::updatePos();
		}

		else if (customDotCrosshairManager::wasUserInModSettings()) {
			customDotCrosshairManager::updatePos();
			customDotCrosshairManager::updateColors();
		}

		auto crosshair = customDotCrosshairManager::get();

		idRenderModelGuiManager::drawColoredRect(idRenderModelGui_a2, crosshair.outlineRect.x, crosshair.outlineRect.y, crosshair.outlineRect.w, crosshair.outlineRect.h, crosshair.outlineIdColor);
		idRenderModelGuiManager::drawColoredRect(idRenderModelGui_a2, crosshair.fillRect.x, crosshair.fillRect.y, crosshair.fillRect.w, crosshair.fillRect.h, crosshair.currentIdColorFillRef);

		return;


	}
	

	p_perfMetricsDrawGraphs(a1, idRenderModelGui_a2);     
}



typedef void(__fastcall* showHudAndCrosshair_FAA460_t)(__int64 a1, __int64 idHudInfo_a2);

showHudAndCrosshair_FAA460_t p_showHudAndCrosshair_FAA460 = nullptr;      
showHudAndCrosshair_FAA460_t p_showHudAndCrosshair_FAA460_Target = nullptr;      

void __fastcall showHudAndCrosshair_FAA460_Hook(__int64 a1, __int64 idHudInfo_a2) {
	static uint64_t lastAnimCamCheckMs = 0;



	if (ModSettingsManager::isCustomHudEnabled() && ModSettingsManager::isCustomCrosshairEnabled() && idHudInfo_a2) {
		DWORD hudReticleFlags = *(DWORD*)(idHudInfo_a2 + 0x958);
		bool isCrosshairShown = (hudReticleFlags & 1) != 0;
		customDotCrosshairManager::updateVisibility(isCrosshairShown);
		customDotCrosshairManager::setColor((*(DWORD*)(idHudInfo_a2 + 0x994) == 0));   

	}
	p_showHudAndCrosshair_FAA460(a1, idHudInfo_a2);
}



typedef DWORD* (__fastcall* soundEventSmth_t)(__int64 a1, DWORD* idSysLocal_a2, __int64 idSoundEvent_a3, char a4, char a5);
soundEventSmth_t p_soundEventSmth = nullptr;
soundEventSmth_t p_soundEventSmth_Target = nullptr;

DWORD* __fastcall soundEventSmth_Hook(__int64 a1, DWORD* idSysLocal_a2, __int64 idSoundEvent_a3, char a4, char a5) {

	if (ModSettingsManager::isSilentProtagonist()) {
		std::string idSoundName = *(const char**)(idSoundEvent_a3 + 8);

		for (const auto& soundName : soundManager::skipSoundsStrSet) {
			if (idSoundName.compare(0, soundName.length(), soundName) == 0) {
				auto resPtr = (idResource*)idSoundEvent_a3;
				*idSysLocal_a2 = 0;
				return idSysLocal_a2;
			}
		}
		
		
	}	
	return p_soundEventSmth(a1, idSysLocal_a2, idSoundEvent_a3, a4, a5);     
}



typedef __int64(__fastcall* getLocalisedStrAddrMB_t)(__int64 struct_a1, char* refString_a2);
getLocalisedStrAddrMB_t p_getLocalisedStrAddrMB = nullptr;
getLocalisedStrAddrMB_t p_getLocalisedStrAddrMB_Target = nullptr;

__int64 __fastcall getLocalisedStrAddrMB_Hook(__int64 struct_a1, char* string_a2) {
	

	if (!languageManager::isGetStringsPtrAttempt()) {
		languageManager::acquireDevStringsPtrs();
	}
	
	return p_getLocalisedStrAddrMB(struct_a1, string_a2);
}





typedef void(__fastcall* swf_RenderEditTex_t)(
	__int64 idSWF_a1,
	__int64 idRenderModelGui_a2,
	__int64 idSWFTextInstance_a3,
	float* a4,
	unsigned int a5,
	_QWORD* a6,
	char a7
	);

swf_RenderEditTex_t p_swf_RenderEditTex = nullptr;
swf_RenderEditTex_t p_swf_RenderEditTex_Target = nullptr;

void __fastcall swf_RenderEditTex_Hook(
	__int64 idSWF_a1,
	__int64 idRenderModelGui_a2,
	__int64 idSWFTextInstance_a3,
	float* a4,
	unsigned int a5,
	_QWORD* a6,
	char a7
) {

	static swfColorRGBA_t lastHealthColor;

	static bool isFirstTimeDevString = true;
	static bool isFirstTimeDevHelpString = true;
	static int hookExecDevStrCheckCounter = 0;
	static int hookExecDevHelpStrCheckCounter = 0;

	static void* lasttextInst_textPtr = nullptr;

	
	if (idSWFTextInstance_a3) {
		
		auto textInst = (idSWFTextInstance*)idSWFTextInstance_a3;	

		if (textInst->fullPathHash == idSWF_Manager::armorTextInstanceHash) {

			idHudInfo* idHudInfoPtr = idPlayerManager::getIdHudInfo();

			if (ModSettingsManager::isHudWarningEnabled() && hudManager::isRedArmorTrigger(idHudInfoPtr)) {
				idSWF_Manager::blink((idSWFTextInstance*)idSWFTextInstance_a3);
			}	
			else if (ModSettingsManager::isHudWarningEnabled() && hudManager::isOrangeArmorTrigger(idHudInfoPtr)) {
				idSWF_Manager::setOrangeColor((idSWFTextInstance*)idSWFTextInstance_a3);
			}
			else {
				idSWF_Manager::setDefaultColor((idSWFTextInstance*)idSWFTextInstance_a3);
			}
		}

		else if (textInst->fullPathHash == idSWF_Manager::healthTextInstanceHash) {

			idHudInfo* idHudInfoPtr = idPlayerManager::getIdHudInfo();

			if (ModSettingsManager::isHudWarningEnabled() && hudManager::isRedHealthTrigger(idHudInfoPtr)) {
				idSWF_Manager::blink((idSWFTextInstance*)idSWFTextInstance_a3);
			}
			if (ModSettingsManager::isHudWarningEnabled() && hudManager::isOrangeHealthTrigger(idHudInfoPtr)) {
				idSWF_Manager::setOrangeColor((idSWFTextInstance*)idSWFTextInstance_a3);
			}
			else {
				idSWF_Manager::setDefaultColor((idSWFTextInstance*)idSWFTextInstance_a3);
			}
		}

		//? may be this is causing a freeze for many users...we could replace it by a btn they have to press to acces the mod settings...
		
		/*else if (MenuStateManager::isRenderModNameFlag() && (textInst->text.data && languageManager::getLocalizedDevStr() && strcmp(textInst->text.data, languageManager::getLocalizedDevStr()) == 0)) {

			if (&textInst->text != lasttextInst_textPtr) {

				lasttextInst_textPtr = &textInst->text;

				logInfo("debug main menu: textInst: %p &textInst->text has changed to: %p swf_RenderEditTex_Hook: textInst->text.len: %d textInst->text.allocedAndFlag: 0x%X  languageManager::getLocalizedDevStr(): %s", textInst, &textInst->text ,  textInst->text.len, textInst->text.allocedAndFlag, languageManager::getLocalizedDevStr());
			}			
		}*/

		//! changing the str_menu_root_dev_label
		else if (MenuStateManager::isRenderModNameFlag() && (textInst->text.data && languageManager::getLocalizedDevStr() && strcmp(textInst->text.data, languageManager::getLocalizedDevStr()) == 0)) {
			logInfo("debug main menu: swf_RenderEditTex_Hook: textInst->text.len: %d textInst->text add: %p", textInst->text.len, &textInst->text);
			if (textInst->text.allocedAndFlag) {
				strncpy(textInst->text.data, "Kaibz Mod", 9);
				if (isFirstTimeDevString) {
					logInfo("isFirstTimeDevString (mininising log output): swf_RenderEditTex_Hook: overwriting localized Dev str");
					isFirstTimeDevString = false;
				}
				textInst->text.len = 9;
			}
		}


		//! changing the str_menu_root_dev_help. this is the text at the bottom of the screen when hovering over a btn in the menu.
		//? 24/5/24 temporily checking if we can just comment this out....
		else if (MenuStateManager::isRenderModNameFlag() && (textInst->text.data && languageManager::getLocalizedDevHelpTextStr() && strcmp(textInst->text.data, languageManager::getLocalizedDevHelpTextStr()) == 0)) {
			if (textInst->text.allocedAndFlag) {
				strncpy(textInst->text.data, "Open Mod Settings", 17);
				if (isFirstTimeDevHelpString) {
					logInfo("(isFirstTimeDevHelpString (mininising log output): swf_RenderEditTex_Hook : overwriting localized Dev Help Text str");
					isFirstTimeDevHelpString = false;
				}
				textInst->text.len = 17;
			}
		}		
		
	}

	/*if (hookExecCounter <= 10 ) {
		logInfo("swf_RenderEditTex_Hook: debug: hook has executed: %d times (max counter 10)", hookExecCounter);
	}*/		

	return p_swf_RenderEditTex(idSWF_a1, idRenderModelGui_a2, idSWFTextInstance_a3, a4, a5, a6, a7);
}





typedef void(__fastcall* RenderSpriteInstance_t)(
	idSWF* idSWF_a1,
	__int64 idRenderModelGui_a2,
	idSWFSpriteInstance* idSWFSpriteInstance_a3,
	__int64 struct_a4,
	unsigned int a5,
	char a6);

RenderSpriteInstance_t p_RenderSpriteInstanc_Target = nullptr;
RenderSpriteInstance_t p_RenderSpriteInstanc = nullptr;

void __fastcall RenderSpriteInstance_Hook(
	idSWF* idSWF_a1,
	__int64 idRenderModelGui_a2,
	idSWFSpriteInstance* idSWFSpriteInstance_a3,
	__int64 struct_a4,
	unsigned int a5,
	char a6) {
		



	static uint64_t lastHudPosAndScaleCheckMs = 0;
	static bool isFirstTimeInRenderSpriteInstance_Hook = true;
	

	if (idSWF_a1 && (strcmp(idSWF_a1->filename.str, "swf/merchud.swf") == 0)) {
		idSWF_Manager::acquireMercuryHudidSWFPtrFast(idSWF_a1);
	

		/*if (isFirstTimeInRenderSpriteInstance_Hook) {

			bool isError = false;
			float windowHeightF = (float)cachedCvarsManager::get_WindowHeightInt();
			
			if (idSWF_a1->swfScale != idSWF_Manager::swfScaleDefault) {
				logWarn("isFirstTimeInRenderSpriteInstance_Hook: idSWF_a1->swfScale (%.2f) != idSWF_Manager::swfScaleDefault (%.2f) THIS IS NOT EXPECTED BEHAVIOUR", idSWF_a1->swfScale, idSWF_Manager::swfScaleDefault);
				isError = true;
			}
			if (idSWF_a1->frameHeight != windowHeightF) {
				logWarn("isFirstTimeInRenderSpriteInstance_Hook: idSWF_a1->frameHeight (%.2f) != windowHeightF (%.2f) THIS IS NOT EXPECTED BEHAVIOUR ", idSWF_a1->frameHeight, windowHeightF);
				isError = true;
			}		
			if (!isError) {
				logInfo("isFirstTimeInRenderSpriteInstance_Hook is true: idSWF_a1->swfScale: %.2f idSWF_a1->frameHeight: %.2f as expected.", idSWF_a1->swfScale, idSWF_a1->frameHeight);
			}			

			isFirstTimeInRenderSpriteInstance_Hook = false;
		}*/



		if (K_Utils::EpochMillis() - lastHudPosAndScaleCheckMs > 300) {
			lastHudPosAndScaleCheckMs = K_Utils::EpochMillis();

			
			if (! ModSettingsManager::isCustomHudEnabled()) {     

				idSWF_Manager::resetHudPosAndScaleToDefault(idSWF_a1);

			}
			else {
				idSWF_Manager::setCustomHudPosAndScale(idSWF_a1);

			}
		}


		if (idSWFSpriteInstance_a3) {							

			if (ModSettingsManager::isCustomHudEnabled()) {
 				if (strncmp(idSWFSpriteInstance_a3->name.str, "reticle", 7) == 0) {
					return;
				}
			}
			
			if (!ModSettingsManager::isShowHudScoreTotalNumber()) {
				if (idSWFSpriteInstance_a3->fullPathHash == idSWF_Manager::simulationTopHudScoreTextHash) {
					return;
				}				
			}
			
			if (!ModSettingsManager::isShowWorldMarkers() && !hintManager::wasHintBtnPressed()) {
				if (strncmp(idSWFSpriteInstance_a3->name.str, "marker", 6) == 0) {					
					return;
				}
			}

			if (!ModSettingsManager::isAlarmIconsEnabled()) {
				if (idSWFSpriteInstance_a3->fullPathHash == idSWF_Manager::alarmIconsSwfHash) {
					return;
				}
			}			

			if (!ModSettingsManager::isMaxedOutEnabled() && idFocusTrackerManager::islastFocusedCrosshairIconStateMaxedOut()) {

				if (idSWFSpriteInstance_a3->fullPathHash == idSWF_Manager::maxedOutSwfHash) {
					return;
				}
			}
		}
	}	

	p_RenderSpriteInstanc(idSWF_a1, idRenderModelGui_a2, idSWFSpriteInstance_a3, struct_a4, a5, a6);
}





typedef void(__fastcall* processInput_t)(idPlayer* idPlayer_a1, __int64* a2, char a3);
processInput_t p_processInput_t = nullptr;
processInput_t p_processInput_t_Target = nullptr;

void __fastcall processInput_t_Hook(idPlayer* idPlayer_a1, __int64* a2, char a3) {

	if (MemHelper::isBadReadPtr(idPlayer_a1)) {
		return p_processInput_t(idPlayer_a1, a2, a3);
	}




	if (idPlayer_a1->playerVolatile.showMarkerHintFadeOutTime == 0xFFFFFFFFFFFFFFFFui64) {		
		hintManager::setHintBtnPressState(false);
	}
	else {
		hintManager::setHintBtnPressState(true);
	}

	return p_processInput_t(idPlayer_a1, a2, a3);

}




typedef __int64(__fastcall* guiModel_idDevGuiSmth_t)(__int64 someStruct_a1);

guiModel_idDevGuiSmth_t p_guiModel_idDevGuiSmth = nullptr;
guiModel_idDevGuiSmth_t p_guiModel_idDevGuiSmth_Target = nullptr;

__int64 __fastcall guiModel_idDevGuiSmth_Hook(__int64 someStruct_a1) {
	return 0i64;
	return p_guiModel_idDevGuiSmth(someStruct_a1);
}






typedef __int64(__fastcall* renderParm_769CE0_t)(idDeclRenderParm* DeclRenderParm_a1, __int64 a2, __int64 a3);

renderParm_769CE0_t p_renderParm_769CE0 = nullptr;      
renderParm_769CE0_t p_renderParm_769CE0_Target = nullptr;      

__int64 __fastcall renderParm_769CE0_Hook(idDeclRenderParm* DeclRenderParm_a1, __int64 a2, __int64 a3) {


	if (DeclRenderParm_a1 && DeclRenderParm_a1->parmIndex == idRenderParmManager::itemHighlightParmIndex) {
		if (ModSettingsManager::isDisableItemHighlight()) {
			DeclRenderParm_a1->parmIndex = idRenderParmManager::disableParmIndex;
		}
		else {
			DeclRenderParm_a1->parmIndex = idRenderParmManager::itemHighlightParmIndex;
		}
	}


	return p_renderParm_769CE0(DeclRenderParm_a1, a2, a3);
}


using colorSmgh_t = __int64(__fastcall*)(__int64, idDeclRenderParm*, void*);

colorSmgh_t p_colorSmgh = nullptr;
colorSmgh_t p_colorSmgh_Target = nullptr;

__int64 __fastcall colorSmgh_Hook(__int64 a1, idDeclRenderParm* idDeclRenderParm_a2, void* a3) {



	if (idDeclRenderParm_a2 && idDeclRenderParm_a2->parmIndex == idRenderParmManager::simulationFilterParmIndex) {

		if (ModSettingsManager::isDisableSimulationFilter()) {
			if (idDeclRenderParm_a2->parmIndex != idRenderParmManager::disableParmIndex) {
				logInfo("colorSmgh_Hook disabling simulation filter");
				idDeclRenderParm_a2->parmIndex = idRenderParmManager::disableParmIndex;
			}			
		}
		else {
			if (idDeclRenderParm_a2->parmIndex != idRenderParmManager::simulationFilterParmIndex){
				logInfo("colorSmgh_Hook restoring simulation filter");
				idDeclRenderParm_a2->parmIndex = idRenderParmManager::simulationFilterParmIndex;
			}			
		}
		
	}

	return p_colorSmgh(a1, idDeclRenderParm_a2, a3);
}





typedef void(__fastcall* idKeyboardSmth_t)(__int64 a1, unsigned int a2);
idKeyboardSmth_t p_idKeyboardSmth_t = nullptr;
idKeyboardSmth_t p_idKeyboardSmth_t_Target = nullptr;

void __fastcall idKeyboardSmth_Hook(__int64 idUsercmdGenLocal_a1, unsigned int a2) {		

	//todo 20/9/24 try replacing this with the new cmdTracker methods	
	/*static uint64_t lastFakeKeyPressMs = 0;
	static uint64_t lastFakeZoomKeyPressMs = 0;

	if (K_Utils::EpochMillis() - lastFakeKeyPressMs > 350) {

		if (autoItemPickUpManager::isUseKeyAutoPressFlag()) {

			logInfo("idKeyboardSmth_Hook triggering use key press n release");
			
			idUsercmdGenLocalManager::sendFakeUseKeyPressAndRelase(idUsercmdGenLocal_a1, a2, true);
			idUsercmdGenLocalManager::sendFakeUseKeyPressAndRelase(idUsercmdGenLocal_a1, a2, false);

			lastFakeKeyPressMs = K_Utils::EpochMillis();

			autoItemPickUpManager::setUseKeyAutoPressFlag(false);
		}
	}	*/

	return p_idKeyboardSmth_t(idUsercmdGenLocal_a1, a2);
}





//! 0xFEB3E0
typedef char(__fastcall* idPlayer_UseCheck_t_FEB3E0)(idPlayer* idPlayer_a1, __int64* gameTime_a2);  

idPlayer_UseCheck_t_FEB3E0 p_idPlayer_UseCheck = nullptr;
idPlayer_UseCheck_t_FEB3E0 p_idPlayer_UseCheck_Target = nullptr;

char __fastcall idPlayer_UseCheck_Hook(idPlayer* idPlayer_a1, __int64* gameTime_a2) {

	static uint64_t lastLightStartXAdjustMs = 0;

	/*idEntity* entity = (idEntity*)idPlayer_a1;	
	idUsercmdGenLocalManager::DBG_RawCmdTracker_Buttons = entity->playerController->rawUCmdTracker.usercmd.buttons;*/


	static uint64_t lastFakeKeyPressMs = 0;
	static uint64_t lastFakeZoomKeyPressMs = 0;

	if (K_Utils::EpochMillis() - lastFakeKeyPressMs > 350) {

		if (autoItemPickUpManager::isUseKeyAutoPressFlag()) {

			logInfo("idPlayer_UseCheck_Hook: triggering use key press n release");

			idUsercmdGenLocalManager::setButtonFlag(idPlayer_a1, BUTTON_USE, true);
			//idUsercmdGenLocalManager::setButtonFlag(idPlayer_a1, BUTTON_USE, false);

			/*idUsercmdGenLocalManager::sendFakeUseKeyPressAndRelase(idUsercmdGenLocal_a1, a2, true);
			idUsercmdGenLocalManager::sendFakeUseKeyPressAndRelase(idUsercmdGenLocal_a1, a2, false);*/

			lastFakeKeyPressMs = K_Utils::EpochMillis();

			autoItemPickUpManager::setUseKeyAutoPressFlag(false);
		}
	}




	idPlayerManager::handleChange(idPlayer_a1);

	idFocusTrackerManager::acquirecrosshairInfoDataForDebug(idPlayer_a1);		

	idLightManager::AdjustLight(idPlayer_a1);


	//? keep in mind the checking the pm_animCamAmoun value in console will not reflect the actual value we set with our method. i guess this is because of flags not being updated cause we change the float value directly and we should instead use the execute cmd, same as we do in doom eternal mod.
	cameraManager::updateAnimCamAmount(idPlayer_a1);	

	//cameraManager::updateAnimCamAmountV2(idPlayer_a1);


	if (idFocusTrackerManager::shouldItemBePickedUp(idPlayer_a1)) {
		autoItemPickUpManager::setUseKeyAutoPressFlag(true);

	}
	else {
		autoItemPickUpManager::setUseKeyAutoPressFlag(false);
	}

	
	return p_idPlayer_UseCheck(idPlayer_a1, gameTime_a2);
}



//! this is a way to know which keyboard key has been pressed, however you will not get the analog inputs from a controller using this, this means you will not know if trigger 1 or 2 is pressed unfortunately.
//! __int64 __fastcall idUsercmdGenLocal_SendKeySmth_AE6FE0(__int64 idUsercmdGenLocal_a1, unsigned int devicneNumMB_a2, unsigned int keyNum_a3, char isDown_a4)
typedef __int64(__fastcall* idUsercmdGenLocal_SendKeySmth_t)(__int64 idUsercmdGenLocal_a1, unsigned int devicneNumMB_a2, keyNum_t keyNum_a3, char isDown_a4);
idUsercmdGenLocal_SendKeySmth_t p_SendKeySmth_t = nullptr;
idUsercmdGenLocal_SendKeySmth_t p_SendKeySmth_t_Target = nullptr;

__int64 __fastcall SendKeySmth_t_Hook(__int64 idUsercmdGenLocal_a1, unsigned int devicneNumMB_a2, keyNum_t keyNum_a3, char isDown_a4) {	

	//idUsercmdGenLocalManager::dbgLogHookArgsChanges(idUsercmdGenLocal_a1, devicneNumMB_a2, keyNum_a3, isDown_a4);


	/*if (!ModSettingsManager::isSwapBindsWhenDualWielding()) {
		return p_SendKeySmth_t(idUsercmdGenLocal_a1, devicneNumMB_a2, keyNum_a3, isDown_a4);
	}

	if (!idUsercmdGenLocalManager::isFireKeysBindsSet()) {
		logErr("FireKeys are not set, dual wielding key swap mod feature can not work, please bind keys to fire and zoom keys");
		return p_SendKeySmth_t(idUsercmdGenLocal_a1, devicneNumMB_a2, keyNum_a3, isDown_a4);
	}

	if (idPlayerManager::isDualWielding()) {
		if (idUsercmdGenLocalManager::isAttack1Key(keyNum_a3)) {
			keyNum_a3 = K_JOY_TRIGGER1;
		}
		else if (idUsercmdGenLocalManager::isZoomKey(keyNum_a3)) {
			keyNum_a3 = K_JOY_TRIGGER2;
		}
	}*/
		
	return p_SendKeySmth_t(idUsercmdGenLocal_a1, devicneNumMB_a2, keyNum_a3, isDown_a4);
}






//! game console log
typedef void(__cdecl* IdLib_Printf)(const char* a1, ...);
IdLib_Printf  pIdLib_Printf = nullptr;
IdLib_Printf  pIdLib_PrintfTarget;


void __cdecl IdLib_PrintfHook_1238530(const char* format, ...) {
	va_list args;
	va_start(args, format);

	char buffer[2048];
	int result = vsnprintf(buffer, sizeof(buffer), format, args);      

	va_end(args);       

	globalVariableString = std::string(buffer);

	if (ModSettingsManager::getIsLogGameConsoleToLogFile()) {
		logInfo("IdLib_Printf: %s", globalVariableString.c_str());
	}

	return pIdLib_Printf(buffer);      
}




typedef char(__fastcall* idPlayerHandleZoomSmth_t)(idPlayer* idPlayer_a1, char a2, __int64 a3);
idPlayerHandleZoomSmth_t p_idPlayerHandleZoomSmth = nullptr;
idPlayerHandleZoomSmth_t p_idPlayerHandleZoomSmth_Target = nullptr;

char __fastcall idPlayerHandleZoomSmth_Hook(idPlayer* idPlayer_a1, char a2, __int64 a3) {	

	if (ModSettingsManager::isSwapBindsWhenDualWielding() && idPlayerManager::isDualWielding(idPlayer_a1)) {
		idEntity* entity = (idEntity*)idPlayer_a1;
		idUsercmdGenLocalManager::invertZoomAndAttack(entity->playerController->ucmdTracker1.usercmd.buttons);
	}

	//? 20/9/24 commenting this for alt testing
	if (!ModSettingsManager::isAdsToggleEnabled()) {
		if (ADS_Manager::getPatchState() != zoomCodeOriginal) {
			ADS_Manager::restoreZoomBtnReleaseCheck();
		}
	}
	else {

		//! if zoom key has bee pressed
		if (ADS_Manager::isToggleFlag() && idPlayer_a1) {
			//! this will patch the code
			ADS_Manager::Toggle(idPlayer_a1->playerVolatile.hudInfo.inScope);
		}
	}
	return p_idPlayerHandleZoomSmth(idPlayer_a1, a2, a3);


	/*idEntity* entity = (idEntity*)idPlayer_a1;
	idUsercmdGenLocalManager::DBG_CmdTracker1_Buttons = entity->playerController->ucmdTracker1.usercmd.buttons;

	static bool lastisZoomBtnPressed = false;

	bool isZoomBtnPressed = idUsercmdGenLocalManager::isButtonPressed(entity->playerController->rawUCmdTracker.usercmd.buttons, BUTTON_ZOOM);

	if (isZoomBtnPressed != lastisZoomBtnPressed) {

		idUsercmdGenLocalManager::DBG_IsZoomBtnPressCheckActive = true;
		ADS_Manager::Toggle(idPlayer_a1->playerVolatile.hudInfo.inScope);


		lastisZoomBtnPressed = isZoomBtnPressed;
	}
	else {
		idUsercmdGenLocalManager::DBG_IsZoomBtnPressCheckActive = false;
	}*/



	//if (idUsercmdGenLocalManager::DBG_IsZoomBtnReleasedFlag && idUsercmdGenLocalManager::isButtonPressed(entity->playerController->rawUCmdTracker.usercmd.buttons, BUTTON_ZOOM)) {
	//	idUsercmdGenLocalManager::DBG_IsZoomBtnReleasedFlag = false;
	//}
	//else { //! if btn released
	//	idUsercmdGenLocalManager::DBG_IsZoomBtnReleasedFlag = true;
	//}
	

	/*static bool isToggleActive = false;


	idEntity* entity = (idEntity*)idPlayer_a1;
	idUsercmdGenLocalManager::DBG_CmdTracker1_Buttons = entity->playerController->ucmdTracker1.usercmd.buttons;

	if (isToggleActive) {
		if (idUsercmdGenLocalManager::isButtonPressed(entity->playerController->rawUCmdTracker.usercmd.buttons, BUTTON_ZOOM)) {
			isToggleActive = false;
		}
	}
	else {
		if (idUsercmdGenLocalManager::isButtonPressed(entity->playerController->rawUCmdTracker.usercmd.buttons, BUTTON_ZOOM)) {
			isToggleActive = true;
		}
	}


	if (isToggleActive) {
		idUsercmdGenLocalManager::setButtonFlag(entity->playerController->ucmdTracker1.usercmd.buttons, BUTTON_ZOOM, true);
	}*/



	//? forcing this for debug make sure to remove it when done !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//! this works !
	//idUsercmdGenLocalManager::setButtonFlag(entity->playerController->ucmdTracker1.usercmd.buttons, BUTTON_ZOOM, true);
	

}




typedef char(__fastcall* levelLoadCompleted_t)();
levelLoadCompleted_t p_levelLoadCompleted = nullptr;
levelLoadCompleted_t p_levelLoadCompleted_Target = nullptr;

char __fastcall levelLoadCompleted_Hook() {


	if (!idLightManager::setLightMaterialFromVec()) {
		logWarn("levelLoadCompleted_Hook: failed to find and assign any spot light material for flashlight...How could that happen????");
	}

	idLightManager::updateHeadLight();

	idLightManager::resetWasFlashlightOn();

	weaponsManager::updateDeclWeapons();

	return p_levelLoadCompleted();
}



WNDPROC pOriginalWndProc = nullptr;

LRESULT CALLBACK HookedWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (MenuStateManager::isNotMenu() && !idConsoleLocalManager::isConsoleOpened() && cachedCvarsManager::isWindowFocused()) {
		if (uMsg == WM_KEYDOWN) {
			if (wParam == ModSettingsManager::getNormalSpeedKeyCode()) {
				logInfo("HookedWndProc: user pressing reset game speed key");
				timescaleManager::resetSpeed();
			}
			else if (wParam == ModSettingsManager::getFastForwardKeyCode()) {
				logInfo("HookedWndProc: user pressing fast forward game speed key");
				timescaleManager::increaseSpeed();
			}
			else if (wParam == ModSettingsManager::getFlashLightKeyCode()) {
				if (idLightManager::shouldFlashLightBeOff()) {
					logWarn("preventing user from changing flashlight state to prevent screen glare");
				}
				else {
					idLightManager::toggleHeadLight();
				}
			}
			else if (wParam == ModSettingsManager::getHighFrameMvtFixKeyVkCode()) {
				idPlayerManager::triggerHighFramerateMvtFix();
			}
		}
	}
	return CallWindowProc(pOriginalWndProc, hwnd, uMsg, wParam, lParam);
}



////! void __fastcall PlayAnimByIndex_Smth(idAnimSysNode_PlayAnimByIndex* idAnimSysNode_PlayAnimByIndex_a1, __int64 a2, __int64 a3, _QWORD* a4)
//typedef void(__fastcall* PlayAnimByIndex_t)(void* idAnimSysNode_PlayAnimByIndex_a1, __int64 a2, __int64 a3, _QWORD* a4);
//PlayAnimByIndex_t p_PlayAnimByIndex_t = nullptr;
//PlayAnimByIndex_t p_PlayAnimByIndex_t_Target = nullptr;
//
//void __fastcall PlayAnimByIndex_t_Hook(void* idAnimSysNode_PlayAnimByIndex_a1, __int64 a2, __int64 a3, _QWORD* a4) {
//	
//
//
//
//	p_PlayAnimByIndex_t(idAnimSysNode_PlayAnimByIndex_a1, a2, a3, a4);
//}




//? useless to analyse cam sprint animation:
//typedef char(__fastcall* playerCameraSmth_t)(idPlayer* idplayer_a1, void*** a2, char a3);
//playerCameraSmth_t p_playerCameraSmth_t = nullptr;
//playerCameraSmth_t p_playerCameraSmth_t_Target = nullptr;
//
//char __fastcall playerCameraSmth_Hook(idPlayer* idplayer_a1, void*** a2, char a3) {
//	
//	static char lastA3 = -1;
//	static void*** lasta2 = nullptr;
//
//	if (a3 != lastA3) {
//		logInfo("playerCameraSmth_Hook: a3 has changed to: %d", a3);
//		lastA3 = a3;
//	}
//
//	if (a2 != lasta2) {
//		logInfo("playerCameraSmth_Hook: a2 has changed to: %p", a2);
//		lasta2 = a2;
//	}
//
//	return p_playerCameraSmth_t(idplayer_a1, a2, a3);
//}






//? this works but won't be using it atm check the alternative
//! this will check the firing state of the currently equipped weapon so we know when pm_animCamAmount should be set to default value
//typedef char(__fastcall* idPlayerWeaponStateSmth_t)(__int64 idPlayer_a1, __int64* struct_a2);
//idPlayerWeaponStateSmth_t p_idPlayerWeaponStateSmth = nullptr;
//idPlayerWeaponStateSmth_t p_idPlayerWeaponStateSmth_Target = nullptr;
//
//char __fastcall idPlayerWeaponStateSmth_Hook(__int64 idPlayer_a1, __int64* struct_a2) {
//	
//	static bool lastIsEquippedWeaponFiring = false;
//
//	__int64 curentlyEquippedIdWeapon = *(_QWORD*)(idPlayer_a1 + 0x1A38);
//
//	// ida
//	bool isWeaponFiring = (curentlyEquippedIdWeapon && !*(DWORD*)(curentlyEquippedIdWeapon + 4i64 * *(int*)(curentlyEquippedIdWeapon + 0x118) + 0x130));
//
//	if (isWeaponFiring != lastIsEquippedWeaponFiring) {
//		logInfo("weapon state has change and is now: %s", isWeaponFiring ? "firing" : "not firing");
//		lastIsEquippedWeaponFiring = isWeaponFiring;
//	}
//
//
//
//	return p_idPlayerWeaponStateSmth(idPlayer_a1, struct_a2);
//}


//? this func triggers all the time and keyNum will be K_JOY_TRIGGER1 and then K_JOY_TRIGGER2 the actual input don't matter so this is not really what we're looking for
//! RVA: 0xae5140 void __fastcall idUsercmdGenLocal_JoystickCheckSmth(__int64 idUsercmdGenLocal_a1, unsigned __int64 a2, keyNum_t* a3, float a4, float a5)
//typedef void(__fastcall* JoystickCheckSmth_t)(__int64 idUsercmdGenLocal_a1, unsigned __int64 a2, keyNum_t a3, float a4, float a5);
//JoystickCheckSmth_t p_JoystickCheckSmth_t = nullptr;
//JoystickCheckSmth_t p_JoystickCheckSmth_t_Target = nullptr;
//
//void __fastcall JoystickCheckSmth_t_Hook(__int64 idUsercmdGenLocal_a1, unsigned __int64 a2, keyNum_t a3, float a4, float a5) {
//	
//	idUsercmdGenLocalManager::debugLog_JoystickCheckSmth_t_Hook(idUsercmdGenLocal_a1, a2, a3, a4, a5);
//
//
//	p_JoystickCheckSmth_t(idUsercmdGenLocal_a1, a2, a3, a4, a5);
//}













































































































































































