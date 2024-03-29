#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <filesystem>
#include <regex>
#include "../K_Utils/K_Utils.h"
#include "../Config/Config.h"
#include "../Wolf2/TypeInfoManager.h"
#include "varInfoCustom.h"
#include "classVarInfo_K.h"


class idLibGenerator {

private:

	std::set<std::string> m_debugClsTypeAndNameSet;
	std::set<std::string> m_debugOpsSet;
	std::set<std::string> m_debugTypesSet;

	std::set<std::string> m_uniqueClassNamesSet;
	unsigned int m_dupeCounter = 0;

	std::vector<std::string> m_uniqueEnumVarNamesVec;
	unsigned int m_dupeEnumVarsCounter = 0;

	std::string m_idLibClassesFileName = "Wolf2_idLib_Cls.txt";
	std::string m_idLibEnumsFileName = "Wolf2_idLib_Enums.txt";

	std::string m_idaProLib_ClassesFileName = "Wolf2_idaPro_Classes_Types.txt";
	std::string m_idaProLib_EnumsFileName = "Wolf2_idaPro_Enums_Types.txt";


	std::string m_idaIdbStringsFileName = "Wolf2_Ida_Strings_no_Duplicate.txt";

		


public:	

	std::string getClsInfoAsText(classTypeInfo_t* clsTypeInfoPtr);
	std::string getClsInfoAsTextV3(classTypeInfo_t* clsTypeInfoPtr); 
	
	
	std::string getUniqueEnumVarName(std::string enumVarName);

	std::string getEnumInfoAsText(enumTypeInfo_t* enumTypeInfoPtr);

	void generateIdLibFilesV2();         
	void generateIdaPro_C_Lib();
	void generateIdaProc_C_Lib_Test(std::string clasName);

	void debugPrint();
	

};
