#include "Config.h"

#define BUILD_DATE __DATE__ " " __TIME__


FILE* Config::fp;

 ModConfig Config::m_modConfig{ ModConfig::debug }; 

 buildType Config::m_buildType{ buildType::unknown };


 void Config::setBuildType(buildType type) {
	 m_buildType = type;
 }

 buildType Config::getBuildType() {
	 return m_buildType;
 }

 std::string Config::getBuildTypeAsStr() {
	 switch (m_buildType)
	 {
	 case buildType::unknown:
		 return "Mod Build: unknown.";
	 case buildType::dev:
		 return "Mod Build: Dev";
	 case buildType::nexusDebug:
		 return "Mod Build: Nexus Debug";
	 case buildType::nexusRelease:
		 return "Mod Build: Nexus Release";
	 default:
		 return "Mod Build: default case...How could that happen?";
	 }
 }


void Config::set(ModConfig debugVersion)
{
	

	loguru::g_preamble_thread = false;
	loguru::g_preamble_date = false;
	loguru::g_preamble_uptime = false;


	m_modConfig = debugVersion;
	
	bool isfreopen_sError = false;

	switch (m_modConfig)
	{
	
	case ModConfig::error:
		loguru::g_stderr_verbosity = loguru::Verbosity_OFF; 
		loguru::add_file(MOD_LOG_FILE_NAME.c_str(), loguru::Truncate, loguru::Verbosity_ERROR);
		break;
	case ModConfig::warn:
		loguru::g_stderr_verbosity = loguru::Verbosity_OFF;
		loguru::add_file(MOD_LOG_FILE_NAME.c_str(), loguru::Truncate, loguru::Verbosity_WARNING);
		break;
	case ModConfig::info:
		loguru::g_stderr_verbosity = loguru::Verbosity_OFF;
		loguru::add_file(MOD_LOG_FILE_NAME.c_str(), loguru::Truncate, loguru::Verbosity_INFO);
		break;
	case ModConfig::debug:
		loguru::g_stderr_verbosity = loguru::Verbosity_INFO;
		loguru::add_file(MOD_LOG_FILE_NAME.c_str(), loguru::Truncate, loguru::Verbosity_INFO);
		break;	
	default:
		loguru::g_stderr_verbosity = loguru::Verbosity_OFF;     			
		loguru::add_file(MOD_LOG_FILE_NAME.c_str(), loguru::Truncate, loguru::Verbosity_ERROR);	       
		logErr("Config::set: default condition, how did that happen ?!");
		break;
	}

	
	logInfo("Config::set: log level: %d", (int)debugVersion);

	


}




void Config::printHeaderInLogFile()
{
	if (Config::getBuildType() == buildType::nexusRelease) {
		logWarn(getLogHeaderString().c_str());
	}
	else {
		logInfo(getLogHeaderString().c_str());

	}
}



std::string Config::getLogHeaderString()
{
	std::string headerStr =
		"\n\n**********************************************************************************************\nThis is the log file. \nMod Name: " + MOD_FULL_NAME + "\n"
		+ getModVersionStr() + "\n"	
		+ getModConfigStr() + "\n"		
		+ "Mod Author: Kaibz" + "\n"
		+ "Date: " + getTimeDateStr() + " (Day/Month/Year format)" + "\n"
		+ "For more info on how the mod works, configuration, troubleshooting....Check Install.txt or contact mod author at the Nexus mod page. " + "\n"
		+ "**********************************************************************************************" + "\n\n"
		;

	return headerStr;
}




std::string Config::getTimeDateStr() {

	try
	{
		SYSTEMTIME localTime;
		GetLocalTime(&localTime);

		std::stringstream ss;
		ss << std::setfill('0');
		ss << std::setw(2) << localTime.wDay << '.' << std::setw(2) << localTime.wMonth << '.' << localTime.wYear;
		ss << ' ' << std::setw(2) << localTime.wHour << ':' << std::setw(2) << localTime.wMinute << ':' << std::setw(2) << localTime.wSecond;

		return ss.str();
	}
	catch (const std::exception& ex)
	{
		logErr("getTimeDateStr: %s", ex.what());
	}
	return "Error: could not get getTimeDateStr";
	
}



ModConfig Config::getConfig()
{
	return m_modConfig;
}


bool Config::isDevMode() {

	bool result = (m_modConfig == ModConfig::debug);
	return result;
}

std::string Config::getModVersionStr() {

	std::string result = std::to_string(MOD_VERSION_F);
	size_t dotPos = result.find('.');
	if (dotPos != std::string::npos) {
		result = result.substr(0, dotPos + 3);     
	}

	return "Mod Version: " + result;
}


std::string Config::getModConfigStr()
{

	switch (m_modConfig)
	{
	case ModConfig::debug:
		return "Log level: info (mode: dev/debug)";
	case ModConfig::info:
		return "Log level: info";
	case ModConfig::warn:
		return "Log level: warn";
	case ModConfig::error:
		return " level: error";
	case ModConfig::MAX_VERSIONS:
		return "Log level:: MAX_VERSIONS";
	default:
		return "Log level: default...why did this happen???!!!";
		break;
	}	
}

std::string Config::getModuleName()
{
	return GAME_FILE_NAME;
}



std::string Config::getGameFileNameToLowerStr()
{
	return GAME_FILE_NAME_TO_LOWER;
}









