#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>     
#include <sstream>   
#include <cstdint>
#include <regex>
#include "ClassDef.h"
#include "ClassDefContainer.h"
#include "varInfoCustom.h"




class ClassDefFileGenerator {

private:

    std::string m_enumFileInclude = "#include \"GeneratedEnums.h\"\n"; 

    static std::string getPragmaOnce() {
        return "#pragma once\n";
    }


    static std::string getClassesFileIncludesStr() {
        std::string result;
        result += "#include \"idLib.h\"\n";
        result += "#include \"idColor.h\"\n";
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

    

    

      
    static std::string getClassDefStr(ClassDef classDef) {
        std::string fourSpaces = "    ";
        if (!classDef.classInfoPtr) {
            logErr("getClassDefStr: can not get class def cause classDef.classInfoPtr is null");
            return "\n!!! ERROR COULD NOT GENERATE CLASS DEF CAUSE OF classInfoPtr BEING NULL, CHECK THE LOG !!!\n";
        }
       
        if (classDef.varInfoVec.empty()) {
            logErr("getClassDefStr: varInfoVec is empty, can not get class def check the log there was a problem instanciating this ClassDef ");
            return "\n !!! ERROR COULD NOT GENERATE CLASS DEF CAUSE OF varInfoVec BEING EMPTY, CHECK THE LOG !!!\n";
        }

        logInfo("getClassDefStr classDef.classInfoPtr->name is %s and classDef.className: %s", classDef.classInfoPtr->name, classDef.classNameStr.c_str());

        std::ostringstream result;
        result << "\n";
        if (classDef.hasInheritance()) {
            result << "// " << classDef.classInfoPtr->name << " : " << classDef.getInheritanceListStr() << "\n";
        }        
        result << "class " << classDef.getFormatedClsName() << " {\npublic:\n";

        int currentOffset = 0;

        for (classVariableInfo_t* varInfo : classDef.varInfoVec) {
            if (!varInfo) {
                logErr("getClassDefStr: found null varInfo, something is wrong, not logging class");
                return "\n !!! ERROR COULD NOT GENERATE CLASS DEF CAUSE A varInfo IS NULL, CHECK THE LOG !!!\n";
            }         
           
            int paddingSize = varInfo->offset - currentOffset;

            if (paddingSize > 0) {
                result << fourSpaces  << "char pad_" <<  std::setfill('0') << std::dec << std::uppercase  << currentOffset << "["  << paddingSize << "]; // offset: " << std::hex << currentOffset  << "h" <<  " (" << std::dec << currentOffset << "d) size: " << paddingSize << "\n";
            }
           

            varInfoCustom customVarInfo(varInfo);
            result << customVarInfo.getStr();
            
            currentOffset = varInfo->offset + varInfo->size;
        }

        std::string lastPaddingStr = classDef.getLastPaddingStr(currentOffset);

        if (!lastPaddingStr.empty()) {
            result << fourSpaces << lastPaddingStr << "\n";
        }
        result << "}; // size: " << std::dec << classDef.classInfoPtr->size  << "\n\n";

        return result.str();
    }



public:    

    static void dumpClassDefs() {

        std::string result;

        result += getPragmaOnce();
        result += getClassesFileIncludesStr();
        result += getPragmaPackStartStr();
        result += "\n";
        result += "//? THOSES TYPES HAVE BEEN GENERATED AUTOMATICALLY BY TygeGenerator::dumpClassDefs CLS, IF THE GAMES IS UPDATED AT SOME POINT IN THE FUTURE? JUST LAUNCH this func (numpad 1 when mod loaded in debug mode) AND YOU WILL GET THOSES TYPES/CLASSES WITH CORRECTED OFFSETS DUMPED IN A FILE IN THE SAME FOLDER AS THE GAME";
        result += "\n\n";
        
        for (size_t i = 0; i < ClassDefContainer::getInstance().size(); i++)
        {
            result += getClassDefStr(ClassDefContainer::getInstance()[i]);
        }

        result += "\n\n";
        result += getPragmaPackEndStr();
        result += "\n";

        try
        {
            FILE* outtypes = nullptr;
            fopen_s(&outtypes, "NewColossusClasses_K.h", "w");
            if (outtypes) {
                logInfo("writing File NewColossusClasses_K.h....");
                fputs(result.c_str(), outtypes);
                fclose(outtypes);
            }
            else {
                logErr("outtypes is null for Classes(?!)");
            }
            
        }
        catch (const std::exception& ex)
        {
            logErr("dumpClassDefs: failed: %s", ex.what());
        }

    }
    

   

    
   
    
   

};


