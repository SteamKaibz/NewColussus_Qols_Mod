#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include "../ModSettings/ModSettingsManager.h"




class soundManager
{

private:
	static std::string m_skipBjRefStr;
	static std::string m_skipAnaRefStr;
	static std::string m_skipGraceRefStr;


public:

	static std::unordered_set<std::string> skipSoundsStrSet;

	static void updateFromUserSettings();
};

