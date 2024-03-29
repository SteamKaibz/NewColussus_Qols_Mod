#include "classTypeInfo_K.h"



std::vector<std::string> classTypeInfo_K::m_classNamesVec{};




std::string classTypeInfo_K::parseClsName(std::string input, bool isSuperCls) {
    size_t lessThanPos = input.find('<');

    size_t greaterThanPos = input.find('>', lessThanPos);

    if (lessThanPos != std::string::npos && greaterThanPos != std::string::npos) {
        if (!isSuperCls) {
            m_comment = "// orig name: " + input;       
        }
        std::string beforeAngleBrackets = input.substr(0, lessThanPos);

        std::string afterAngleBrackets = input.substr(greaterThanPos + 1);

        std::string modifiedString = beforeAngleBrackets + afterAngleBrackets;

        size_t doubleColonPos = modifiedString.find("::");
        while (doubleColonPos != std::string::npos) {
            modifiedString.replace(doubleColonPos, 2, "_");
            doubleColonPos = modifiedString.find("::");
        }

        modifiedString.erase(std::remove_if(modifiedString.begin(), modifiedString.end(), ::isspace), modifiedString.end());
        modifiedString.erase(std::remove(modifiedString.begin(), modifiedString.end(), ','), modifiedString.end());

        input = modifiedString;


    }
    std::regex doubleScope("::");
    input = std::regex_replace(input, doubleScope, "_");

    size_t existingNameIndex = getAlreadyExistingNameIndex(input);
    if (existingNameIndex != INT_MAX) {    
        input = input + "_dupe" + std::to_string(existingNameIndex);
    }
    else {
        addClsNameToVec(input);
    }

    input = removeSpaces(input);       
    return input;
}



void classTypeInfo_K::debugPrint()
{
	logInfo("classTypeInfo_K: debugPrint: m_name: %s m_superType: %s  m_size: %d", m_name.c_str(), m_superTypeName.c_str(), m_size);
}

void classTypeInfo_K::addClsNameToVec(std::string clsName)
{
    if (std::find(m_classNamesVec.begin(), m_classNamesVec.end(), clsName) == m_classNamesVec.end()) {
        m_classNamesVec.push_back(clsName);
    }

    
}

std::string classTypeInfo_K::getSuperType()
{
    return m_superTypeName;
}

void classTypeInfo_K::resetClsNamesVec()
{
    logWarn("!!!!!!!!!!!!! resetClsNamesVec called !!!!!!!!!!!!!!!!");
    logWarn("!!!!!!!!!!!!! resetClsNamesVec called !!!!!!!!!!!!!!!!");
    logWarn("!!!!!!!!!!!!! resetClsNamesVec called !!!!!!!!!!!!!!!!");
    m_classNamesVec.clear();
}

std::string classTypeInfo_K::getStructName()
{
    return m_name;
}

std::string classTypeInfo_K::getStructComment()
{
    return m_comment;
}

std::string classTypeInfo_K::removeSpaces(std::string input)
{
    std::string result;
    for (char c : input) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}

size_t classTypeInfo_K::getAlreadyExistingNameIndex(std::string name)
{
    for (size_t i = 0; i < m_classNamesVec.size(); i++)
    {
        if (name == m_classNamesVec[i])return i;
    }
    return (size_t)INT_MAX;
}

int classTypeInfo_K::getSuperTypeSize()
{
    logInfo("getSuperTypeSize : debug: returning: %d", m_superTypeSize);
    return m_superTypeSize;
}

std::string classTypeInfo_K::getErrorClsAsCharArray()
{
    std::string result = "";
    result += "\nstruct ";
    result += m_name;
    if (!m_superTypeName.empty()) {
        result += " : public ";
        result += m_superTypeName;
    }
    result += " {\n";
    result += "\tchar failArray[" + std::to_string(m_size) + "];\n";
    result += "}; // size: " + std::to_string(m_size) + "\n";
    return result;
}

int classTypeInfo_K::getSize()
{
    return m_size;
}
