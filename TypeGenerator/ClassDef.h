#pragma once

#include "../Wolf2/TypeInfoManager.h"



struct ClassDef {

    classTypeInfo_t* classInfoPtr = nullptr;
    std::vector<classVariableInfo_t*> varInfoVec;
    std::vector<std::string> inheritanceStrVec;
    std::string classNameStr;
    int currentOffset = 0;

       
    ClassDef(const char* classNameArg, const std::vector<const char*>& vars)
    {

        classNameStr = classNameArg;

        classInfoPtr = TypeInfoManager::findClassInfo(classNameStr.c_str());
        if (!classInfoPtr) {
            logErr("ClassDef: failed to find classInfo for classNameStr:  %s", classNameStr.c_str());
            return;
        }

        logInfo("ClassDef: classNameArg: %s and classNameStr: %s classInfoPtr classInfoPtr->name: %s", classNameArg, classNameStr.c_str(), classInfoPtr->name);

        for (size_t i = 0; i < vars.size(); i++)
        {
            auto member = TypeInfoManager::findClassField(classNameStr.c_str(), vars[i]);
            if (!member) {
                logErr("ClassDef: failed to find findClassField for classNameStr.c_str(): %s var: %s .Clearing varInfoVec so that this ClassDef doesn't get processed, you should check if there is a type in the var names", classNameStr.c_str(), vars[i]);
                varInfoVec.clear();
                return;
            }
            varInfoVec.push_back(TypeInfoManager::findClassField(classNameStr.c_str(), vars[i]));
        }

        acquirreInheritanceList();
        SortVarInfoVec();

    }

    std::string getFormatedClsName() {
        if (classInfoPtr) {
            return replaceDoubleScopeWithUnderscore(classInfoPtr->name);
        }
        return "*/! ERROR GETTING FORMATTED CLS NAME !/*";
    }

    static std::string replaceDoubleScopeWithUnderscore(std::string typeName) {
        std::regex doubleScope("::");
        return std::regex_replace(typeName, doubleScope, "_");
    }


    static bool CompareByOffset(const classVariableInfo_t* a, const classVariableInfo_t* b) {
        return a->offset < b->offset;
    }

    void SortVarInfoVec() {
        std::sort(varInfoVec.begin(), varInfoVec.end(), CompareByOffset);
    }

    void acquirreInheritanceList() {

        inheritanceStrVec.clear();

        if (!classInfoPtr) {
            logErr("acquirreInheritanceList: classInfoPtr is null for cls: %s returning", classNameStr.c_str());
            return;
        }

        classTypeInfo_t* tempClassInfo = TypeInfoManager::findClassInfo(classNameStr.c_str());

        std::string superType;

        while (true)
        {
            superType = tempClassInfo->superType;

            if (superType.empty()) {
                break;
            }
            inheritanceStrVec.push_back(superType);
            tempClassInfo = TypeInfoManager::findClassInfo(superType.c_str());
        }
    }

    std::string getInheritanceListStr() {

        if (inheritanceStrVec.size() <= 0) {
            return std::string();
        }

        std::string result;

        for (size_t i = 0; i < inheritanceStrVec.size(); i++) {
            result += inheritanceStrVec[i];

            if (i < inheritanceStrVec.size() - 1) {
                result += " : ";
            }
        }
        return result;
    }

    bool hasInheritance() {
        return (inheritanceStrVec.size() > 0);
    }

    classVariableInfo_t* getLastVarInfoEntry() {
        if (!varInfoVec.empty()) {
            return varInfoVec.back();           
        }
        return nullptr;
    }

    std::string getLastOffsetInHex(int offset) {
        if (offset < 0) {
            logErr("getLastOffsetInHex: offset is <0: %d", offset);
            return std::string();
        }
        std::stringstream ss;
        ss << std::hex <<  std::uppercase << offset << "h";
        return ss.str();
    }

    std::string getLastPaddingStr(int currentOffset) {
        classVariableInfo_t* lastVarInfo = getLastVarInfoEntry();

        if (lastVarInfo == nullptr) {
            logErr("getLastPaddingStr: lastVarInfo is nullPtr can not get last Padding right");
            return "ERROR LAST PADDING CAN NOT BE COMPUTED, CHECK THE LOG";
        }

        if (!classInfoPtr) {
            logErr("getLastPaddingStr: classInfoPtr is nullPtr can not get last Padding right");
            return "ERROR LAST PADDING CAN NOT BE COMPUTED, CHECK THE LOG";
        }

        int lastPaddingSize = classInfoPtr->size - currentOffset ;       

       

        if (lastPaddingSize < 0) {
            logErr("getLastPaddingStr: for class: %s lastPaddingSize is < 0, can not get last Padding right. classInfoPtr->size: %d currentOffset: %d lastVarInfo->size: %d lastVarInfo->name: %s", classInfoPtr->name, classInfoPtr->size, currentOffset, lastVarInfo->size, lastVarInfo->name);
            return "ERROR LAST PADDING CAN NOT BE COMPUTED, CHECK THE LOG";
        }
        else {
            logInfo("getLastPaddingStr: for class: %s lastPaddingSize == %d classInfoPtr->size: %d currentOffset: %d lastVarInfo->size: %d lastVarInfo->name: %s", classInfoPtr->name, lastPaddingSize, classInfoPtr->size, currentOffset, lastVarInfo->size, lastVarInfo->name);
        }


        if (lastPaddingSize == 0) { 
            return std::string();                   
        }

        std::string result;
        result += "char pad_End[";
        result += std::to_string(lastPaddingSize);
        result += "]; // offset: ";       
        result += getLastOffsetInHex(currentOffset);
        result += " (" + std::to_string(currentOffset);       
        result += "d) size: ";       
        result += std::to_string(lastPaddingSize);
        return result;
    }

   
};
