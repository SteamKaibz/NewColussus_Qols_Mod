#pragma once

#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>     
#include <sstream>   
#include <cstdint>
#include <regex>
#include "../MemHelper/MemHelper.h"
#include "../Config/Config.h"
#include "../Wolf2/TypeInfoManager.h"
#include "../K_Utils/K_Utils.h"



class ClassDefV2
{
private:
    classTypeInfo_t* m_classInfoPtr = nullptr;
    std::vector<classVariableInfo_t*> m_varInfoVec;
    std::vector<std::string> m_inheritanceStrVec;
    std::string m_classNameStr;
    int m_currentOffset = 0;

public:

    ClassDefV2(const char* classNameArg) {
        auto clsInfoPtr = TypeInfoManager::findClassInfo(classNameArg);
        if (!clsInfoPtr) {
            logErr("ClassDefV2: could not find clsInfoPtr for input: %s", classNameArg);
            return;
        }
        m_classNameStr = classNameArg;


    }


    std::string getInheritanceListStr();
    
    bool hasInheritance();

   

};

