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
#include "../MemHelper/MemHelper.h"


class classTypeInfo_K
{
private:
	std::string m_superTypeName = "";
	int m_superTypeSize = 0;

	std::string m_name = "";
	std::string m_comment = "";               
	int m_size = 0;

	std::string parseClsName(std::string input, bool isSuperCls);

	static std::vector<std::string> m_classNamesVec;

public:
	classTypeInfo_K(classTypeInfo_t* typeInfoPtr)
	{
		if (MemHelper::isBadReadPtr(typeInfoPtr)) {
			logErr("!!!!!!!!!!  classTypeInfo_K: typeInfoPtr is bad ptr: %p Can not format !!!!!!!!!!!!!", typeInfoPtr);
			return;
		}

		m_name = parseClsName(typeInfoPtr->name, false);
		m_size = typeInfoPtr->size;

		if (typeInfoPtr->superType && typeInfoPtr->superType[0]) {
			m_superTypeName = parseClsName(typeInfoPtr->superType, true);
			auto superTypeInfoPtr = TypeInfoManager::findClassInfo(typeInfoPtr->superType);
			if (!MemHelper::isBadReadPtr(superTypeInfoPtr)) {
				m_superTypeSize = superTypeInfoPtr->size;
			}
			else {
				logErr("failed bad ptr: %p for superType typeInfoPtr for clsName: %s", superTypeInfoPtr, m_name.c_str());
			}
		}

	}


	void debugPrint();
	void addClsNameToVec(std::string clsName);
	static void resetClsNamesVec();

	std::string removeSpaces(std::string input);

	size_t getAlreadyExistingNameIndex(std::string name);

	std::string getSuperType();	
	std::string getStructName();
	std::string getStructComment();
	int getSize();

	int getSuperTypeSize();

	std::string getErrorClsAsCharArray();

};

