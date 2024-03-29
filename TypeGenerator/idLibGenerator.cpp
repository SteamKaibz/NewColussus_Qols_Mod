#include "idLibGenerator.h"
#include "classTypeInfo_K.h"





void idLibGenerator::generateIdLibFilesV2()
{
    int debugSafeCounter = 0;
    int counter = 0;
    int classCounter = 0;
    int enumCounter = 0;


    std::filesystem::path idaStringsFile = m_idaIdbStringsFileName;
    if (!std::filesystem::exists(idaStringsFile)) {
        logErr("generateIdLibFilesV2: m_idaIdbStringsFileName: %s not found, can not generate idLib returning", m_idaIdbStringsFileName.c_str());
        return;
    }

    auto idaAllStrsSet = K_Utils::loadFileToSet(m_idaIdbStringsFileName);

    std::vector<std::string> classTypesStrVec{};
    classTypesStrVec.reserve(131072);

    std::vector<std::string> enumTypesStrVec{};
    enumTypesStrVec.reserve(131072);

    for (const auto& idaStr : idaAllStrsSet)
    {
        auto clsInfoPtr = TypeInfoManager::findClassInfo(idaStr.c_str());
        if (clsInfoPtr) {
            auto clsStr = getClsInfoAsText(clsInfoPtr);
            if (!clsStr.empty()) {
                classTypesStrVec.push_back(clsStr);
                classCounter++;
            }
        }
        auto enumInfoPtr = TypeInfoManager::FindEnumInfo(idaStr.c_str());
        if (enumInfoPtr) {
            auto enumStr = getEnumInfoAsText(enumInfoPtr);
            if (!enumStr.empty()) {
                enumTypesStrVec.push_back(enumStr);
                enumCounter++;
            }
        }
    }
    std::string clsSummary = "\n" + std::to_string(classCounter) + " classes types were found.";
    classTypesStrVec.push_back(clsSummary);

    std::string enumsSummary = "\n" + std::to_string(enumCounter) + " enums types were found.";
    enumTypesStrVec.push_back(enumsSummary);

    K_Utils::saveVecToFile(m_idLibClassesFileName, classTypesStrVec);
    K_Utils::saveVecToFile(m_idLibEnumsFileName, enumTypesStrVec);

}


void idLibGenerator::generateIdaPro_C_Lib()
{
    int debugSafeCounter = 0;
    int counter = 0;
    int classCounter = 0;
    int enumCounter = 0;

    std::filesystem::path idaStringsFile = m_idaIdbStringsFileName;
    if (!std::filesystem::exists(idaStringsFile)) {
        logErr("generateIdaPro_C_Lib: m_idaIdbStringsFileName: %s not found, can not generate IdaPro_C_Lib returning", m_idaIdbStringsFileName.c_str());
        return;
    }

    auto idaAllStrsSet = K_Utils::loadFileToSet(m_idaIdbStringsFileName);

    std::vector<std::string> classTypesStrVec{};
    classTypesStrVec.reserve(131072);

    std::vector<std::string> enumTypesStrVec{};
    enumTypesStrVec.reserve(131072);

    for (const auto& idaStr : idaAllStrsSet)
    {
        auto clsInfoPtr = TypeInfoManager::findClassInfo(idaStr.c_str());
        if (clsInfoPtr) {
            auto clsStr = getClsInfoAsTextV3(clsInfoPtr);
            if (!clsStr.empty()) {
                classTypesStrVec.push_back(clsStr);
                classCounter++;
            }
        }
        auto enumInfoPtr = TypeInfoManager::FindEnumInfo(idaStr.c_str());
        if (enumInfoPtr) {
            auto enumStr = getEnumInfoAsText(enumInfoPtr);
            if (!enumStr.empty()) {
                enumTypesStrVec.push_back(enumStr);
                enumCounter++;
            }
        }
    }
    std::string clsSummary = "\n" + std::to_string(classCounter) + " classes types were found.";
    classTypesStrVec.push_back(clsSummary);

    std::string enumsSummary = "\n" + std::to_string(enumCounter) + " enums types were found.";
    enumTypesStrVec.push_back(enumsSummary);

    K_Utils::saveVecToFile(m_idaProLib_ClassesFileName, classTypesStrVec);
    K_Utils::saveVecToFile(m_idaProLib_EnumsFileName, enumTypesStrVec);
}

void idLibGenerator::generateIdaProc_C_Lib_Test(std::string className)
{
    auto clsInfoPtr = TypeInfoManager::findClassInfo(className.c_str());
    
    if (clsInfoPtr) {
        logInfo("generateIdaProc_C_Lib_Test: for cls: %s found clsInfoPtr: %p", className.c_str(), clsInfoPtr);
        auto clsStr = getClsInfoAsTextV3(clsInfoPtr);
        logInfo("generateIdaProc_C_Lib_Test:");
        logInfo("%s", clsStr.c_str());
    }
}

void idLibGenerator::debugPrint()
{
    logInfo("debugPrint:");
    logInfo("Ops:");
    for (const auto& opsStr : m_debugOpsSet) {
        logInfo("%s", opsStr.c_str());
    }
    logInfo("");
    logInfo("Types:");
    for (const auto& typeStr : m_debugTypesSet) {
        logInfo("%s", typeStr.c_str());
    }
}




std::string idLibGenerator::getClsInfoAsText(classTypeInfo_t* typeInfoPtr)
{
    std::string clsTxt;

    if (MemHelper::isBadReadPtr(typeInfoPtr)) {
        logErr("getClsInfoAsText: typeInfoPtr is bad ptr: %p ", typeInfoPtr);
        return clsTxt;
    }

    clsTxt += "\nstruct ";
    clsTxt += typeInfoPtr->name;
    if (typeInfoPtr->superType && typeInfoPtr->superType[0]) {
        clsTxt += " : public ";
        clsTxt += typeInfoPtr->superType;
    }
    clsTxt += " {\n";

    for (auto bleh2 = typeInfoPtr->variables; bleh2 && bleh2->name; ++bleh2) {
        clsTxt += "\t//";

        char buff[64];
        std::string offsetHex = K_Utils::intToHexString(bleh2->offset);
        sprintf_s(buff, "Offset %s,\t size %d\n", offsetHex.c_str(), bleh2->size);
        clsTxt += buff;
        if (bleh2->comment && bleh2->comment[0]) {
            clsTxt += "\t//";
            clsTxt += bleh2->comment;
            clsTxt += "\n";
        }
        clsTxt += "\t";
        clsTxt += bleh2->type;


        if (bleh2->ops) {
            clsTxt += bleh2->ops;
        }
        clsTxt += " ";
        clsTxt += bleh2->name;
        clsTxt += ";\n";
    }
    clsTxt += "};\n";
    return clsTxt;
}



std::string replaceDoubleScopeWithUnderscore(std::string input) {
    std::regex doubleScope("::");
    return std::regex_replace(input, doubleScope, "_");
}

std::string idLibGenerator::getClsInfoAsTextV3(classTypeInfo_t* typeInfoPtr)
{
        

    std::string clsTxt;
    int currentOffset = 0;
    int computedStructSize = 0;
    bool isBitFieldFlag = false;     
    int bitfieldCounter = 0;
    classTypeInfo_t* superTypeInfoPtr = 0;
    bool isFirstMember = true;

    if (MemHelper::isBadReadPtr(typeInfoPtr)) {
        logErr("getClsInfoAsText: typeInfoPtr is bad ptr: %p ", typeInfoPtr);
        return clsTxt;
    }
    else if (typeInfoPtr->size < 0) {
        logWarn("found typeInfoPtr->size < 0 with name: %s Not parsing it. However the class def will still be in Wolf2_IdLib_V2.h is you need to look at it.", typeInfoPtr->name);
        return clsTxt;
    }


    classTypeInfo_K typeInfo_K(typeInfoPtr);
    if (!typeInfo_K.getStructComment().empty()) {
        clsTxt += typeInfo_K.getStructComment();
        clsTxt += "\n";
    }


    clsTxt += "\nstruct ";
    std::string className = typeInfo_K.getStructName();
    clsTxt += className;

    if (!typeInfo_K.getSuperType().empty()) {
        clsTxt += " : public ";
        clsTxt += typeInfo_K.getSuperType();    
        currentOffset = typeInfo_K.getSuperTypeSize();
        computedStructSize = typeInfo_K.getSuperTypeSize();
    }    
    clsTxt += " {\n";
    


    for (auto member = typeInfoPtr->variables; member && member->name; ++member) {

        classVarInfo_K varInfo_K(member);

        if (member->size < 0) {
            clsTxt += "\t// bitfield member:  ";
            clsTxt += member->type;
            if (member->ops) {
                clsTxt += member->ops;
            }
            clsTxt += " ";
            clsTxt += member->name;
            clsTxt += ";\n";
            isBitFieldFlag = true;
            continue;
        }       

        int paddingSize = member->offset - currentOffset;
        if (paddingSize > 0) {
            clsTxt += "\t// offset: " + K_Utils::intToHexString(currentOffset) + " size: " + std::to_string(paddingSize) + "\n";
            if (isBitFieldFlag) {
                clsTxt += "\tchar bitField_";
            }
            else {
                clsTxt += "\tchar pad_";
            }
            clsTxt += K_Utils::intToHexString(currentOffset);
            clsTxt += "[" + std::to_string(paddingSize) + "];\n";
            computedStructSize += paddingSize;
            currentOffset += paddingSize;
        }


        clsTxt += "\t// offset: " + K_Utils::intToHexString(member->offset) + " current offset: " + K_Utils::intToHexString(currentOffset) + " size: " + std::to_string(member->size) + " " + varInfo_K.getCommentLine() + "\n";
      

        if (member->ops) {
            m_debugOpsSet.insert(member->ops);          
        }
        if (member->type) {
            m_debugTypesSet.insert(member->type);
        }

        std::string memberDecl = "\t";
        memberDecl += varInfo_K.getDeclLine();
        memberDecl += "\n";
        clsTxt += memberDecl;

       

        isBitFieldFlag = false;         
        currentOffset = member->offset + member->size;
        computedStructSize += member->size;

        if (computedStructSize == typeInfoPtr->size) {
            break;
        }   


    }    

    int sizeMismatchPadSize = typeInfoPtr->size - computedStructSize;
    if (sizeMismatchPadSize == 0) {
        clsTxt += "}; // struct size: " + std::to_string(typeInfoPtr->size) + " (" + K_Utils::intToHexString(typeInfoPtr->size) + ")";
        clsTxt += "\n";
    }    
    else if (sizeMismatchPadSize > 0) {
        clsTxt += "\tchar allignment_Pad";
        clsTxt += "[" + std::to_string(sizeMismatchPadSize) + "];\n";
        clsTxt += "}; // struct size: " + std::to_string(typeInfoPtr->size) + " (" + K_Utils::intToHexString(typeInfoPtr->size) + ")";
        clsTxt += "\n";
    }
    else {   
        logErr("getClsInfoAsTextV3: sizeMismatchPadSize: is %d something is wrong with this class generation: %s typeInfoPtr->size: %d computedStructSize: %d generating alternative cls...", sizeMismatchPadSize, typeInfoPtr->name, typeInfoPtr->size, computedStructSize);
        clsTxt = typeInfo_K.getErrorClsAsCharArray();
    }

    return clsTxt;
}


std::string idLibGenerator::getUniqueEnumVarName(std::string enumVarName) {
    for (size_t i = 0; i < m_uniqueEnumVarNamesVec.size(); i++)
    {
        if (enumVarName == m_uniqueEnumVarNamesVec[i]) {
            std::string uniqueName = enumVarName + "_dup_" + std::to_string(m_dupeEnumVarsCounter);
            m_dupeEnumVarsCounter++;
            return uniqueName;
        }
    }
    m_uniqueEnumVarNamesVec.push_back(enumVarName);
    return enumVarName;
}

std::string idLibGenerator::getEnumInfoAsText(enumTypeInfo_t* enumTypeInfoPtr)
{
    int enumVarsCounter = 0;                

    std::string enumAsStr;
    if (!enumTypeInfoPtr) {
        logErr("getEnumInfoAsText: enumTypeInfo is null can not get def");
        return enumAsStr;
    }
    enumAsStr += "enum ";

    enumAsStr += replaceDoubleScopeWithUnderscore(enumTypeInfoPtr->name);

    enumAsStr += " {\n";


    for (auto eval = enumTypeInfoPtr->values; eval && eval->name && eval->name[0]; eval++) {

        enumAsStr += getUniqueEnumVarName(eval->name);
        enumAsStr += " = ";
        enumAsStr += std::to_string(eval->value);
        enumAsStr += ",\n";
        enumVarsCounter++;
    }
    enumAsStr += "};\n";

    if (enumVarsCounter == 0) {
        return std::string();
    }
    return enumAsStr;
}










