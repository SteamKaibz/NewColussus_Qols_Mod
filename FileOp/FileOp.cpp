#include "FileOp.h"


std::string FileOp::m_modDirectoryPathStr = "";
std::string FileOp::m_modSettingsFilePath = "";



std::string FileOp::getGameDirectoryPath(const char* moduleName) {
	HMODULE hModules[1024];
	DWORD cbNeeded;

	if (EnumProcessModules(GetCurrentProcess(), hModules, sizeof(hModules), &cbNeeded)) {
		for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
			char szModule[MAX_PATH];

			if (GetModuleFileNameExA(GetCurrentProcess(), hModules[i], szModule, sizeof(szModule) / sizeof(char))) {
				if (strstr(szModule, moduleName) != nullptr) {
					std::string fullPath(szModule);
					std::size_t found = fullPath.find_last_of("\\/");
					std::string directoryStr = fullPath.substr(0, found);

					logInfo("acquireGameDirectoryPath: found path for %s : %s directory is: %s", moduleName, szModule, directoryStr.c_str());
					return directoryStr;       
				}
			}
		}
	}
	logErr("acquireGameDirectoryPath: Failed to find game file: %s returning empty string", moduleName);
	return std::string();

}



bool FileOp::CreateModDirectory() {

	std::string gameDirectoryPathStr = getGameDirectoryPath(Config::GAME_FILE_NAME.c_str());
	if (gameDirectoryPathStr.empty()) {
		logErr("CreateModDirectory: can not create mod directory");
		return false;
	}
    m_modDirectoryPathStr = gameDirectoryPathStr + "\\" + Config::MOD_FOLDER_NAME;
    if (!PathFileExists(m_modDirectoryPathStr.c_str())) {
        bool createDirResult = CreateDirectory(m_modDirectoryPathStr.c_str(), NULL) != 0;
		if (!createDirResult) {
			logErr("CreateModDirectory: failed to create mod directory: %s", m_modDirectoryPathStr.c_str());
			return false;
		}
		else {
			logInfo("CreateModDirectory: succes creating mod directory: %s", m_modDirectoryPathStr.c_str());
		}
    }

    logInfo("CreateModDirectory: not creating directory %s cause it already exists.", m_modDirectoryPathStr.c_str());
    return true;    
}

std::string FileOp::getModSettingsFilePath()
{
	if (m_modDirectoryPathStr.empty()) {
		CreateModDirectory();		
	}
    return m_modDirectoryPathStr + "\\" + Config::MOD_SETTINGS_FILE_NAME;
}
