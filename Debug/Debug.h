#pragma once

#include "../Wolf2/idGameLocalManager.h"


enum hudFlags_t {
    HUDFLAG_NONE = 0x0,
    HUDFLAG_FADEOUTHUD = 0x1,
    HUDFLAG_FADEINHUD = 0x2,
    HUDFLAG_FADEDOUT = 0x4,
    HUDFLAG_FADEDIN = 0x8,
    HUDFLAG_FADERESET = 0x10,
    HUDFLAG_FADEACC = 0x20,
    HUDFLAG_DELAYED = 0x40,
    HUDFLAG_HIDECROSSHAIR = 0x80,
    HUDFLAG_HIDEUSEBUTTON = 0x100,
    HUDFLAG_HIDEHEALTHARMOR = 0x200,
    HUDFLAG_HIDEWPNWHEEL = 0x400,
    HUDFLAG_HIDEWEAPONAMMO = 0x800,
    HUDFLAG_HIDEGRENADEAMMO = 0x1000,
    HUDFLAG_HIDETHROWWPNAMMO = 0x2000,
    HUDFLAG_HIDECOMBATHUD = 0x4000,
    HUDFLAG_HIDECOMBATHUD_PH = 0x8000,
    HUDFLAG_SHOWINFONOT = 0x10000,
    HUDFLAG_NOTAPPLIED = 0x20000,
    HUDFLAG_INTERACT_TUTORIAL = 0x40000,
    HUDFLAG_TIMER = 0x80000,
    HUDFLAG_SHOWCHALLENGEHUD = 0x100000,
    HUDFLAG_SHOWSCORE = 0x200000,
    HUDFLAG_SHOWHINTFADEIN = 0x400000,
    HUDFLAG_SHOWHINTFADEOUT = 0x800000,
    HUDFLAG_SWEEPMARKER = 0x1000000,
    HUDFLAG_FLAGSPROCESSED = 0x2000000,
    HUDFLAG_SHOWADDHEALTHBAR = 0x4000000,
    HUDFLAG_HIDESUBTITLES = 0x8000000,
    HUDFLAG_HIDERESTOFHUD = 0x10000000,
    HUDFLAG_FREEZE_OPTIONS = 0x20000000,
    HUDFLAG_FREEZE_OPTIONS_RESET = 0x40000000,
};





class Debug
{
private:

    static std::vector<__int64> m_idRenderModelGuiPtrsVec;

public:

    static std::string getHUDFlagsString(int hudFlags);

    static void printPlayerInfoOnKeyPress();

    static std::string getCurrentMovementModeStr();

    static void AddidRenderModelGuiPtrInStretchPicFuncToVec(__int64 idRenderModelGuiPtr);

    static void printidRenderModelGuiPtrs();

    static int gethudStateFlagsInt();

    static void printLivePlayerInfo();

    static int getlongTextTest();

};

