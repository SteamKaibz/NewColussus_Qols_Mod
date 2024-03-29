#pragma once

#include <Windows.h>
#include <filesystem>  
#include <string>
#include <Shlwapi.h>     
#pragma comment(lib, "Shlwapi.lib")
#include <Psapi.h>
#include "../Config/Config.h"



class FileOp
{
private:

	static std::string m_modDirectoryPathStr;

	static std::string m_modSettingsFilePath;

public:

	static std::string GetModulePath();

	static bool acquireGameDirectoryPath(const char* moduleName);

	static std::string GetModuleDirectory();

	static bool CreateModDirectory();

	static std::string getModSettingsFilePath();

	static std::string getGameDirectoryPath(const char* moduleName);

};

