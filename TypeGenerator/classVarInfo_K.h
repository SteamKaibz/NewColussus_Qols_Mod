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

struct opsStruct {
	std::string ptrStr = "";
	std::string arrayStr = "";
	std::string defaultStr = "";
	
	std::string getStr() {
		return ptrStr + arrayStr + defaultStr;
	}
};

class classVarInfo_K
{
private:
	std::string m_type = "";
	opsStruct m_opsStruct;
	std::string m_ops = "";
	std::string m_name = "";
	std::string m_comment = "";               
	std::string m_declLine = "";
	int m_size = 0;
	
	void parse();
	void parseOps();
	void formatType();
	


public:
	classVarInfo_K(classVariableInfo_t* varInfo)
	{
		if (MemHelper::isBadReadPtr(varInfo)) {
			logErr("!!!!!!!!!!  classVarInfo_K: varInfo is bad ptr: %p Can not format !!!!!!!!!!!!!", varInfo);
			return;
		}
		m_type = varInfo->type;
		m_ops = varInfo->ops;
		m_name = varInfo->name;
		m_size = varInfo->size;
		
		parse();
	}

	std::string getDeclLine();
	std::string getCommentLine();
	void formatTypeV2();
	void formatTypeTo_C_Type();
};

