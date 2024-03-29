#pragma once
#include <string>
#include <vector>
#include "../Wolf2/TypeInfoManager.h"
#include <regex>


class EnumsDefFileGenerator {
private:

    std::string m_enumFileInclude = "#include \"GeneratedEnums.h\"\n";

    static std::string getPragmaOnce() {
        return "#pragma once\n";
    }

    static std::string getEnumFileIncludesStr() {
        return "#include <cstdint>\n";
    }

    static std::string getClassesFileIncludesStr() {
        std::string result;
        result += "#include \"idLib.h\"\n";
        result += "#include \"GeneratedEnums.h\"\n";
        result += "\n\n";
        return result;
    }

    static std::string getPragmaPackStartStr() {
        return "#pragma pack(push, 1) // making sure no padding is added by compiler\n\n";
    }

    static std::string getPragmaPackEndStr() {
        return "#pragma pack(pop) // Restore default packing alignment\n";
    }

    static std::string getEnumTypeAsStr(int enumType) {
        switch (enumType) {
        case 0:
            return "int8_t";    
        case 1:
            return "uint8_t";   
        case 2:
            return "int16_t";   
        case 3:
            return "uint16_t";   
        case 4:
            return "int32_t";   
        case 5:
            return "uint32_t";   
        case 6:
            return "int64_t";   
        case 7:
            return "uint64_t";   
        default:
            return "ERROR COULD NOT FIND ENUM TYPE ENUM IS NOT VALID";   
        }
    }

    static std::string getEnumDefStr(enumTypeInfo_t* enumTypeInfo) {
        int counter = 1;

        std::string result;
        if (!enumTypeInfo) {
            logErr("getEnumDefStr: enumTypeInfo is null can not get def");
            return result;
        }
        result += "enum ";
        result += replaceDoubleScopeWithUnderscore(enumTypeInfo->name);       
        result += " {\n";


        for (auto eval = enumTypeInfo->values; eval && eval->name && eval->name[0]; eval++) {

            result += eval->name;
            result += " = ";
            result += std::to_string(eval->value);
            result += ",\n";

        }
        result += "};\n";

        return result;
    }


    static std::string replaceDoubleScopeWithUnderscore(std::string typeName) {
        std::regex doubleScope("::");
        return std::regex_replace(typeName, doubleScope, "_");
    }
   

public:

    static void DumpEnumDefs() {

        std::string result;
        result += getPragmaOnce();
        result += "\n";
        result += getEnumFileIncludesStr();
        result += "\n\n";

        std::vector<enumTypeInfo_t*> enumTypesInfoVec;

        enumTypesInfoVec.push_back(TypeInfoManager::FindEnumInfo("playerType_t"));
        enumTypesInfoVec.push_back(TypeInfoManager::FindEnumInfo("idPlayer::playerUseState_t"));
        enumTypesInfoVec.push_back(TypeInfoManager::FindEnumInfo("gameState_t"));
        enumTypesInfoVec.push_back(TypeInfoManager::FindEnumInfo("movementMode_t"));
        enumTypesInfoVec.push_back(TypeInfoManager::FindEnumInfo("idPlayer::animSysNodeFlags_t"));
        enumTypesInfoVec.push_back(TypeInfoManager::FindEnumInfo("shellScreen_t"));
        enumTypesInfoVec.push_back(TypeInfoManager::FindEnumInfo("idPlayerHud::hudState_t"));


        for (size_t i = 0; i < enumTypesInfoVec.size(); i++)
        {
            result += getEnumDefStr(enumTypesInfoVec[i]);
            result += "\n\n";
        }

        try
        {
            FILE* outtypes = nullptr;
            fopen_s(&outtypes, "NewColossus_Enums_K.h", "w");
            if (outtypes) {
                logInfo("writing File NewColossus_Enums_K.h....");
                fputs(result.c_str(), outtypes);
                fclose(outtypes);
            }
            else {
                logErr("outtypes is null for Enums (?!)");
            }

        }
        catch (const std::exception& ex)
        {
            logErr("DumpEnumDefs: failed: %s", ex.what());
        }





    }
};

