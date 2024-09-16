#pragma once

#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // For std::hex and std::setw
#include <sstream> // For stringstream
#include <cstdint>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <regex>

#include "../Wolf2/TypeInfoManager.h"
#include "../K_Utils/K_Utils.h"



class IdaScriptsGen
{
private:

	std::set<std::string> m_uniqueClassNamesSet;
	unsigned int m_dupeCounter = 0;

	std::vector<std::string> m_uniqueEnumVarNamesVec;
	unsigned int m_dupeEnumVarsCounter = 0;


	//todo adapted data from meathook, me might change this later on
	int m_offset_typeinfo = -1;
	int m_offset_typeinfo2 = -1;


	static inline const char* g_idc_skipset[] = {
	"char",
	"unsigned char",
	"short",
	"unsigned short",
	"int",
	"unsigned int",
	"long",
	"unsigned long",
	"long long",
	"unsigned long long",
	"float",
	"double",
	"bool"
	};

	static inline std::set<std::string_view> g_fuckset{};

	static inline char opsbuffer[256];



public:

	void dumpIdaIdc();

	classTypeInfo_t* ClassTypes(unsigned& out_n, unsigned whichsource);

	enumTypeInfo_t* EnumTypes(unsigned& out_n, unsigned whichsource);

	bool should_skip_type(std::string_view typenam);

	std::string normalize_type_name(std::string_view input);

	std::string getGeneratedIdcPythonScriptStr();
};

