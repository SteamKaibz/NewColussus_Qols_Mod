#pragma once

#include <windows.h>
#include <chrono>
#include <Psapi.h>
#include <mmsystem.h>
#include <string>
#include <locale>
#include <codecvt>
#include <thread>
#include <string_view>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <filesystem>
#include "../Config/Config.h"




class K_Utils {

private:

	static std::set<std::string> uniqueAppNames;

public:

	static bool IsBitSet(int value, int bitPosition); 

	static uint64_t EpochMillis();

	static std::string unicode_to_utf8(wchar_t* wide_string);

	static std::string getBuildDate();

	static void PlayModLoadSuccesBeeps();

	static void PlayModUnloadedBeeps();

	static std::wstring StandardKeyToStringW(DWORD VKey);

	static std::string wide_to_narrow(const std::wstring& wide_str);

	static std::wstring WstrtoLower(const std::wstring& input);

	static std::string intToHexString(__int64 decimalValue);

	static bool saveSetToFile(std::string fileName, std::set<std::string> StrSet);
	static bool saveVecToFile(std::string fileName, std::vector<std::string> StrVec);

	static void removeDuplicates(const std::string& inputFilePath, const std::string& outputFilePath);

	static std::set<std::string> loadFileToSet(std::string inputFilePath);

};














