
#include "dllmain.h"



void ClearConsoleInputBuffer() {
	while (std::cin.peek() != EOF) {
		std::cin.ignore(1);
	}
}


bool initModDirectory() {
	if (!FileOp::CreateModDirectory()) {
		logErr("initModDirectory: failed to create directory");		
		return false;
	}
	return true;
}



bool isConflictingModExist() {

	try
	{
		std::wstring dinput8ModName = L"dinput8.dll";
		const std::string NewColossusTweaker_03_HashStr = "e1cf0d14ed12ba16511a9907285501b3";


		logInfo("Checking for conflicting mods...");
		std::filesystem::path currentPath = std::filesystem::current_path();
		std::string currentPathStr = currentPath.string();
		BYTE md5Hash[Md5Check::HASHSIZE];

		logInfo("listing files in game directory (%s)", currentPathStr.c_str());

		for (const auto& entry : std::filesystem::directory_iterator(currentPath))
		{
			std::filesystem::path filePath = entry.path();
			std::wstring fileNameToLowerWstr = K_Utils::WstrtoLower(filePath.filename().wstring());
			

			if (fileNameToLowerWstr == dinput8ModName)
			{				

				if (Md5Check::GetFileMD5Hash(filePath.c_str(), md5Hash))
				{

					std::string fileNameStr = K_Utils::wide_to_narrow(fileNameToLowerWstr);
					std::string hashAsStr = Md5Check::getHashArrayAsStr(md5Hash, Md5Check::HASHSIZE);
					if (hashAsStr == NewColossusTweaker_03_HashStr) {
						logErr("Found conflicting file: %s in game directory: %s (file hash: %s) ", fileNameStr.c_str(), currentPathStr.c_str(),  hashAsStr.c_str());
						return true;
					}
					logWarn("Found file called: %s mod in game directory, this file may conflict with the mod (or not)", fileNameStr.c_str());
				}				
			}	
			else {

				if (std::filesystem::is_directory(entry.status())) {
					logInfo("Found Directory: %ls in game directory", fileNameToLowerWstr.c_str());
				}
				else if (std::filesystem::is_regular_file(entry.status())) {
					logInfo("Found File: %ls in game directory", fileNameToLowerWstr.c_str());
				}
				else {
					logInfo("found Other: %ls in game directory", fileNameToLowerWstr.c_str());
				}

			}
			
		}
		logInfo("isConflictingModExist: found no existing conflicting mods");
		return false;
	}
	catch (const std::exception& ex)
	{
		logErr("isConflictingModExist catch error: %s mod should not be able to start.", ex.what());
		return true;
	}
}


void DisableWndProcHook(HWND hwnd) {
	SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)pOriginalWndProc);
}



void initImguiV2() {
	if (!ImGuiManager::isInitFlag()) return;

	if (ImGuiManager::isPreviousInitAttempt()) return;

	logInfo("initImguiV2: init process started..");
	logInfo("ImGui Rendering backend: %s\n", U::RenderingBackendToStr());
	MinHookManager::setInitializeStatus(MH_Initialize());

	if (!(MinHookManager::getInitializeStatus() == MH_OK || MinHookManager::getInitializeStatus() == MH_ERROR_ALREADY_INITIALIZED)) {
		auto statusStr = MH_StatusToString(MinHookManager::getInitializeStatus());
		logErr("initImguiV2: Failed to initialize MinHook. minhook status is: %s the mod will not work as it should please report to mod author with a log file.\n", statusStr);
	}
	else {
		H::Init();
	}
	ImGuiManager::setInitAttempt();

}


//? new version to handle people who can not use imgui: (the backup version is below)
void modInit() {

	logInfo("modInit: initializing json settings....");

	if (initModDirectory()) {
		Menu::LoadFromFile();
		ModSettingsManager::updateFromImGui(Menu::getSettings());
		Menu::logChangedJsonFile();

	}
	else {

		modStatus.setError();		
		return;
	}


	logInfo("modInit: waiting for MenuStateManager to initialize....");

	idCmdManager::init();

	idCvarManager::init();

	languageManager::LogGameLocalisation();

	logInfo("modInit: %s", idRenderModelGuiManager::getDisplayDbgInfoStr().c_str());

	while (MenuStateManager::get() == uninitialized || MenuStateManager::get() == undefined) {
		Sleep(100);
	}


	std::string gameVersionStr = BuildInfo::getBuildStr();
	logInfo("Game build version: %s", gameVersionStr.c_str());

}


//void modInit() {
//
//	logInfo("modInit: waiting for MenuStateManager to initialize....");
//
//	idCvarManager::setModInitCvars();
//
//	idCvarManager::setCriticalCvars();
//
//	languageManager::LogGameLocalisation();
//
//
//	logInfo("modInit: Game Window Width: %d Heigth: %d", cachedCvarsManager::get_WindowWidthInt(), cachedCvarsManager::get_WindowHeightInt());
//
//	while (MenuStateManager::get() == uninitialized || MenuStateManager::get() == undefined) {
//		Sleep(100);
//	}
//
//	
//	if (initModDirectory()) {
//		Menu::LoadFromFile();
//		ModSettingsManager::updateFromImGui(Menu::getSettings());
//		Menu::logChangedJsonFile();
//
//	}
//	else {
//		
//		modStatus.setError();
//	}
//
//
//	std::string gameVersionStr = BuildInfo::getBuildStr();
//	logInfo("Game build version: %s", gameVersionStr.c_str());
//
//	
//
//}


bool InitializeHooksV2() {
	
	logInfo("InitializeHooksV2 calling MH_Initialize() ");

	auto initStatus = MH_Initialize();

	auto initStatusStr = MH_StatusToString(initStatus);
	if (!(initStatus == MH_OK || initStatus == MH_ERROR_ALREADY_INITIALIZED)) {
		logErr("Failed to initialize MinHook. minhook status is: %s \n", initStatusStr);
		return false;
	}


	if (!modStatus.isAllGood()) {
		logErr("InitializeHooks: modStatus Error, can not create hooks.");
		return false;
	}

	p_idKeyboardSmth_t_Target = reinterpret_cast<idKeyboardSmth_t>(MemHelper::getFuncAddr(0xAE72A0));
	if (MH_CreateHook(reinterpret_cast<void**>(p_idKeyboardSmth_t_Target), &idKeyboardSmth_Hook, reinterpret_cast<void**>(&p_idKeyboardSmth_t)) != MH_OK) {
		logErr("Failed to create p_idKeyboardSmth_t_Target hook.");
		return false;
	}
	p_idMenuManager_Shell_Update_t_Target = reinterpret_cast<idMenuManager_Shell_Update_t>(MemHelper::getFuncAddr(0x39A410));
	if (MH_CreateHook(reinterpret_cast<void**>(p_idMenuManager_Shell_Update_t_Target), &idMenuManager_Shell_Update_Hook, reinterpret_cast<void**>(&p_idMenuManager_Shell_Update_t)) != MH_OK) {
		logErr("Failed to create p_idMenuManager_Shell_Update_t_Target hook.");
		return false;
	}

	p_drawChar_MB_5280B0_t_Target = reinterpret_cast<drawChar_MB_5280B0_t>(MemHelper::getFuncAddr(0x5280B0));
	if (MH_CreateHook(reinterpret_cast<void**>(p_drawChar_MB_5280B0_t_Target), &drawChar_Hook, reinterpret_cast<void**>(&p_drawChar_MB_5280B0_t)) != MH_OK) {
		logErr("Failed to create p_drawChar_MB_5280B0_t_Target hook.");
		return false;
	}

	p_perfMetricsDrawGraphs_Target = reinterpret_cast<perfMetricsDrawGraphs_t>(MemHelper::getFuncAddr(0xA991E0));
	if (MH_CreateHook(reinterpret_cast<void**>(p_perfMetricsDrawGraphs_Target), &perfMetricsDrawGraphs_Hook, reinterpret_cast<void**>(&p_perfMetricsDrawGraphs)) != MH_OK) {
		logErr("Failed to create p_perfMetricsDrawGraphs_Target hook.");
		return false;
	}

	p_soundEventSmth_Target = reinterpret_cast<soundEventSmth_t>(MemHelper::getFuncAddr(0xB79A70));
	if (MH_CreateHook(reinterpret_cast<void**>(p_soundEventSmth_Target), &soundEventSmth_Hook, reinterpret_cast<void**>(&p_soundEventSmth)) != MH_OK) {
		logErr("Failed to create soundEventSmth_B79A70 hook.");
		return false;
	}

	p_swf_RenderEditTex_Target = reinterpret_cast<swf_RenderEditTex_t>(MemHelper::getFuncAddr(0x874CD0));
	if (MH_CreateHook(reinterpret_cast<void**>(p_swf_RenderEditTex_Target), &swf_RenderEditTex_Hook, reinterpret_cast<void**>(&p_swf_RenderEditTex)) != MH_OK) {
		logErr("Failed to create swf_RenderEditTex hook.");
		return false;
	}

	p_guiModel_idDevGuiSmth_Target = reinterpret_cast<guiModel_idDevGuiSmth_t>(MemHelper::getFuncAddr(0x1022230));
	if (MH_CreateHook(reinterpret_cast<void**>(p_guiModel_idDevGuiSmth_Target), &guiModel_idDevGuiSmth_Hook, reinterpret_cast<void**>(&p_guiModel_idDevGuiSmth)) != MH_OK) {
		logErr("Failed to create guiModel_idDevGuiSmth hook.");
		return false;
	}


	p_renderParm_769CE0_Target = reinterpret_cast<renderParm_769CE0_t>(MemHelper::getFuncAddr(0x769CE0));
	if (MH_CreateHook(reinterpret_cast<void**>(p_renderParm_769CE0_Target), &renderParm_769CE0_Hook, reinterpret_cast<void**>(&p_renderParm_769CE0)) != MH_OK) {
		logErr("Failed to create renderParm_769CE0 hook.");
		return false;
	}

	p_showHudAndCrosshair_FAA460_Target = reinterpret_cast<showHudAndCrosshair_FAA460_t>(MemHelper::getFuncAddr(0xFAA460));
	if (MH_CreateHook(reinterpret_cast<void**>(p_showHudAndCrosshair_FAA460_Target), &showHudAndCrosshair_FAA460_Hook, reinterpret_cast<void**>(&p_showHudAndCrosshair_FAA460)) != MH_OK) {
		logErr("Failed to create showHudAndCrosshair_FAA460 hook.");
		return false;
	}

	
	p_idPlayer_UseCheck_Target = reinterpret_cast<idPlayer_UseCheck_t_FEB3E0>(MemHelper::getFuncAddr(0xFEB3E0));
	if (MH_CreateHook(reinterpret_cast<void**>(p_idPlayer_UseCheck_Target), &idPlayer_UseCheck_Hook, reinterpret_cast<void**>(&p_idPlayer_UseCheck)) != MH_OK) {
		logErr("Failed to create p_idPlayer_UseCheck_Target hook.");
		return false;
	}

	pIdLib_PrintfTarget = reinterpret_cast<IdLib_Printf>(MemHelper::getFuncAddr(0x1238530));
	if (MH_CreateHook(reinterpret_cast<void**>(pIdLib_PrintfTarget), &IdLib_PrintfHook_1238530, reinterpret_cast<void**>(&pIdLib_Printf)) != MH_OK) {
		logErr("Failed to create pIdLib_PrintfTarget hook.");
		return false;
	}

	p_closeIdConsoleSmth_A8D1E0_Target = reinterpret_cast<closeIdConsoleSmth_A8D1E0_t>(MemHelper::getFuncAddr(0xA8D1E0));
	if (MH_CreateHook(reinterpret_cast<void**>(p_closeIdConsoleSmth_A8D1E0_Target), &closeIdConsoleSmth_A8D1E0_Hook, reinterpret_cast<void**>(&p_closeIdConsoleSmth_A8D1E0)) != MH_OK) {
		logErr("Failed to create closeIdConsoleSmth_A8D1E0_Target hook.");
		return false;
	}


	p_idPlayerHandleZoomSmth_Target = reinterpret_cast<idPlayerHandleZoomSmth_t>(MemHelper::getFuncAddr(0xFEC6B0));
	if (MH_CreateHook(reinterpret_cast<void**>(p_idPlayerHandleZoomSmth_Target), &idPlayerHandleZoomSmth_Hook, reinterpret_cast<void**>(&p_idPlayerHandleZoomSmth)) != MH_OK) {
		logErr("Failed to create p_idPlayerHandleZoomSmth_Target hook.");
		return false;
	}

	p_levelLoadCompleted_Target = reinterpret_cast<levelLoadCompleted_t>(MemHelper::getFuncAddr(0xAAC570));
	if (MH_CreateHook(reinterpret_cast<void**>(p_levelLoadCompleted_Target), &levelLoadCompleted_Hook, reinterpret_cast<void**>(&p_levelLoadCompleted)) != MH_OK) {
		logErr("Failed to create p_levelLoadCompleted_Target hook.");
		return false;
	}


	p_GoingFromMainMenuToInGame_Target = reinterpret_cast<goingFromMainMenuToInGame_t>(MemHelper::getFuncAddr(0x398A30));
	if (MH_CreateHook(reinterpret_cast<void**>(p_GoingFromMainMenuToInGame_Target), &goingFromMainMenuToInGame_Hook, reinterpret_cast<void**>(&p_GoingFromMainMenuToInGame)) != MH_OK) {
		logErr("Failed to create GoingFromMainMenuToInGame_Target hook.");
		return false;
	}

	p_RenderSpriteInstanc_Target = reinterpret_cast<RenderSpriteInstance_t>(MemHelper::getFuncAddr(0x871C50));
	if (MH_CreateHook(reinterpret_cast<void**>(p_RenderSpriteInstanc_Target), &RenderSpriteInstance_Hook, reinterpret_cast<void**>(&p_RenderSpriteInstanc)) != MH_OK) {
		logErr("Failed to create p_RenderSpriteInstanc_Target hook.");
		return false;
	}



	p_colorSmgh_Target = reinterpret_cast<colorSmgh_t>(MemHelper::getFuncAddr(0x38CFD0));
	if (MH_CreateHook(reinterpret_cast<void**>(p_colorSmgh_Target),
		&colorSmgh_Hook,
		reinterpret_cast<void**>(&p_colorSmgh)) != MH_OK) {
		logErr("Failed to create colorSmgh_Target hook.");
		return false;
	}


	p_processInput_t_Target = reinterpret_cast<processInput_t>(MemHelper::getFuncAddr(0xFF8640));
	if (MH_CreateHook(reinterpret_cast<void**>(p_processInput_t_Target), &processInput_t_Hook, reinterpret_cast<void**>(&p_processInput_t)) != MH_OK) {
		logErr("Failed to create p_processInput_t_Target hook.");
		return false;
	}


	p_getLocalisedStrAddrMB_Target = reinterpret_cast<getLocalisedStrAddrMB_t>(MemHelper::getFuncAddr(0x121D500));
	if (MH_CreateHook(reinterpret_cast<void**>(p_getLocalisedStrAddrMB_Target), &getLocalisedStrAddrMB_Hook, reinterpret_cast<void**>(&p_getLocalisedStrAddrMB)) != MH_OK) {
		logErr("Failed to create p_getLocalisedStrAddrMB_Target hook.");
		return false;
	}


	p_SendKeySmth_t_Target = reinterpret_cast<idUsercmdGenLocal_SendKeySmth_t>(MemHelper::getFuncAddr(0xAE6FE0));
	if (MH_CreateHook(reinterpret_cast<void**>(p_SendKeySmth_t_Target), &SendKeySmth_t_Hook, reinterpret_cast<void**>(&p_SendKeySmth_t)) != MH_OK) {
		logErr("Failed to create SendKeySmth_t hook.");
		return false;
	}







	/*p_JoystickCheckSmth_t_Target = reinterpret_cast<JoystickCheckSmth_t>(MemHelper::getFuncAddr(0xae5140)); 
	if (MH_CreateHook(reinterpret_cast<void**>(p_JoystickCheckSmth_t_Target), &JoystickCheckSmth_t_Hook, reinterpret_cast<void**>(&p_JoystickCheckSmth_t)) != MH_OK) {
		logErr("Failed to create JoystickCheckSmth_t hook.");
		return false;
	}*/

	


	//p_playerCameraSmth_t_Target = reinterpret_cast<playerCameraSmth_t>(MemHelper::getFuncAddr(0xff4340));
	//if (MH_CreateHook(reinterpret_cast<void**>(p_playerCameraSmth_t_Target), &playerCameraSmth_Hook, reinterpret_cast<void**>(&p_playerCameraSmth_t)) != MH_OK) {
	//	logErr("Failed to create p_playerCameraSmth_t_Target hook.");
	//	return false;
	//}


	//p_idPlayerWeaponStateSmth_Target = reinterpret_cast<idPlayerWeaponStateSmth_t>(MemHelper::getFuncAddr(0xFD31D0));
	//if (MH_CreateHook(reinterpret_cast<void**>(p_idPlayerWeaponStateSmth_Target), &idPlayerWeaponStateSmth_Hook, reinterpret_cast<void**>(&p_idPlayerWeaponStateSmth)) != MH_OK) {
	//	logErr("Failed to create idPlayerWeaponStateSmth_Target hook.");
	//	return false;
	//}





	pOriginalWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWLP_WNDPROC, (LONG_PTR)&HookedWndProc);	



	

	Sleep(100);    

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		logErr("InitializeHooksV2: MH_EnableHook: Enabling all hooks failed.");
		return false;
	}


	logInfo("Hooks successfully created and enabled.\n");
	return true;
}





DWORD __stdcall EjectThread(LPVOID lpParameter) {
	Sleep(100);
	FreeLibraryAndExitThread(DllHandle, 0);
}








bool findGameWindow(std::string windowName) {
	uint64_t waitStartMs = K_Utils::EpochMillis();
	uint64_t timeoutMs = 10000;


	logInfo("findGameWindow: searching for %s window Please wait...", windowName.c_str());
	while (hWindow == NULL && ((K_Utils::EpochMillis() - waitStartMs) < timeoutMs))
	{
		hWindow = FindWindowA(windowName.c_str(), NULL);
		Sleep(20);
	}
	if (hWindow == NULL) {
		logErr("findGameWindow: failed to find Window: %s Mod can not start", windowName.c_str());
		return false;
	}

	logInfo("findGameWindow: Succes Finding  Window: %s", windowName.c_str());
	return true;
}



DWORD WINAPI ModMain() {

	Console::Enable();
	
	//? this about updating mod version if you update.
	Config::setBuildType(buildType::dev);  //! dev, nexusDebug, nexusRelease   


	//! this could and sould be simplified....
	if (Config::getBuildType() == buildType::dev) {
		Config::set(ModConfig::debug);
		logWarn("this is dev build, logging level set to info + some extras.");
	}
	else if (Config::getBuildType() == buildType::nexusDebug) {
		Config::set(ModConfig::info);
		logWarn("this is nexusDebug build, logging level set to info level.");		
	}
	else if (Config::getBuildType() == buildType::nexusRelease){
		Config::set(ModConfig::warn);
		logWarn("this is nexusRelease build, logging level set to warn level.");		
	}
	else {
		Config::set(ModConfig::info);
		logWarn("Could not find mod builType, setting it to info");
	}


	logWarn("\n*\nIF THE MOD IS NOT WORKING CORRECTLY FOR YOU, DISABLE ANY GUIS LIKE DISCORD, AFTER BURNER, RIVA TUNER, NIVIDA, AMD....AND SEE IT IF FIXES THE PROBLEM AS THIS HAS BEEN THE CASES FOR OTHER USERS\n*");
	

	Config::printHeaderInLogFile();



	if (isConflictingModExist()) {
		modStatus.setError();
	}

	modStatus.logModStatus();


	if (modStatus.isAllGood() && !mem.isGameFileNameValid(Config::getGameFileNameToLowerStr())) {
		logErr("ModMain: exe file name incorect, mod can not start.");
		modStatus.setError();
	}

	if (modStatus.isAllGood()) {		
		if (!findGameWindow(Config::GAME_WINDOW_NAME)) {
			modStatus.setError();         
		}
		else {
			uintptr_t mainModuleAddr = MemHelper::getModuleBaseAddr();
			if (mainModuleAddr == NULL) {
				logErr("Module base address is: NULL, mod can not start!");
				modStatus.setError();
			}
			else {
				logInfo("Module base address is: %p", (void*)mainModuleAddr);
			}
		}		
	}

	
	if (modStatus.isAllGood() && !Scanner::fastGetAddressesAndPatch()) {
		logErr("fastGetAddressesAndPatch: failed.");
		modStatus.setError();
	}


	if (modStatus.isAllGood() && !InitializeHooksV2()) {
		modStatus.setError();
	}


	if (modStatus.isAllGood()) {
		modInit();	       	
	}


	
	
	if (ModSettingsManager::isModLoadBeep() || Config::isDevMode()) {
		if (modStatus.isAllGood()) {
			logInfo("PlayModLoadSuccesBeeps is called so beeps should be heard.... ");
			K_Utils::PlayModLoadSuccesBeeps();              
		}
	}

	if (!modStatus.isAllGood()) {
		TTS::addToQueue(sayErrorCheckLog);
		logErr("ERROR: MOD CAN NOT START !");
	}
		

	if (g_sleepTimeMainLoopMs <= 0) {
		logWarn(" g_sleepTimeMainLoopMs val: %u", g_sleepTimeMainLoopMs);
	}
	else {
		logInfo(" g_sleepTimeMainLoopMs val: %u ", g_sleepTimeMainLoopMs);
	}	


	/*if (Config::IsForceNoModUi) {
		logWarn("");
		logWarn("g_isForceNoUI is true, user will not be able be able to use mod UI in the game");
		logWarn("g_isForceNoUI is true, user will not be able be able to use mod UI in the game");
		logWarn("g_isForceNoUI is true, user will not be able be able to use mod UI in the game");
		logWarn("g_isForceNoUI is true, user will not be able be able to use mod UI in the game");
		logWarn("");
	}*/

	

	uint64_t lastGetAsyncKeyPressMs = 0;
	uint64_t lastdebugUseSystemPrintMs = 0;
	uint64_t lastIniFileWatcherCheckMs = 0;
	uint64_t lastHighFpxFixCheckMs = 0;
	uint64_t lastDwCheckMs = 0; //! dual wield	
	bool istryCacheGameFireKeysBindsFirstTime = true;;
	
	gameState_t lastGameState = GAMESTATE_UNINITIALIZED;

	uint64_t lastAutoMaterialTestMs = 0;
	bool isAutoMaterialTest = false;


	while (true) {

		Sleep(g_sleepTimeMainLoopMs);                 


		TTS::sayAllInQueue();          

		if (!modStatus.isAllGood()) {     					
			if (Config::isDevMode() && GetAsyncKeyState(VK_NUMPAD0) && ((K_Utils::EpochMillis() - g_lastGetAsyncKeyPress) > 500)) {
				g_lastGetAsyncKeyPress = K_Utils::EpochMillis();
				logInfo("DEBUG: user just pressed  VK_NUMPAD0: attempting to Unload Mod...");
				break;
			}
			continue;                     
		}

		gameState_t gameState = idGameLocalManager::getGameState();
		if (gameState != lastGameState) {

			std::string GameStateLastEnumStateStr = TypeInfoManager::getEnumMemberName("gameState_t", lastGameState);
			std::string GameStateEnumStateStr = TypeInfoManager::getEnumMemberName("gameState_t", gameState);

			logInfo("Main: gamestate has changed from: %s to %s", GameStateLastEnumStateStr.c_str(), GameStateEnumStateStr.c_str());

			lastGameState = gameState;
		}
		
		//! if the game is loading/unloading a map just wait 
		if ((gameState != GAMESTATE_ACTIVE) && (gameState != GAMESTATE_NOMAP)) {
			continue;
		}

		//! wait until game menu is initialized before imgui init
		//? adding an extra static bool to force no ui and hopefully help issues with user who can not get a json file generated and as a result can not use the mod.
		if (ModSettingsManager::getIsUseImgui() && ImGuiManager::isInitFlag()) {
			initImguiV2();         
		}

		//todo will the focus work if the option win_pauseOnAltTab  is on/off?
		if (MenuStateManager::isNotMenu() && cachedCvarsManager::isWindowFocused()) {
			
			
			//gameState_t gameState = idGameLocalManager::getGameState();
			//logInfo("dbg: logging gamestate for crash study: %d", idGameLocalManager::getGameState());

			//! trying this version instead
			ADS_Manager::checkZoomBtnStateFromCmdTracker();		

		}	

		if (K_Utils::EpochMillis() - lastAutoMaterialTestMs > 100) {


			idMaterialManager::autoShowMaterialStartingWith("textures/guis/extra");


			lastAutoMaterialTestMs = K_Utils::EpochMillis();
		}

		

		//? 20/9/24 not needed anymore
		////! one way to make sure the 'swap keys for dw' mod features is initialized
		//if (istryCacheGameFireKeysBindsFirstTime) {

		//	if (!idUsercmdGenLocalManager::isFireKeysBindsSet()) {
		//		idUsercmdGenLocalManager::tryCacheGameFireKeysBinds();
		//	}
		//	istryCacheGameFireKeysBindsFirstTime = false;
		//}

		//! 23/8/24 adding this to fix the player stuck on ledges at high framerate. we could potentially make this system trigger automatically but it will do for now.
		if (K_Utils::EpochMillis() - lastHighFpxFixCheckMs > 50) {

			idPlayerManager::checkForHighFramerateMvtFixTimerEnd();

			lastHighFpxFixCheckMs = K_Utils::EpochMillis();
		}

		
		

		if (Config::isDevMode()) {

			if (GetAsyncKeyState(VK_NUMPAD0) && ((K_Utils::EpochMillis() - g_lastGetAsyncKeyPress) > 500)) {
				g_lastGetAsyncKeyPress = K_Utils::EpochMillis();
				logInfo("DEBUG: user just pressed  VK_NUMPAD0: attempting to Unload Mod...");
				break;
			}

			if (GetAsyncKeyState(VK_NUMPAD1) && ((K_Utils::EpochMillis() - g_lastGetAsyncKeyPress) > 300)) {
				g_lastGetAsyncKeyPress = K_Utils::EpochMillis();
				logInfo("secret Debug: user just pressed  VK_NUMPAD1 : dumping class defs:");

				TTS::addToQueue(sayGeneratingTypes);

				//! leave those:
				EnumsDefFileGenerator::DumpEnumDefs();
				ClassDefFileGenerator::dumpClassDefs();

				/*idEventManager::listAllEventsToFile();
				idEventManager::generateEventNumsEnumFile();
				idEventManager::generateEventNumsEnumFileFor_0xcb58c0();*/

				/*IdaScriptsGen gen;
				gen.dumpIdaIdc();*/

			}


			if (GetAsyncKeyState(VK_NUMPAD2) && ((K_Utils::EpochMillis() - g_lastGetAsyncKeyPress) > 300)) {
				g_lastGetAsyncKeyPress = K_Utils::EpochMillis();
				logInfo("DEBUG: user just pressed  VK_NUMPAD2");			
				

				Menu::bShowDebugWindow = !Menu::bShowDebugWindow;

			}

			if (GetAsyncKeyState(VK_NUMPAD3) && ((K_Utils::EpochMillis() - g_lastGetAsyncKeyPress) > 300)) {
				g_lastGetAsyncKeyPress = K_Utils::EpochMillis();
				
				logInfo("DEBUG: user just pressed  VK_NUMPAD3");

				k_tests.PrintIdPlayerInfo();

				idLightManager::debugGetLastHeadLightPtr();

				std::string currentMapName = idGameLocalManager::getCurrentMapName();
				logInfo("currentMapName: %s", currentMapName.c_str());
				
				cachedCvarsManager::debugLogWin_hasFocusCvar();

				logInfo("IdHudInfo ptr: %p", idPlayerManager::getIdHudInfo());

				idCVar* animCamAmountCvar = (idCVar*)idCvarManager::getCvarPtr("pm_animCamAmount");
				logInfo("animCamAmountCvar: %p", animCamAmountCvar);


				idPlayerManager::Dbg_LogPreMoveAdd();

				hudManager::debugLogWeaponInfo();

			}

			if (GetAsyncKeyState(VK_NUMPAD4) && ((K_Utils::EpochMillis() - g_lastGetAsyncKeyPress) > 300)) {
				g_lastGetAsyncKeyPress = K_Utils::EpochMillis();

				logInfo("DEBUG: user just pressed  VK_NUMPAD4");


				Menu::bTEMPisShowStats = !Menu::bTEMPisShowStats;
					

				//idResourceManager::debugLogResourceListForClsName("idDeclSwfJournalResource");

			}

			if (GetAsyncKeyState(VK_NUMPAD5) && ((K_Utils::EpochMillis() - g_lastGetAsyncKeyPress) > 300)) {
				g_lastGetAsyncKeyPress = K_Utils::EpochMillis();



				//idResourceList* resList = idResourceManager::getResourceListPtrForClsName("idDeclDevMenuList");
				idResourceList* resList = idResourceManager::getResourceListPtrForClsName("idMaterial");
				logInfo("resList: %p", resList);

					//! keep findClassInfo:
				//classTypeInfo_t* clsInfoPtr = TypeInfoManager::findClassInfo("idMessageCallback");
				//logInfo("clsInfoPtr: %p", clsInfoPtr);			

				

			}

			if (GetAsyncKeyState(VK_NUMPAD7) && ((K_Utils::EpochMillis() - g_lastGetAsyncKeyPress) > 300)) {
				g_lastGetAsyncKeyPress = K_Utils::EpochMillis();

				isAutoMaterialTest = !isAutoMaterialTest;
				logInfo("VK_NUMPAD7: isAutoMaterialTest: %d", isAutoMaterialTest);

				//idMaterialManager::testMaterialPrev();

			}

			if (GetAsyncKeyState(VK_NUMPAD9) && ((K_Utils::EpochMillis() - g_lastGetAsyncKeyPress) > 300)) {
				g_lastGetAsyncKeyPress = K_Utils::EpochMillis();

				//idMaterialManager::testMaterialNext();

			}

			
		}	     
	}

	logInfo("debug shutdown");

	H::bShuttingDown = true;
	H::Free();
	DisableWndProcHook(hWindow);    

	MH_Uninitialize();      
	
	
	K_Utils::PlayModUnloadedBeeps();
	logInfo("attemting to exit mod...");
	CreateThread(0, 0, EjectThread, 0, 0, 0);		
	
	return 0;
}



DWORD WINAPI OnProcessDetach(LPVOID lpParam) {
	Console::Hide();

	
	return 0;
}



extern "C" BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);


	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		DllHandle = hModule;
		DisableThreadLibraryCalls(hModule);

		U::SetRenderingBackend(VULKAN);

		HANDLE hHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ModMain, DllHandle, 0, NULL);
		if (hHandle != NULL) {
			CloseHandle(hHandle);
		}
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH && !lpReserved) {
		OnProcessDetach(NULL);
	}

	return TRUE;











}

