#include "BuildInfo.h"



std::string BuildInfo::getBuildStr()
{

    //? no sig but func that has this var is at result: matches @ 0xA5B800, sig direct: 88 54 24 10 48 89 4C 24 ? 57
    auto buildAddr = MemHelper::getAddr(0x3C78F38);
    if (MemHelper::isBadReadPtr((void*)buildAddr)) {
        return "failed To Find Build Addr";
    }
    std::string buildStr = *(const char**)buildAddr;
    return buildStr;
}


std::string BuildInfo::getImGuiBuildStr() {
    return "Game Build Version: " + BuildInfo::getBuildStr();
}