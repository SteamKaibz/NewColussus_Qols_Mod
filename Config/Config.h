#pragma once

#include <windows.h>
#include <string>
#include <iostream>
#include <format>
#include "../Loguru/loguru.hpp"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "../Voice/Voice.h"
#include <filesystem>


#ifndef logDebug
#define logDebug(...) VLOG_F(loguru::Verbosity_1 , __VA_ARGS__)
#endif 

#ifndef logInfo
#define logInfo(...) VLOG_F(loguru::Verbosity_0 , __VA_ARGS__)
#endif  

#ifndef logWarn
#define logWarn(...) VLOG_F(loguru::Verbosity_WARNING , __VA_ARGS__)
#endif  

#ifndef logErr
#define logErr(...) VLOG_F(loguru::Verbosity_ERROR , __VA_ARGS__)
#endif  


enum class ModConfig
{
	error = 0,
	warn,
	info,
	debug = 666,
	MAX_VERSIONS	
	
};

enum class buildType {
	unknown,
	dev,
	nexusDebug,
	nexusRelease
};





class Config
{
private:
	static buildType m_buildType;
	static ModConfig m_modConfig;
	static FILE* fp;



public:


	

	static const inline float MOD_VERSION_F = 2.1f;

	static const inline std::string MOD_FOLDER_NAME = "KaibzMod";

	static const inline std::string MOD_FULL_NAME = "New Colossus Advanced Options (KaibzMod)";

	static const inline std::string MOD_FILE_NAME = "XINPUT1_3.dll";

	static const inline std::string MOD_LOG_FILE_NAME = "KaibzMod_Log.txt";

	static const inline std::string MOD_SETTINGS_FILE_NAME = "modSettings.json";

	static const inline std::string GAME_FILE_NAME = "NewColossus_x64vk.exe";

	static const inline std::string GAME_FILE_NAME_TO_LOWER = "newcolossus_x64vk.exe";	
	
	static const inline std::string GAME_WINDOW_NAME = "Wolfenstein II The New Colossus";










	static buildType getBuildType();
	static std::string getBuildTypeAsStr();
	static void setBuildType(buildType type);

	static void set(ModConfig config);

	static std::string getModuleName();
	static std::string getModVersionStr();
	static ModConfig getConfig();
	static std::string getModConfigStr();
	static bool isDevMode();
	static std::string getGameFileNameToLowerStr();

	static void printHeaderInLogFile();
	static std::string getLogHeaderString();
	static std::string getDatedBuildStr();    
	static std::string getTimeDateStr();
	static int getShortModVersionAsInt();
	static double getShortModVersionAsDouble();
	static std::string getShortModVersionAsString();   
	static bool isSecretMaxVerboseDebugLevel;




};



