#include "idEventManager.h"
#include "../MemHelper/MemHelper.h"
#include "../K_Utils/K_Utils.h"


std::string idEventManager::m_idEventDefFileName = "Wolf2_IdEventsDefsDump.txt";
std::vector<std::string> idEventManager::m_idEventDefStrVec;

std::string idEventManager::eventTypeToString(eventType_t eventType) {
    switch (eventType) {
    case EVENT_GAME:
        return "EVENT_GAME";
    case EVENT_ACTION:
        return "EVENT_ACTION";
    case EVENT_ANIMEVENT:
        return "EVENT_ANIMEVENT";
    case EVENT_FSMEVENT:
        return "EVENT_FSMEVENT";
    case EVENT_NOTICE:
        return "EVENT_NOTICE";
    default:
        return "Unknown";
    }
}



std::string idEventManager::getidEventDefToStr(idEventDef* idEventDefPtr) {
    std::string result = "";

    if (MemHelper::isBadReadPtr((void*)idEventDefPtr)) {
        logErr("printidEventDef: idEventDefPtr is a bad ptr: %p", (void*)idEventDefPtr);
        return result;
    }

    // Helper function to handle null or empty strings
    auto safeGetString = [](const char* str) -> std::string {
        if (str && *str) {
            return std::string(str);
        }
        return "null or empty";
        };

    result += "name: " + safeGetString(idEventDefPtr->name) + "\n";
    result += "formatspec: " + safeGetString(idEventDefPtr->formatspec) + "\n";
    result += "argTypes: " + safeGetString(idEventDefPtr->argTypes) + "\n";
    result += "argDefaultValues: " + safeGetString(idEventDefPtr->argDefaultValues) + "\n";
    result += "returnType: " + std::to_string(idEventDefPtr->returnType) + "\n";
    result += "numargs: " + std::to_string(idEventDefPtr->numargs) + "\n";
    result += "numstrings: " + std::to_string(idEventDefPtr->numstrings) + "\n";
    result += "eventnum: " + std::to_string(idEventDefPtr->eventnum) + " (" + K_Utils::intToHexString(idEventDefPtr->eventnum) + ")\n";
    result += "flags: " + std::to_string(idEventDefPtr->flags) + "\n";
    std::string typeStr = eventTypeToString(idEventDefPtr->type) + "\n";
    result += "typeStr: " + typeStr;
    result += "comment: " + safeGetString(idEventDefPtr->comment) + "\n";
    result += "\n";

    return result;
}

//? 16/9/24 we could have done so much better as we have the funcs in idEventDefInterfaceLocal (26CC240) I guess that will do for now though....
void idEventManager::listAllEventsToFile() {

    m_idEventDefStrVec.clear();

    int v2 = 0;
    //? no sig for addr but instead where it's called: result: matches @ 0xAA2D5F, sig direct: 4C 8D 1D ? ? ? ? 66 66 0F 1F 84 00 ? ? ? ? 49 8B 1B
    __int64 maxEventNumAdd = MemHelper::getAddr(0x4297098);
    if (MemHelper::isBadReadPtr((void*)maxEventNumAdd)) {
        logErr("listAllEventsToFile: maxEventNumAdd is bad ptr: %p", (void*)maxEventNumAdd);
        return;
    }
    int maxEventNum = *(int*)maxEventNumAdd;
    logInfo("listAllEventsToFile : maxEventNum: %d", maxEventNum);

    if (maxEventNum > 0) {
        //! result: matches @ 0x42974A0, sig direct: D0 F3 44 3C F7 7F 00
        __int64* idEventDefListPtr = (__int64*)MemHelper::getAddr(0x42974A0);
        if (MemHelper::isBadReadPtr((void*)idEventDefListPtr)) {
            logErr("listAllEventsToFile: idEventDefListPtr is bad ptr: %p", (void*)idEventDefListPtr);
            return;
        }
        logInfo("listAllEventsToFile : idEventDefListPtr: %p", (void*)idEventDefListPtr);

        std::string fileTitleStr = "idEvent Definitions: events max count: " + std::to_string(maxEventNum);
        m_idEventDefStrVec.push_back(fileTitleStr);
        m_idEventDefStrVec.push_back("\n");
        
        do {
            //logInfo("listAllEventsToFile : counter: %d", v2);
            idEventDef* eventDefPtr = (idEventDef*) *idEventDefListPtr;
            if (MemHelper::isBadReadPtr(eventDefPtr)) {
                logErr("listAllEventsToFile: eventDefPtr is bad ptr: %p", eventDefPtr);
                return;
            }
            m_idEventDefStrVec.push_back(getidEventDefToStr(eventDefPtr));
            //m_idEventDefVec.push_back(eventDefPtr);
            //printidEventDef(eventDefPtr);           
            ++v2;
            ++idEventDefListPtr;
        } while (v2 < maxEventNum);
    }

    K_Utils::saveVecToFile(m_idEventDefFileName, m_idEventDefStrVec);
   
}


std::vector<idEventDef*> idEventManager::getEventsVec() {

    std::vector<idEventDef*> resultVec;

    int v2 = 0;
    
    __int64 maxEventNumAdd = MemHelper::getAddr(0x4297098);
    if (MemHelper::isBadReadPtr((void*)maxEventNumAdd)) {
        logErr("getEventsVec: maxEventNumAdd is bad ptr: %p", (void*)maxEventNumAdd);
        return resultVec;
    }
    int maxEventNum = *(int*)maxEventNumAdd;
    logInfo("getEventsVec : maxEventNum: %d", maxEventNum);

    if (maxEventNum > 0) {
        //! result: matches @ 0x42974A0, sig direct: D0 F3 44 3C F7 7F 00
        __int64* idEventDefListPtr = (__int64*)MemHelper::getAddr(0x42974A0);
        if (MemHelper::isBadReadPtr((void*)idEventDefListPtr)) {
            logErr("getEventsVec: idEventDefListPtr is bad ptr: %p", (void*)idEventDefListPtr);
            return resultVec;
        }
        logInfo("getEventsVec : idEventDefListPtr: %p", (void*)idEventDefListPtr);


        do {
            idEventDef* eventDefPtr = (idEventDef*)*idEventDefListPtr;
            if (MemHelper::isBadReadPtr(eventDefPtr)) {
                logErr("getEventsVec: eventDefPtr is bad ptr: %p", eventDefPtr);
                return resultVec;
            }
            resultVec.push_back(eventDefPtr);
                   
            ++v2;
            ++idEventDefListPtr;
        } while (v2 < maxEventNum);
    }

    logInfo("getEventsVec: dbg: returning %zu events", resultVec.size());
    return resultVec;

}


void idEventManager::generateEventNumsEnumFile() {

    unsigned int eventsPtrCounter = 0;
    unsigned int eventsStrCounter = 0;

    std::vector<std::string> numEventK_tDefStrVec;
    std::string enumHeaderStr = "enum eventNumK_t {";
    numEventK_tDefStrVec.push_back(enumHeaderStr);


    std::vector<idEventDef*> eventDefsPtrs = getEventsVec();
    for (size_t i = 0; i < eventDefsPtrs.size(); i++)
    {
        numEventK_tDefStrVec.push_back(getEventNumAsEnumMember(i, eventDefsPtrs[i]));
        eventsStrCounter++;
    }

    std::string enumLastLineStr = "};";
    numEventK_tDefStrVec.push_back(enumLastLineStr);


    /* logInfo("generateEventNumsEnumFile: found : %u events Str, saving to file: %s", eventsPtrCounter, Config::.c_str());*/
    K_Utils::saveVecToFile("Wolf2_EventsAsEnum.h", numEventK_tDefStrVec);

}

//! special case where switch statement is done a a transformed value of event num.
void idEventManager::generateEventNumsEnumFileFor_0xcb58c0() {

    unsigned int eventsPtrCounter = 0;
    unsigned int eventsStrCounter = 0;

    const bool b_SpecialCasefor0xcb58c0 = true;

    std::vector<std::string> numEventK_tDefStrVec;
    std::string enumHeaderStr = "enum eventNumK_0xcb58c0_t {";
    numEventK_tDefStrVec.push_back(enumHeaderStr);


    std::vector<idEventDef*> eventDefsPtrs = getEventsVec();
    for (size_t i = 0; i < eventDefsPtrs.size(); i++)
    {
        numEventK_tDefStrVec.push_back(getEventNumAsEnumMember(i, eventDefsPtrs[i], b_SpecialCasefor0xcb58c0));
        eventsStrCounter++;
    }

    std::string enumLastLineStr = "};";
    numEventK_tDefStrVec.push_back(enumLastLineStr);


    /* logInfo("generateEventNumsEnumFile: found : %u events Str, saving to file: %s", eventsPtrCounter, Config::.c_str());*/
    K_Utils::saveVecToFile("Wolf2_EventsAsEnumSpecial.h", numEventK_tDefStrVec);

}


std::string idEventManager::getEventNumAsEnumMember(size_t index, idEventDef* eventDefPtr, bool is_0xcb58c0_SpecialCase) {

    static bool isFirstTime = true;
    std::string result;

    if (MemHelper::isBadReadPtr(eventDefPtr)) {
        logErr("getEventNumAsEnumMember: found bad ptr: %p", eventDefPtr);
        return "!!!ERROR!!!";
    }

    std::string eventNameStr = eventDefPtr->name;
    if (eventNameStr.empty()) {
        eventNameStr = "!!!!! ERROR EVENT !!!!!";
    }
    else if(eventNameStr == "break") {
        eventNameStr = "renamedK_break";
    }
    else if (is_0xcb58c0_SpecialCase && isFirstTime) {
        eventNameStr = eventDefPtr->name;
        eventNameStr+= " = - 0xD1";
        isFirstTime = false;
    } 

    result += "\t";
    result += eventNameStr;   
    result += " , // index: ";
    result += K_Utils::intToHexString(index);
    result += " eventnum: ";
    result += K_Utils::intToHexString(eventDefPtr->eventnum);

    return result;
}