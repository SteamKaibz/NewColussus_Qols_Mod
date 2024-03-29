#pragma once
#include "../Wolf2/TypeInfoManager.h"
#include <regex>
#include <string>
#include <unordered_map>


class varInfoCustom {

private:

    classVariableInfo_t* varInfoPtr;
    std::string declarationStr;
    std::string varNameStr;
    std::string usableTypeStr;
    std::string opsStr;
    std::string typeCommentStr;           


    void convertToUsableType() {
        if (!varInfoPtr) {
            logErr("convertToUsableType varInfoPtr is null can not process");
            return;
        }

        std::string varInfoTypeStr = varInfoPtr->type;
        logInfo("convertToUsableType: debug: varInfoTypeStr is %s", varInfoTypeStr.c_str());

        typeCommentStr = "// " + std::string(varInfoTypeStr) + std::string(varInfoPtr->ops);

        if (varInfoTypeStr.starts_with("idList")) {
            usableTypeStr = "idList";
        }
        else if (varInfoTypeStr.starts_with("idGrowableList")) {
            usableTypeStr = "void*";
            varNameStr = "idGrowableList_" + std::string(varInfoPtr->name);
        }
        else if (varInfoTypeStr.starts_with("idTypesafeTime")) {
            
            usableTypeStr = extractIdTimeSafeType(varInfoTypeStr);
        }
        else if (varInfoTypeStr.starts_with("idArray")) {
            std::regex pattern(R"(idArray\s*<\s*(.*?)\s*,\s*(\d+)\s*>)");
            std::smatch match;
            if (std::regex_search(varInfoTypeStr, match, pattern)) {
                if (match.size() == 3) {
                    std::string variableName = match[1].str();
                    std::string numberStr = match[2].str();
                    usableTypeStr = variableName;
                    varNameStr = std::string(varInfoPtr->name) + "_ptr" + "[" + numberStr + "]";
                }
            }
        }      
        else if (varInfoTypeStr == "idPlayerControllerBase") {
            usableTypeStr = "idPlayerController" + std::string(varInfoPtr->ops);
        }
        else {

            usableTypeStr = varInfoTypeStr;
            if (varInfoPtr->ops) {
                usableTypeStr += std::string(varInfoPtr->ops);
            }
            typeCommentStr.clear();
        }
        usableTypeStr = replaceDoubleScopeWithUnderscore(usableTypeStr);
    }

    void ConvertToVS64Type() {

        std::unordered_map<std::string, std::string> typeMap = {
            {"uint32", "unsigned int"},
            {"int32", "int"},
            {"uint16", "unsigned short"},
            {"int16", "short"},
            {"uint8", "unsigned char"},
            {"int8", "char"},
            {"uint64", "unsigned long long"},
            {"int64", "long long"}
        };

        std::string output = usableTypeStr;
        for (const auto& pair : typeMap) {
            size_t pos = output.find(pair.first);
            while (pos != std::string::npos) {
                output.replace(pos, pair.first.length(), pair.second);
                pos = output.find(pair.first, pos + pair.second.length());
            }
        }

        usableTypeStr = output;
    }


    std::string extractIdTimeSafeType(const std::string& input) {
        size_t openBracketPos = input.find('<');
        size_t commaPos = input.find(',');

        if (openBracketPos != std::string::npos && commaPos != std::string::npos) {
            std::string type = input.substr(openBracketPos + 1, commaPos - openBracketPos - 1);
            size_t firstNonSpace = type.find_first_not_of(" ");
            size_t lastNonSpace = type.find_last_not_of(" ");
            if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos) {
                type = type.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
            }
            return type;
        }

        return "TYPE NOT FOUND ";     
    }

    std::string replaceDoubleScopeWithUnderscore(std::string typeName) {
        std::regex doubleScope("::");
        return std::regex_replace(typeName, doubleScope, "_");
    }


    std::string getOffsetAndSizeComment() {
        if (!varInfoPtr) {
            logErr("getOffsetAndSizeComment varInfoPtr is null can not process");
            return std::string();
        }
        std::ostringstream result;
        result << "// offset: " << std::hex << std::uppercase << varInfoPtr->offset  << "h (" <<  std::dec << varInfoPtr->offset << "d)  size: " << varInfoPtr->size;
        return result.str();
    }



public:

    varInfoCustom(classVariableInfo_t* varInfoPtrArg)
    {
        varInfoPtr = varInfoPtrArg;
        if (!varInfoPtr) {
            logErr("varInfoCustom: varInfoPtr is null ptr can not process");
            return;
        }
        convertToUsableType();
        ConvertToVS64Type();           
    }

    std::string rearrangeBracketsInDeclaration(const std::string& input) {
        std::regex pattern(R"((\w+)\[(\d+)\]\s+(\w+))");       
        std::smatch matches;

        if (std::regex_match(input, matches, pattern)) {
            if (matches.size() == 4) {        
                return matches[1].str() + " " + matches[3].str() + "[" + matches[2].str() + "]";
            }
        }
        return input;       
    }

    std::string getStr() {
        if (!varInfoPtr) {
            logErr("varInfoCustom: can not get Str cause varInfoPtr is null");
            return std::string();
        }
        std::string result;
        std::string spacing = "    ";

        if (!typeCommentStr.empty()) {
            result += spacing + typeCommentStr + "\n";
        }
        if (varNameStr.empty()) {
            varNameStr = varInfoPtr->name;
        }

        std::string declarationStr = usableTypeStr.c_str();
        declarationStr += " ";
        declarationStr += varNameStr.c_str();
        declarationStr = rearrangeBracketsInDeclaration(declarationStr);


        logInfo("getStr: usableTypeStr: %s varNameStr: %s declarationStr: %s getOffsetAndSizeComment(): %s", usableTypeStr.c_str(), varNameStr.c_str(), declarationStr.c_str(), getOffsetAndSizeComment().c_str());
        result += spacing + declarationStr + " ; " + getOffsetAndSizeComment() + "\n";
        return result;
    }


};
