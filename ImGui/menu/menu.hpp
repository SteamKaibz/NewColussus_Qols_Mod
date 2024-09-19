#pragma once

#include <Windows.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include "../../ModSettings/ModSettings.h"
#include "../../FileOp/FileOp.h"

#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_impl_win32.h"
#include "../../Config/Config.h"
#include "../dependencies/imgui/Imgui_Wolf2Test.cpp"
#include "../../Debug/ImGuiDebugWin.h"
#include "../../Wolf2/autoItemPickUpManager.h"
#include "../../Wolf2/idUsercmdGenLocalManager.h"
#include "../../Wolf2/hudManager.h"
#include "../../Wolf2/idFocusTrackerManager.h"
#include "../../Wolf2/BuildInfo.h"
#include "../Fonts/font_awesome.cpp"
#include "../Fonts/font_awesome.h"

#include "fastForwardGui.h"
#include "WarningGui.h"
#include "../../Wolf2/timescaleManager.h"
#include "../../Wolf2/idEngineLocalManager.h"
#include "DebugGui.h"
#include "hudExtrasGui.h"
#include "../../Wolf2/idLightManager.h"
#include "../../Debug/Debug.h"
#include "liveStatsGui.h"









namespace Menu {
    void InitializeContext(HWND hwnd);
    void Render( );

    bool isVkCodeValid(unsigned int vkCode);
    bool isDuplicateKeyError();

    inline bool bShowMenu = false;
    inline bool bShowDebugWindow = false;
    inline bool bShowWarningWindow = true;
    inline bool bShowFastForwardIcon = true;

    inline bool bTEMPisShowStats = false;

    inline ImFont* icons_font_awesome = nullptr;

    inline auto orangeColor = ImVec4(1.0f, 0.65f, 0.0f, 1.0f);
    inline auto yellowColor = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
    inline auto redColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    inline auto grayColor = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);
    inline auto whiteColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    inline auto invisibleColor = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);


    inline const char* hudChoiceItemsV2[] = {
    "Biggest Hud",
    "Bigger Hud",
    "Game Default Hud",
    "Smaller Hud",
    "Mini Hud",    
    "Custom Size HUD (Use Sliders Below)"
    };

    







    inline ModSettings modSettings;
    static inline std::string lastModSettingsJsonFileStr;
    void LoadFromFile();
    std::string getJsonFileAsStr();
    void logChangedJsonFile();
    void SaveToFile();


    void LoadSettings(ModSettings modSettingsFromFile);
    ModSettings getSettings();

    inline int lastKeyPressed = -1;

    void showModMenu(bool* p_open = NULL);



}   
