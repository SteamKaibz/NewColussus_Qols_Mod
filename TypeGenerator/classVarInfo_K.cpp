#include "classVarInfo_K.h"



void classVarInfo_K::parse()
{
    formatTypeV2();
    parseOps();
    m_declLine = m_type + m_opsStruct.ptrStr + " " + m_name + m_opsStruct.arrayStr + ";";
}

void classVarInfo_K::parseOps()
{
    if (m_ops == "*") {
        m_opsStruct.ptrStr = "*";
    }  
    else if (m_ops == "**") {
        m_opsStruct.ptrStr = "**";
    }
    else if (m_ops.starts_with("[(") && m_ops.ends_with(")]")) {
        m_type = "char";
        m_opsStruct.arrayStr = "[" + std::to_string(m_size) + "]";
    }
    else if (m_ops.starts_with("[") && m_ops.ends_with("]")) {

        m_opsStruct.arrayStr = m_ops;  
        m_comment = "// orig ops: " + m_ops;
    }
    else if (m_ops.starts_with("*") && m_ops.ends_with("]")) {
        m_opsStruct.ptrStr = "*";
        m_opsStruct.arrayStr = m_ops.substr(1);   
        m_comment = "// orig ops: " + m_ops ;
    }
    else if (m_ops.starts_with("*") || (m_ops.starts_with("("))) {
        m_opsStruct.ptrStr = "*";
        m_comment = "// orig ops: " + m_ops;
    }
    else {
        m_opsStruct.defaultStr = m_ops;          
    }
}

std::string classVarInfo_K::getDeclLine()
{
    return m_declLine;
}

std::string classVarInfo_K::getCommentLine()
{
    return m_comment;
}

void classVarInfo_K::formatTypeV2() {

    size_t lessThanPos = m_type.find('<');

    size_t greaterThanPos = m_type.find('>', lessThanPos);

    if (lessThanPos != std::string::npos && greaterThanPos != std::string::npos) {
        std::string beforeAngleBrackets = m_type.substr(0, lessThanPos);

        std::string afterAngleBrackets = m_type.substr(greaterThanPos + 1);

        std::string modifiedString = beforeAngleBrackets + afterAngleBrackets;

        size_t doubleColonPos = modifiedString.find("::");
        while (doubleColonPos != std::string::npos) {
            modifiedString.replace(doubleColonPos, 2, "_");
            doubleColonPos = modifiedString.find("::");
        }

        modifiedString.erase(std::remove_if(modifiedString.begin(), modifiedString.end(), ::isspace), modifiedString.end());
        modifiedString.erase(std::remove(modifiedString.begin(), modifiedString.end(), ','), modifiedString.end());

        m_type = modifiedString;
    }
    std::regex doubleScope("::");
    m_type = std::regex_replace(m_type, doubleScope, "_");
}


void classVarInfo_K::formatTypeTo_C_Type() {


}







