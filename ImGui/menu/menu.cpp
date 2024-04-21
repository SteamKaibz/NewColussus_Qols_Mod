#include "menu.hpp"

#include "../Fonts/Robotto.h"




namespace ig = ImGui;

namespace Menu {  


    void InitializeContext(HWND hwnd) {
        if (ig::GetCurrentContext( ))
            return;

        ImGui::CreateContext( );       


        ImGui_ImplWin32_Init(hwnd);

        ImGuiIO& io = ImGui::GetIO( );
        io.IniFilename = io.LogFilename = nullptr;



        ImFontConfig font_cfg;
        font_cfg.FontDataOwnedByAtlas = false;
        io.Fonts->AddFontFromMemoryTTF(robottoData, sizeof(robottoData), 22.0f, &font_cfg); 


       static const ImWchar icon_ranges[] = { 0xf000, 0xf3ff, 0 };
       ImFontConfig config;
       config.MergeMode = true;
       config.PixelSnapH = true;
       config.OversampleH = true;
       config.OversampleV = true;
       config.FontDataOwnedByAtlas = false;          
      
       icons_font_awesome = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 40.0f, &config, icon_ranges);        




          
    











      




        

       



    }

    void Render( ) { 

                    

        if (bShowDebugWindow) {  
            DebugGui::showDebugWindow();
        }

       
        if (bShowMenu) {

            showModMenu();
            return;             
        }
        
        if (idEngineLocalManager::isGameActive() && timescaleManager::isFastForwardTimeScale()) {
            fastForwardGui::showFastForwardIcon();
        }

        if (ModSettingsManager::isShowFlashLightIcon() && idEngineLocalManager::isGameActive() && idLightManager::isHeadLightOn()) {
            hudExtrasGui::showHudExtrasWindow();
        }
              

        if (bShowWarningWindow) {
            WarningGui::showWarningWindow();
        }
       
    }






    bool isVkCodeValid(unsigned int vkCode) {
        return (vkCode >= VK_LBUTTON && vkCode <= VK_OEM_CLEAR);
    }


    bool isDuplicateKeyError() {
        auto isError = (modSettings.normalSpeedKeyVkCode == modSettings.fastForwardKeyVkCode ||
            modSettings.normalSpeedKeyVkCode == modSettings.flashLightKeyVkCode ||
            modSettings.fastForwardKeyVkCode == modSettings.flashLightKeyVkCode ||
            modSettings.normalSpeedKeyVkCode == modSettings.fastForwardKeyVkCode);
        return isError;
    }

    void LoadSettings(ModSettings modSettingsFromFile)
    {
        modSettings = modSettingsFromFile;
    }

    ModSettings getSettings()
    {
        return modSettings;
    }


    void logChangedJsonFile() {
        std::string jsonFileStr = getJsonFileAsStr();

        if (lastModSettingsJsonFileStr.empty()) {
            lastModSettingsJsonFileStr = jsonFileStr;
            if (jsonFileStr.empty()) {
                logWarn("jsonFileStr is empty, this should not happen...nothing to log.");
            }
            else {
                logInfo("logging modSettings file for the first time: ");
                logInfo("%s", jsonFileStr.c_str());
            }           
        }
        else if(lastModSettingsJsonFileStr != jsonFileStr){
            lastModSettingsJsonFileStr = jsonFileStr;
            if (jsonFileStr.empty()) {
                logWarn("jsonFileStr is empty, this should not happen...nothing to log. (lastModSettingsJsonFileStr is not empty)");
            }
            else {
                logInfo("modSettings file has changed to: ");
                logInfo("%s", jsonFileStr.c_str());
            }
        }   
        else {
            logInfo("modSettings file was not modified by user. not logging it.");
        }
    }

    
    std::string getJsonFileAsStr() {
        std::string filePath = FileOp::getModSettingsFilePath();
        logInfo("LoadFromFile: loading file: %s", filePath.c_str());

        if (!std::filesystem::exists(filePath)) {
            logWarn("LogJsonFile: can not log, filpath: %s does not exist", filePath.c_str());
            return std::string();
        }

        std::ifstream file(filePath);
        nlohmann::json j;
        if (file.is_open()) {
            file >> j;
        }
        return j.dump();
    }


    void LoadFromFile() {
        std::string filePath = FileOp::getModSettingsFilePath();
        logInfo("LoadFromFile: loading file: %s", filePath.c_str());

        if (!std::filesystem::exists(filePath)) {
            logWarn("LoadFromFile: creating default settings file: %s", filePath.c_str());
            SaveToFile();
            return;
        }

        try {
            std::ifstream file(filePath);
            nlohmann::json j;
            if (file.is_open()) {
                file >> j;

                modSettings.fastForwardKeyVkCode = j.value("fastForwardKeyVkCode", VK_F1);
                modSettings.normalSpeedKeyVkCode = j.value("normalSpeedKeyVkCode", VK_F2);
                modSettings.isAutoPickUpHealth = j.value("isAutoPickUpHealth", false);
                modSettings.isAutoPickUpArmor = j.value("isAutoPickUpArmor", false);
                modSettings.isAutoPickUpAmmo = j.value("isAutoPickUpAmmo", false);
                modSettings.isAutoPickUpHatchet = j.value("isAutoPickUpHatchet", false);
                modSettings.isAutoPickEnigma = j.value("isAutoPickEnigma", false);

                modSettings.isDisableItemHighlighthing = j.value("isDisableItemHighlighthing", false);
                modSettings.isSetAutoMapDefaultZoomToMin = j.value("isSetAutoMapDefaultZoomToMin", false);
            
                modSettings.isAdsToggle = j.value("isAdsToggle", false);
                modSettings.zoomKeyVkCode = j.value("zoomKeyVkCode", VK_RBUTTON);  

                modSettings.isUseCustomHud = j.value("isUseCustomHud", false);
                modSettings.hudConfiguration = j.value("hudConfiguration", (int)HUDConfigV2::BiggerHud);
                modSettings.hudScale = j.value("hudScale", 1.0f);
                modSettings.hudFrameHeightMul = j.value("hudFrameHeightMul", 1.0f);
                modSettings.hudSafeFrameOffset = j.value("hudSafeFrameOffset", modSettingsConst::safeFrameDefaultVal);
                modSettings.showAlarmIcons = j.value("showAlarmIcons", true);
                modSettings.showMaxedOutText = j.value("showMaxedOutText", true);

                modSettings.isEnableHudWarning = j.value("isEnableHudWarning", true);
                modSettings.hudBlinkWarningSpeedMs = j.value("hudBlinkWarningSpeedMs", 500);

                modSettings.hudHealthRedTriggerPrct = j.value("hudHealthRedTriggerPrct", modSettingsConst::hudHealthRedTriggerPrctDef);
                modSettings.hudArmorRedTriggerPrct = j.value("hudArmorRedTriggerPrct", modSettingsConst::hudArmorRedTriggerPrctDef);

                modSettings.hudHealthOrangeTriggerPrct = j.value("hudHealthOrangeTriggerPrct", modSettingsConst::hudHealthOrangeTriggerPrctDef);
                modSettings.hudArmorOrangeTriggerPrct = j.value("hudArmorOrangeTriggerPrct", modSettingsConst::hudArmorOrangeTriggerPrctDef);

                modSettings.isCustomCrosshair = j.value("isCustomCrosshair", false);
                modSettings.customCrosshairSize = j.value("customCrosshairSize", 3);
                modSettings.customCrosshairOutlineThickness = j.value("customCrosshairOutlineThickness", 1);

                auto crosshairColor = j.value("customCrosshairColor", modSettingsConst::gameHudColorVec);
                modSettings.customCrosshairColor = ImVec4(crosshairColor[0], crosshairColor[1], crosshairColor[2], crosshairColor[3]);
                auto targetColor = j.value("customCrosshairTargetColor", modSettingsConst::gameHudColorVec);
                modSettings.customCrosshairTargetColor = ImVec4(targetColor[0], targetColor[1], targetColor[2], targetColor[3]);

                auto outlineColor = j.value("customCrosshairOutlineColor", modSettingsConst::redHudColorVec);
                modSettings.customCrosshairOutlineColor = ImVec4(outlineColor[0], outlineColor[1], outlineColor[2], outlineColor[3]);

                modSettings.isSkipFog = j.value("isSkipFog", false);
                modSettings.isHdrDisabled = j.value("isHdrDisabled", false);
                modSettings.isDisabledSimulationFilter = j.value("isDisabledSimulationFilter", false);
                modSettings.colorSaturation = j.value("colorSaturation", 1.0f);


                modSettings.isShowHudScoreDamageNumbers = j.value("isShowHudScoreDamageNumbers", true);
                modSettings.isShowHudScoreTotalNumber = j.value("isShowHudScoreTotalNumber", true);

                modSettings.isshowObjectiveMarkers = j.value("isshowObjectiveMarkers", true);
                modSettings.isFreeLeanOnly = j.value("isFreeLeanOnly", false);
                modSettings.headBobAmount = j.value("headBobAmount", 0.1f);
                modSettings.viewKickMax = j.value("viewKickMax", 0.5f);
                modSettings.isEnableGaussianBlur = j.value("isEnableGaussianBlur", false);


                modSettings.flashLightKeyVkCode = j.value("flashLightKeyVkCode", VK_F3);
                auto headLightColor = j.value("headlightColor", modSettingsConst::headlightDefaultColorVec);
                modSettings.headlightColor = ImVec4(headLightColor[0], headLightColor[1], headLightColor[2], headLightColor[3]);
                modSettings.isHeadLightAdvancedSettingsEnabled = j.value("isHeadLightAdvancedSettingsEnabled", false);

                modSettings.headlightIntensity = j.value("headlightIntensity", modSettingsConst::headlightIntensityDef);
                modSettings.headlightTarget_X = j.value("headlightTarget_X", modSettingsConst::headlightTargetXDef);
                modSettings.headlightLightEnd_X = j.value("headlightLightEnd_X", modSettingsConst::headlightEndXDef);
                modSettings.isShowFlashLightIcon = j.value("isShowFlashLightIcon", true);

               

                modSettings.handgunAdsFov = j.value("handgunAdsFov", 85.0f);
                modSettings.handgunAdsFovSensMultiplier = j.value("handgunAdsFovSensMultiplier", 0.5f);

                modSettings.smgAdsFov = j.value("smgAdsFov", 80.0f);
                modSettings.smgAdsFovSensMultiplier = j.value("smgAdsFovSensMultiplier", 0.5f);

                modSettings.battlerifleAdsFov = j.value("battlerifleAdsFov", 65.0f);
                modSettings.battlerifleAdsFovSensMultiplier = j.value("battlerifleAdsFovSensMultiplier", 0.5f);

                modSettings.battlerifleScopeFov = j.value("battlerifleScopeFov", 40.0f);
                modSettings.battlerifleScopeFovSensMultiplier = j.value("battlerifleScopeFovSensMultiplier", 0.35f);

                modSettings.shotgunAdsFov = j.value("shotgunAdsFov", 75.0f);
                modSettings.shotgunAdsFovSensMultiplier = j.value("shotgunAdsFovSensMultiplier", 0.5f);

                modSettings.lkwAdsFov = j.value("lkwAdsFov", 65.0f);
                modSettings.lkwAdsFovSensMultiplier = j.value("lkwAdsFovSensMultiplier", 0.5f);

                modSettings.lkwscopeFov = j.value("lkwscopeFov", 40.0f);
                modSettings.lkwscopeFovSensMultiplier = j.value("lkwscopeFovSensMultiplier", 0.35f);

                modSettings.kampfpistolAdsFov = j.value("kampfpistolAdsFov", 85.0f);
                modSettings.kampfpistolAdsFovSensMultiplier = j.value("kampfpistolAdsFovSensMultiplier", 0.5f);

                modSettings.heavyweaponAdsFov = j.value("heavyweaponAdsFov", 65.0f);
                modSettings.heavyweaponAdsFovSensMultiplier = j.value("heavyweaponAdsFovSensMultiplier", 0.5f);

                modSettings.lasergewehrAdsFov = j.value("lasergewehrAdsFov", 65.0f);
                modSettings.lasergewehrAdsFovSensMultiplier = j.value("lasergewehrAdsFovSensMultiplier", 0.5f);

                modSettings.ubergewehrAdsFov = j.value("ubergewehrAdsFov", 65.0f);
                modSettings.ubergewehrAdsFovSensMultiplier = j.value("ubergewehrAdsFovSensMultiplier", 0.5f);


                modSettings.isSilentProtagonist = j.value("isSilentProtagonist", false);
                modSettings.isSilentAna = j.value("isSilentAna", false);
                modSettings.isSilentGrace = j.value("isSilentGrace", false);


                modSettings.isModLoadBeep = j.value("isModLoadBeep", false);
                modSettings.isLogGameConsoleToLogFile = j.value("isLogGameConsoleToLogFile", false);
                modSettings.isUseImgui = j.value("isUseImgui", true);


            }
            else {
                logErr("LoadFromFile: error opening file: %s using default mod settings.", filePath.c_str());
            }
        }
        catch (const nlohmann::json::parse_error& e) {
            logErr("LoadFromFile: JSON parsing error: %s saving default file...", e.what());
            modSettings.reset();     
            SaveToFile();
        }
    }



    void SaveToFile() {
        std::string filePath = FileOp::getModSettingsFilePath();
        logInfo("SaveToFile: saving to filePath: %s", filePath.c_str());

        nlohmann::json j;

        j["fastForwardKeyVkCode"] = modSettings.fastForwardKeyVkCode;
        j["normalSpeedKeyVkCode"] = modSettings.normalSpeedKeyVkCode;

        j["isAutoPickUpHealth"] = modSettings.isAutoPickUpHealth;
        j["isAutoPickUpArmor"] = modSettings.isAutoPickUpArmor;
        j["isAutoPickUpAmmo"] = modSettings.isAutoPickUpAmmo;
        j["isAutoPickUpHatchet"] = modSettings.isAutoPickUpHatchet;
        j["isAutoPickEnigma"] = modSettings.isAutoPickEnigma;

        j["isDisableItemHighlighthing"] = modSettings.isDisableItemHighlighthing;
        j["isSetAutoMapDefaultZoomToMin"] = modSettings.isSetAutoMapDefaultZoomToMin;

        j["isAdsToggle"] = modSettings.isAdsToggle;
        j["zoomKeyVkCode"] = modSettings.zoomKeyVkCode;  

        j["isUseCustomHud"] = modSettings.isUseCustomHud;
        j["hudConfiguration"] = modSettings.hudConfiguration;
        j["hudScale"] = modSettings.hudScale;
        j["hudFrameHeightMul"] = modSettings.hudFrameHeightMul;
        j["hudSafeFrameOffset"] = modSettings.hudSafeFrameOffset;
        j["showAlarmIcons"] = modSettings.showAlarmIcons;
        j["showMaxedOutText"] = modSettings.showMaxedOutText;


        j["isEnableHudWarning"] = modSettings.isEnableHudWarning;
        j["hudBlinkWarningSpeedMs"] = modSettings.hudBlinkWarningSpeedMs;

        j["hudHealthRedTriggerPrct"] = modSettings.hudHealthRedTriggerPrct;
        j["hudArmorRedTriggerPrct"] = modSettings.hudArmorRedTriggerPrct;

        j["hudHealthOrangeTriggerPrct"] = modSettings.hudHealthOrangeTriggerPrct;
        j["hudArmorOrangeTriggerPrct"] = modSettings.hudArmorOrangeTriggerPrct;


        j["isCustomCrosshair"] = modSettings.isCustomCrosshair;
        j["customCrosshairSize"] = modSettings.customCrosshairSize;
        j["customCrosshairOutlineThickness"] = modSettings.customCrosshairOutlineThickness;
        j["customCrosshairColor"] = { modSettings.customCrosshairColor.x, modSettings.customCrosshairColor.y, modSettings.customCrosshairColor.z, modSettings.customCrosshairColor.w };
        j["customCrosshairTargetColor"] = { modSettings.customCrosshairTargetColor.x, modSettings.customCrosshairTargetColor.y, modSettings.customCrosshairTargetColor.z, modSettings.customCrosshairTargetColor.w };
        j["customCrosshairOutlineColor"] = { modSettings.customCrosshairOutlineColor.x, modSettings.customCrosshairOutlineColor.y, modSettings.customCrosshairOutlineColor.z, modSettings.customCrosshairOutlineColor.w };

        j["isSkipFog"] = modSettings.isSkipFog;
        j["isHdrDisabled"] = modSettings.isHdrDisabled;
        j["colorSaturation"] = modSettings.colorSaturation;
        j["isDisabledSimulationFilter"] = modSettings.isDisabledSimulationFilter;


        j["isShowHudScoreDamageNumbers"] = modSettings.isShowHudScoreDamageNumbers;
        j["isShowHudScoreTotalNumber"] = modSettings.isShowHudScoreTotalNumber;

        j["isshowObjectiveMarkers"] = modSettings.isshowObjectiveMarkers;
        j["isFreeLeanOnly"] = modSettings.isFreeLeanOnly;
        j["headBobAmount"] = modSettings.headBobAmount;
        j["viewKickMax"] = modSettings.viewKickMax;
        j["isEnableGaussianBlur"] = modSettings.isEnableGaussianBlur;

        j["flashLightKeyVkCode"] = modSettings.flashLightKeyVkCode;
        j["headlightColor"] = { modSettings.headlightColor.x, modSettings.headlightColor.y, modSettings.headlightColor.z, modSettings.headlightColor.w };
        j["isHeadLightAdvancedSettingsEnabled"] = modSettings.isHeadLightAdvancedSettingsEnabled; 

        j["headlightIntensity"] = modSettings.headlightIntensity;
        j["headlightTarget_X"] = modSettings.headlightTarget_X;
        j["headlightLightEnd_X"] = modSettings.headlightLightEnd_X;
        j["isShowFlashLightIcon"] = modSettings.isShowFlashLightIcon;
       

        j["handgunAdsFov"] = modSettings.handgunAdsFov;
        j["handgunAdsFovSensMultiplier"] = modSettings.handgunAdsFovSensMultiplier;

        j["smgAdsFov"] = modSettings.smgAdsFov;
        j["smgAdsFovSensMultiplier"] = modSettings.smgAdsFovSensMultiplier;

        j["battlerifleAdsFov"] = modSettings.battlerifleAdsFov;
        j["battlerifleAdsFovSensMultiplier"] = modSettings.battlerifleAdsFovSensMultiplier;

        j["battlerifleScopeFov"] = modSettings.battlerifleScopeFov;
        j["battlerifleScopeFovSensMultiplier"] = modSettings.battlerifleScopeFovSensMultiplier;

        j["shotgunAdsFov"] = modSettings.shotgunAdsFov;
        j["shotgunAdsFovSensMultiplier"] = modSettings.shotgunAdsFovSensMultiplier;

        j["lkwAdsFov"] = modSettings.lkwAdsFov;
        j["lkwAdsFovSensMultiplier"] = modSettings.lkwAdsFovSensMultiplier;

        j["lkwscopeFov"] = modSettings.lkwscopeFov;
        j["lkwscopeFovSensMultiplier"] = modSettings.lkwscopeFovSensMultiplier;

        j["kampfpistolAdsFov"] = modSettings.kampfpistolAdsFov;
        j["kampfpistolAdsFovSensMultiplier"] = modSettings.kampfpistolAdsFovSensMultiplier;

        j["heavyweaponAdsFov"] = modSettings.heavyweaponAdsFov;
        j["heavyweaponAdsFovSensMultiplier"] = modSettings.heavyweaponAdsFovSensMultiplier;

        j["lasergewehrAdsFov"] = modSettings.lasergewehrAdsFov;
        j["lasergewehrAdsFovSensMultiplier"] = modSettings.lasergewehrAdsFovSensMultiplier;

        j["ubergewehrAdsFov"] = modSettings.ubergewehrAdsFov;
        j["ubergewehrAdsFovSensMultiplier"] = modSettings.ubergewehrAdsFovSensMultiplier;


        j["isSilentProtagonist"] = modSettings.isSilentProtagonist;
        j["isSilentAna"] = modSettings.isSilentAna;
        j["isSilentGrace"] = modSettings.isSilentGrace;


        j["isModLoadBeep"] = modSettings.isModLoadBeep;
        j["isLogGameConsoleToLogFile"] = modSettings.isLogGameConsoleToLogFile;
        j["isUseImgui"] = modSettings.isUseImgui;


        std::ofstream file(filePath);
        if (file.is_open()) {
            file << j.dump(4);      
        }

    }

  


    




    struct KeyInfo
    {
        const char* name;
        unsigned int vkCode;
    };

    const char* GetZoomBtnKeyNameForComboBox(unsigned int vkCode) {
        switch (vkCode) {
        case VK_LBUTTON: return "MOUSE LEFT";
        case VK_RBUTTON: return "MOUSE RIGHT";
        case VK_MBUTTON: return "MOUSE MIDDLE";
        case VK_XBUTTON1: return "MOUSE X1";
        case VK_XBUTTON2: return "MOUSE X2";
        case VK_BACK: return "BACK";
        case VK_TAB: return "TAB";
        case VK_CLEAR: return "CLEAR";
        case VK_RETURN: return "RETURN";
        case VK_SHIFT: return "SHIFT";
        case VK_CONTROL: return "CONTROL";
        case VK_MENU: return "MENU";
        case VK_PAUSE: return "PAUSE";
        case VK_CAPITAL: return "CAPITAL";
        case VK_ESCAPE: return "ESCAPE";
        case VK_SPACE: return "SPACE";
        case VK_PRIOR: return "PRIOR";
        case VK_NEXT: return "NEXT";
        case VK_END: return "END";
        case VK_HOME: return "HOME";
        case VK_LEFT: return "LEFT";
        case VK_UP: return "UP";
        case VK_RIGHT: return "RIGHT";
        case VK_DOWN: return "DOWN";
        case VK_SELECT: return "SELECT";
        case VK_PRINT: return "PRINT";
        case VK_EXECUTE: return "EXECUTE";
        case VK_SNAPSHOT: return "SNAPSHOT";
        case VK_INSERT: return "INSERT";
        case VK_DELETE: return "DELETE";
        case VK_HELP: return "HELP";
        case '0': return "0";
        case '1': return "1";
        case '2': return "2";
        case '3': return "3";
        case '4': return "4";
        case '5': return "5";
        case '6': return "6";
        case '7': return "7";
        case '8': return "8";
        case '9': return "9";
        case 'A': return "A";
        case 'B': return "B";
        case 'C': return "C";
        case 'D': return "D";
        case 'E': return "E";
        case 'F': return "F";
        case 'G': return "G";
        case 'H': return "H";
        case 'I': return "I";
        case 'J': return "J";
        case 'K': return "K";
        case 'L': return "L";
        case 'M': return "M";
        case 'N': return "N";
        case 'O': return "O";
        case 'P': return "P";
        case 'Q': return "Q";
        case 'R': return "R";
        case 'S': return "S";
        case 'T': return "T";
        case 'U': return "U";
        case 'V': return "V";
        case 'W': return "W";
        case 'X': return "X";
        case 'Y': return "Y";
        case 'Z': return "Z";
        case VK_LWIN: return "LWIN";
        case VK_RWIN: return "RWIN";
        case VK_APPS: return "APPS";
        case VK_SLEEP: return "SLEEP";
        case VK_NUMPAD0: return "NUMPAD0";
        case VK_NUMPAD1: return "NUMPAD1";
        case VK_NUMPAD2: return "NUMPAD2";
        case VK_NUMPAD3: return "NUMPAD3";
        case VK_NUMPAD4: return "NUMPAD4";
        case VK_NUMPAD5: return "NUMPAD5";
        case VK_NUMPAD6: return "NUMPAD6";
        case VK_NUMPAD7: return "NUMPAD7";
        case VK_NUMPAD8: return "NUMPAD8";
        case VK_NUMPAD9: return "NUMPAD9";
        case VK_MULTIPLY: return "MULTIPLY";
        case VK_ADD: return "ADD";
        case VK_SEPARATOR: return "SEPARATOR";
        case VK_SUBTRACT: return "SUBTRACT";
        case VK_DECIMAL: return "DECIMAL";
        case VK_DIVIDE: return "DIVIDE";
        case VK_F1: return "F1";
        case VK_F2: return "F2";
        case VK_F3: return "F3";
        case VK_F4: return "F4";
        case VK_F5: return "F5";
        case VK_F6: return "F6";
        case VK_F7: return "F7";
        case VK_F8: return "F8";
        case VK_F9: return "F9";
        case VK_F10: return "F10";
        case VK_F11: return "F11";
        case VK_F12: return "F12";
        default: return "UNKNOWN";
        }
    }



    const KeyInfo allKeys[] = {
        {"MOUSE LEFT", VK_LBUTTON},
        {"MOUSE RIGHT", VK_RBUTTON},
        {"MOUSE MIDDLE", VK_MBUTTON},
        {"MOUSE X1", VK_XBUTTON1},
        {"MOUSE X2", VK_XBUTTON2},
        {"BACK", VK_BACK},
        {"TAB", VK_TAB},
        {"CLEAR", VK_CLEAR},
        {"RETURN", VK_RETURN},
        {"SHIFT", VK_SHIFT},
        {"CONTROL", VK_CONTROL},
        {"MENU", VK_MENU},
        {"PAUSE", VK_PAUSE},
        {"CAPITAL", VK_CAPITAL},
        {"ESCAPE", VK_ESCAPE},
        {"SPACE", VK_SPACE},
        {"PRIOR", VK_PRIOR},
        {"NEXT", VK_NEXT},
        {"END", VK_END},
        {"HOME", VK_HOME},
        {"LEFT", VK_LEFT},
        {"UP", VK_UP},
        {"RIGHT", VK_RIGHT},
        {"DOWN", VK_DOWN},
        {"SELECT", VK_SELECT},
        {"PRINT", VK_PRINT},
        {"EXECUTE", VK_EXECUTE},
        {"SNAPSHOT", VK_SNAPSHOT},
        {"INSERT", VK_INSERT},
        {"DELETE", VK_DELETE},
        {"HELP", VK_HELP},
        {"0", '0'},
        {"1", '1'},
        {"2", '2'},
        {"3", '3'},
        {"4", '4'},
        {"5", '5'},
        {"6", '6'},
        {"7", '7'},
        {"8", '8'},
        {"9", '9'},
        {"A", 'A'},
        {"B", 'B'},
        {"C", 'C'},
        {"D", 'D'},
        {"E", 'E'},
        {"F", 'F'},
        {"G", 'G'},
        {"H", 'H'},
        {"I", 'I'},
        {"J", 'J'},
        {"K", 'K'},
        {"L", 'L'},
        {"M", 'M'},
        {"N", 'N'},
        {"O", 'O'},
        {"P", 'P'},
        {"Q", 'Q'},
        {"R", 'R'},
        {"S", 'S'},
        {"T", 'T'},
        {"U", 'U'},
        {"V", 'V'},
        {"W", 'W'},
        {"X", 'X'},
        {"Y", 'Y'},
        {"Z", 'Z'},
        {"LWIN", VK_LWIN},
        {"RWIN", VK_RWIN},
        {"APPS", VK_APPS},
        {"SLEEP", VK_SLEEP},
        {"NUMPAD0", VK_NUMPAD0},
        {"NUMPAD1", VK_NUMPAD1},
        {"NUMPAD2", VK_NUMPAD2},
        {"NUMPAD3", VK_NUMPAD3},
        {"NUMPAD4", VK_NUMPAD4},
        {"NUMPAD5", VK_NUMPAD5},
        {"NUMPAD6", VK_NUMPAD6},
        {"NUMPAD7", VK_NUMPAD7},
        {"NUMPAD8", VK_NUMPAD8},
        {"NUMPAD9", VK_NUMPAD9},
        {"MULTIPLY", VK_MULTIPLY},
        {"ADD", VK_ADD},
        {"SEPARATOR", VK_SEPARATOR},
        {"SUBTRACT", VK_SUBTRACT},
        {"DECIMAL", VK_DECIMAL},
        {"DIVIDE", VK_DIVIDE},
        {"F1", VK_F1},
        {"F2", VK_F2},
        {"F3", VK_F3},
        {"F4", VK_F4},
        {"F5", VK_F5},
        {"F6", VK_F6},
        {"F7", VK_F7},
        {"F8", VK_F8},
        {"F9", VK_F9},
        {"F10", VK_F10},
        {"F11", VK_F11},
        {"F12", VK_F12}


    };

    


    void ShowTooltip(const char* tooltip) {
        ImGui::BeginTooltip();
        ImGui::Text("%s", tooltip);
        ImGui::EndTooltip();
    }


    void insertToolTipSameLine(const char* tooltipText) {
        ImGui::SameLine();
        ImGui::Text("    ");
        ImGui::SameLine();        
        ImGui::PushFont(icons_font_awesome);
        ImGui::Text(ICON_FA_QUESTION_CIRCLE);
        ImGui::PopFont();
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(tooltipText);
        }
    }




    void showModMenu(bool* p_open) {

        ImGui::SetNextWindowPos(ImVec2(0, 0));      
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);       

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        float verticalSpacingEndTab = viewport->Size.y * .1f;


        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));         

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));    

        ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);



        if (ImGui::BeginTabBar("Tabs")) {

            ImGui::Indent();

            if (ImGui::BeginTabItem("Auto PickUp")) {


            
                ImGui::NewLine();                
                ImGui::TextWrapped("Click the check boxes of the features you want. This lets you pick up items automatically when you're close enough to them without having to press the use key");              
                ImGui::NewLine(); 

                ImGui::NewLine();
                ImGui::Checkbox("Auto Pick Up Health", &Menu::modSettings.isAutoPickUpHealth);
                insertToolTipSameLine("Automatically pick up health but only if your health is below max health to prevent unwanted health overide");
                
              
                ImGui::NewLine();  
                ImGui::Checkbox("Auto Pick Up Armor", &Menu::modSettings.isAutoPickUpArmor);
                insertToolTipSameLine("Automatically pick up armor from dead enemies and items in the world");

                ImGui::NewLine();  
                ImGui::Checkbox("Auto Pick Up Ammo", &Menu::modSettings.isAutoPickUpAmmo);
                insertToolTipSameLine("Automatically pick up Ammo on the floor, on dead enemies or in Infinite boxes like grenade crates");  
                if (Menu::modSettings.isAutoPickUpAmmo) {
                    ImGui::Indent();
                    ImGui::PushStyleColor(ImGuiCol_Text, yellowColor);
                    ImGui::TextWrapped("You will need 2 copies of the same weapon in your inventory and equip it at least once to auto pick up the ammo inside weapons of that type");
                    ImGui::PopStyleColor();    
                    ImGui::Unindent();         
                }

                ImGui::NewLine();  
                ImGui::Checkbox("Auto Pick Up Hatchet", &Menu::modSettings.isAutoPickUpHatchet);
                insertToolTipSameLine("Automatically pick up hatchets in the world. Still investigating false positive for this one");

                ImGui::NewLine();  
                ImGui::Checkbox("Auto Pick Up Enigma Code", &Menu::modSettings.isAutoPickEnigma);
                insertToolTipSameLine("Automatically pick up Enigma codes on dead officers");
                
               
                ImGui::Dummy(ImVec2(0.0f, verticalSpacingEndTab));


                ImGui::EndTabItem();    
                ImGui::Unindent();         

            }




            if (ImGui::BeginTabItem("Fast Forward")) {

                ImGui::Indent();

                ImGui::NewLine();
                ImGui::TextWrapped("This lets you Fast Forward any gameplay sequence that is not a pre-recorded bink video.");
                ImGui::NewLine();


                static bool isWaitingForFastForwardKeyPress = false;
                static bool isWaitingForNormalSpeedKeyPress = false;

                ImGui::NewLine();      


                ImGui::Text("Fast Forward Key:\t");
                if (!isWaitingForFastForwardKeyPress) {
                    std::string fastForwardKeyName = ModSettings::keyCodeToString(Menu::modSettings.fastForwardKeyVkCode);
                    ImGui::SameLine();
                    if (Menu::isDuplicateKeyError()) {
                        ImGui::PushStyleColor(ImGuiCol_Text, redColor);
                        ImGui::Text("%s\t", fastForwardKeyName.c_str(), Menu::modSettings.fastForwardKeyVkCode);
                        ImGui::PopStyleColor();    
                    }
                    else {
                        ImGui::Text("%s\t", fastForwardKeyName.c_str(), Menu::modSettings.fastForwardKeyVkCode);
                    }
                }
                else {
                    ImGui::SameLine();
                    ImGui::PushStyleColor(ImGuiCol_Text, orangeColor);
                    ImGui::Text("Press New Fast Forward Key...\t");
                    ImGui::PopStyleColor();    
                }
                ImGui::SameLine();
                if (ImGui::Button("Rebind Fast Forward Key")) {
                    isWaitingForFastForwardKeyPress = true;
                }

                if (Menu::isDuplicateKeyError()) {
                    ImGui::NewLine();  
                    ImGui::PushStyleColor(ImGuiCol_Text, redColor);
                    ImGui::Text("KEY ALREADY BOUND TO ANOTHER MOD ACTION !");
                    ImGui::PopStyleColor();    
                }


                if (isWaitingForFastForwardKeyPress && Menu::lastKeyPressed != -1) {
                    Menu::modSettings.fastForwardKeyVkCode = Menu::lastKeyPressed;
                    isWaitingForFastForwardKeyPress = false;
                    Menu::lastKeyPressed = -1;
                }


                ImGui::NewLine();  
                ImGui::NewLine();  

                ImGui::Text("Normal Speed Key:\t");
                if (!isWaitingForNormalSpeedKeyPress) {
                    std::string normalSpeedKeyName = ModSettings::keyCodeToString(Menu::modSettings.normalSpeedKeyVkCode);
                    ImGui::SameLine();
                    if (Menu::isDuplicateKeyError()) {
                        ImGui::PushStyleColor(ImGuiCol_Text, redColor);
                        ImGui::Text("%s\t", normalSpeedKeyName.c_str(), Menu::modSettings.normalSpeedKeyVkCode);
                        ImGui::PopStyleColor();    
                    }
                    else {
                        ImGui::Text("%s\t", normalSpeedKeyName.c_str(), Menu::modSettings.normalSpeedKeyVkCode);
                    }
                }
                else {
                    ImGui::SameLine();
                    ImGui::PushStyleColor(ImGuiCol_Text, orangeColor);
                    ImGui::Text("Press New Normal Speed Key...\t");
                    ImGui::PopStyleColor();    
                }
                ImGui::SameLine();
                if (ImGui::Button("Rebind Normal Speed Key")) {
                    isWaitingForNormalSpeedKeyPress = true;
                }

                if (Menu::isDuplicateKeyError()) {
                    ImGui::NewLine();  
                    ImGui::PushStyleColor(ImGuiCol_Text, redColor);
                    ImGui::Text("KEY ALREADY BOUND TO ANOTHER MOD ACTION !");
                    ImGui::PopStyleColor();    
                }

                if (isWaitingForNormalSpeedKeyPress && Menu::lastKeyPressed != -1) {
                    Menu::modSettings.normalSpeedKeyVkCode = Menu::lastKeyPressed;
                    isWaitingForNormalSpeedKeyPress = false;
                    Menu::lastKeyPressed = -1;     
                }                              

                ImGui::Dummy(ImVec2(0.0f, verticalSpacingEndTab));


                ImGui::EndTabItem();
                ImGui::Unindent();         

            }


            if (ImGui::BeginTabItem("FlashLight")) {

                ImGui::Indent();

                ImGui::NewLine();
                ImGui::Text("This gives the player an optional flashlight that can be turned on/off with a key bind.");
                insertToolTipSameLine("You can change the color/alpha of the flashligh, bind it to a key and have an icon indicator its state.\nThis goes very well with the Disable items highlighting as it makes looking for items in the world more engaging whith the help of the flashlight.");                           
                ImGui::NewLine();  
                ImGui::NewLine();

                static bool isWaitingForFlashLightKeyPress = false;

                ImGui::Text("FlashLight Toggle Key Bind:\t");
                if (!isWaitingForFlashLightKeyPress) {
                    std::string flashLightKeyName = ModSettings::keyCodeToString(Menu::modSettings.flashLightKeyVkCode);
                    ImGui::SameLine();
                    if (Menu::isDuplicateKeyError()) {
                        ImGui::PushStyleColor(ImGuiCol_Text, redColor);
                        ImGui::Text("%s\t", flashLightKeyName.c_str(), Menu::modSettings.flashLightKeyVkCode);
                        ImGui::PopStyleColor();    
                    }
                    else {
                        ImGui::Text("%s\t", flashLightKeyName.c_str(), Menu::modSettings.flashLightKeyVkCode);
                    }
                }
                else {
                    ImGui::SameLine();
                    ImGui::PushStyleColor(ImGuiCol_Text, orangeColor);
                    ImGui::Text("Press New FlashLight Key...\t");
                    ImGui::PopStyleColor();    
                }
                ImGui::SameLine();

                if (ImGui::Button("Rebind FlashLight Key")) {
                    isWaitingForFlashLightKeyPress = true;
                }

                if (Menu::isDuplicateKeyError()) {
                    ImGui::NewLine();  
                    ImGui::PushStyleColor(ImGuiCol_Text, redColor);
                    ImGui::Text("KEY ALREADY BOUND TO ANOTHER MOD ACTION !");
                    ImGui::PopStyleColor();    
                }

                if (isWaitingForFlashLightKeyPress && Menu::lastKeyPressed != -1) {
                    Menu::modSettings.flashLightKeyVkCode = Menu::lastKeyPressed;
                    isWaitingForFlashLightKeyPress = false;
                    Menu::lastKeyPressed = -1;
                }
                ImGui::NewLine();

                ImGui::NewLine();
                ImGui::Checkbox("Show Flash Light Status Icon", &Menu::modSettings.isShowFlashLightIcon);
                insertToolTipSameLine("Shows an icon top right of the screen when the flashlight is on");

                ImGui::NewLine();
                ImGui::ColorEdit3("User FlashLight Color/Alpha", (float*)&Menu::modSettings.headlightColor);
                insertToolTipSameLine("You can set the tint and alpha value of the flashlight. I would recommend to leave it to default. (default 255, 255, 255, 255)");

                ImGui::NewLine();
                ImGui::NewLine();
                ImGui::Checkbox("Advanced FlashLight Options", &Menu::modSettings.isHeadLightAdvancedSettingsEnabled);
                insertToolTipSameLine("Shows more options to customize the flashlight");

                if (Menu::modSettings.isHeadLightAdvancedSettingsEnabled) {
                    ImGui::Indent();
                    ImGui::PushStyleColor(ImGuiCol_Text, yellowColor);
                    ImGui::Text("Read the tooltips before Modifying those");
                    ImGui::PopStyleColor();    

                    ImGui::NewLine();
                    ImGui::SliderFloat("FlashLight Intensity", &Menu::modSettings.headlightIntensity, 0.01f, 5.0f, "%.2f"); 
                    std::string intensityFormated = std::format(" {:.2f}", modSettingsConst::headlightIntensityDef);
                    std::string intensityToolTipStr = "How bright light of the flashlight should be (default: " + intensityFormated + ")";
                    insertToolTipSameLine(intensityToolTipStr.c_str());

                    ImGui::NewLine();
                    ImGui::SliderFloat("FlashLight Target X", &Menu::modSettings.headlightTarget_X, .5f, 5.0f, "%.2f");
                    std::string targetXValFormated = std::format(" {:.2f}", modSettingsConst::headlightTargetXDef); 
                    std::string targetXToolTipStr = "How wide the cone of the flashlight should be (default: " + targetXValFormated + ")";                 
                    insertToolTipSameLine(targetXToolTipStr.c_str());

                    ImGui::NewLine();
                    ImGui::SliderFloat("FlashLight Length", &Menu::modSettings.headlightLightEnd_X, .5f, 50.0f, "%.2f");
                    std::string endXValFormated = std::format(" {:.2f}", modSettingsConst::headlightEndXDef);
                    std::string endXToolTipStr = "How far should the flashlight cast light (default: " + endXValFormated + ")";
                    insertToolTipSameLine(endXToolTipStr.c_str());


                    ImGui::Unindent();
                }       

                ImGui::Dummy(ImVec2(0.0f, verticalSpacingEndTab));



                ImGui::EndTabItem();   
                ImGui::Unindent();

            }



            if (ImGui::BeginTabItem("Weapons")) {

                ImGui::Indent();

                static float minAdsFov = 20.0f;
                static float maxAdsFov = 90.0f;
                float fov = idCvarManager::getCvarFloat("g_fov");
                if (fov != 0.0f) {
                    maxAdsFov = fov - (float)0.001;
                    if (maxAdsFov <= minAdsFov) {
                        maxAdsFov = minAdsFov + 5.0f;
                    }
                }

                float minSensMultiplier = 0.05f;
                float maxSensMultiplier = 1.0f;


                ImGui::NewLine();  
                ImGui::TextWrapped("Weapons ADS FOV and Sens");
                insertToolTipSameLine("You can set the Field Of View (FOV) for each weapon which has a aim down sight (ADS) view or scope.\n You can also set the mouse sensitivity multiplier, the lower it is, the slower the mouse will move in ads/scope view");
                ImGui::NewLine();
               
                ImGui::NewLine();  
                ImGui::Text("Handgun ADS FOV (default 85)");
                ImGui::SliderFloat("##HandgunADSFOV", &Menu::modSettings.handgunAdsFov, minAdsFov, maxAdsFov);
                ImGui::NewLine();  
                ImGui::Text("Handgun ADS Sensitivity Multiplier (default 0.5)");
                ImGui::SliderFloat("##HandgunSensMultiplier", &Menu::modSettings.handgunAdsFovSensMultiplier, minSensMultiplier, maxSensMultiplier, "%.2f");
                ImGui::NewLine();  
                ImGui::NewLine();  
                ImGui::Text("SMG ADS FOV (default 80");
                ImGui::SliderFloat("##SMGADSFOV", &Menu::modSettings.smgAdsFov, minAdsFov, maxAdsFov);
                ImGui::NewLine();  
                ImGui::Text("SMG ADS Sensitivity Multiplier (default 0.5)");
                ImGui::SliderFloat("##SMGSensMultiplier", &Menu::modSettings.smgAdsFovSensMultiplier, minSensMultiplier, maxSensMultiplier);
                ImGui::NewLine();  
                ImGui::NewLine();  
                ImGui::Text("Battlerifle ADS FOV (default 65)");
                ImGui::SliderFloat("##BattlerifleADSFOV", &Menu::modSettings.battlerifleAdsFov, minAdsFov, maxAdsFov);
                ImGui::NewLine();  
                ImGui::Text("Battlerifle ADS Sensitivity Multiplier (default 0.5) ");
                ImGui::SliderFloat("##BattlerifleSensMultiplier", &Menu::modSettings.battlerifleAdsFovSensMultiplier, minSensMultiplier, maxSensMultiplier);
                ImGui::NewLine();  
                ImGui::NewLine();  
                ImGui::Text("Battlerifle Scope FOV (default 40)");
                ImGui::SliderFloat("##BattlerifleScopeFOV", &Menu::modSettings.battlerifleScopeFov, minAdsFov, maxAdsFov);
                ImGui::NewLine();  
                ImGui::Text("Battlerifle Scope Sensitivity Multiplier (default 0.35)");
                ImGui::SliderFloat("##BattlerifleScopeSensMultiplier", &Menu::modSettings.battlerifleScopeFovSensMultiplier, minSensMultiplier, maxSensMultiplier);
                ImGui::NewLine();  
                ImGui::NewLine();  
                ImGui::Text("Shotgun ADS FOV (default 75)");
                ImGui::SliderFloat("##ShotgunADSFOV", &Menu::modSettings.shotgunAdsFov, minAdsFov, maxAdsFov);
                ImGui::NewLine();  
                ImGui::Text("Shotgun ADS Sensitivity Multiplier (default 0.5)");
                ImGui::SliderFloat("##ShotgunSensMultiplier", &Menu::modSettings.shotgunAdsFovSensMultiplier, minSensMultiplier, maxSensMultiplier);
                ImGui::NewLine();  
                ImGui::NewLine();  
                ImGui::Text("LKW ADS FOV (default 65)");
                ImGui::SliderFloat("##LKWADSFOV", &Menu::modSettings.lkwAdsFov, minAdsFov, maxAdsFov);
                ImGui::NewLine();  
                ImGui::Text("LKW ADS Sensitivity Multiplier (default 0.5)");
                ImGui::SliderFloat("##LKWSensMultiplier", &Menu::modSettings.lkwAdsFovSensMultiplier, minSensMultiplier, maxSensMultiplier);
                ImGui::NewLine();  
                ImGui::NewLine();  
                ImGui::Text("LKW Scope FOV (default 40)");
                ImGui::SliderFloat("##LKWScopeFOV", &Menu::modSettings.lkwscopeFov, minAdsFov, maxAdsFov);
                ImGui::NewLine();  
                ImGui::Text("LKW Scope Sensitivity Multiplier (default 35)");
                ImGui::SliderFloat("##LKWScopeSensMultiplier", &Menu::modSettings.lkwscopeFovSensMultiplier, minSensMultiplier, maxSensMultiplier);
                ImGui::NewLine();  
                ImGui::NewLine();  
                ImGui::Text("Kampfpistol ADS FOV (default 85)");
                ImGui::SliderFloat("##KampfpistolADSFOV", &Menu::modSettings.kampfpistolAdsFov, minAdsFov, maxAdsFov);
                ImGui::NewLine();  
                ImGui::Text("Kampfpistol ADS Sensitivity Multiplier (default 0.5)");
                ImGui::SliderFloat("##KampfpistolSensMultiplier", &Menu::modSettings.kampfpistolAdsFovSensMultiplier, minSensMultiplier, maxSensMultiplier);
                ImGui::NewLine();  
                ImGui::NewLine();  
                ImGui::Text("Heavy Weapon ADS FOV (default 65)");
                ImGui::SliderFloat("##HeavyWeaponADSFOV", &Menu::modSettings.heavyweaponAdsFov, minAdsFov, maxAdsFov);
                ImGui::NewLine();  
                ImGui::Text("Heavy Weapon ADS Sensitivity Multiplier (default 0.5)");
                ImGui::SliderFloat("##HeavyWeaponSensMultiplier", &Menu::modSettings.heavyweaponAdsFovSensMultiplier, minSensMultiplier, maxSensMultiplier);
                ImGui::NewLine();  
                ImGui::NewLine();  
                ImGui::Text("Lasergewehr ADS FOV (default 65)");
                ImGui::SliderFloat("##LasergewehrADSFOV", &Menu::modSettings.lasergewehrAdsFov, minAdsFov, maxAdsFov);
                ImGui::NewLine();  
                ImGui::Text("Lasergewehr ADS Sensitivity Multiplier (default 0.5)");
                ImGui::SliderFloat("##LasergewehrSensMultiplier", &Menu::modSettings.lasergewehrAdsFovSensMultiplier, minSensMultiplier, maxSensMultiplier);
                ImGui::NewLine();  
                ImGui::NewLine();  
                ImGui::Text("Ubergewehr ADS FOV  (default 65)");
                ImGui::SliderFloat("##UbergewehrADSFOV", &Menu::modSettings.ubergewehrAdsFov, minAdsFov, maxAdsFov);
                ImGui::NewLine();  
                ImGui::Text("Ubergewehr ADS Sensitivity Multiplier (default 0.5)");
                ImGui::SliderFloat("##UbergewehrSensMultiplier", &Menu::modSettings.ubergewehrAdsFovSensMultiplier, minSensMultiplier, maxSensMultiplier);

                ImGui::Dummy(ImVec2(0.0f, verticalSpacingEndTab));


                ImGui::EndTabItem();
                ImGui::Unindent();

            }





            if (ImGui::BeginTabItem("Hud")) {    

                ImGui::Indent();

                ImGui::NewLine();
                ImGui::Checkbox("Enable Low Health/Armor Warning", &Menu::modSettings.isEnableHudWarning);
                insertToolTipSameLine("Makes the Health and/or Armor Number change color when they get below a precentage of your choice. This is a very effective feedback try it!");

                if (Menu::modSettings.isEnableHudWarning) {
                    ImGui::Indent();

                    ImGui::NewLine();
                    ImGui::SliderInt("Warning Speed", &Menu::modSettings.hudBlinkWarningSpeedMs, 100, 1000, "%d ms");
                    insertToolTipSameLine("how often per second armor/health blink when too low (default 500 milliseconds)");


                    ImGui::NewLine();
                    ImGui::SliderInt("Health Orange Trigger %", &Menu::modSettings.hudHealthOrangeTriggerPrct, 0, 100, "%d%%");
                    insertToolTipSameLine("Below this percentage health number will become Orange (default 40%). Set it to 0 to disable.");

                    ImGui::NewLine();
                    ImGui::SliderInt("Health Red Trigger %", &Menu::modSettings.hudHealthRedTriggerPrct, 0, 100, "%d%%");
                    insertToolTipSameLine("Below this percentage health number will start Blinking Red (default 20%).Set it to 0 to disable.");
                    ImGui::NewLine();
                    ImGui::SliderInt("Armor Orange Trigger %", &Menu::modSettings.hudArmorOrangeTriggerPrct, 0, 100, "%d%%");
                    insertToolTipSameLine("Below this percentage armor number will  become Orange (default 40%).Set it to 0 to disable.");   
                    ImGui::NewLine();
                    ImGui::SliderInt("Armor Red Trigger %", &Menu::modSettings.hudArmorRedTriggerPrct, 0, 100, "%d%%");
                    insertToolTipSameLine("Below this percentage armor number will start blinking Red (default 20%).Set it to 0 to disable.");

                    ImGui::Unindent();         
                }
               

                ImGui::NewLine();   


                ImGui::NewLine();

                if (ImGui::Checkbox("Customise Hud", &Menu::modSettings.isUseCustomHud)) {
                    if (! Menu::modSettings.isUseCustomHud) {
                        logInfo("Mod Menu hudSafeFrameOffset is being reset to %.3f", modSettingsConst::safeFrameDefaultVal);
                        Menu::modSettings.hudSafeFrameOffset = modSettingsConst::safeFrameDefaultVal;
                    }
                }
                insertToolTipSameLine("This lets you customise the hud size, postion, elements, crosshair...");


                ImGui::Indent();
                ImGui::PushStyleColor(ImGuiCol_Text, yellowColor);
                ImGui::Text("If you changed the game resolution since game was launched and now the crosshair is not centered, reload a save to fix it");
                ImGui::PopStyleColor();
                ImGui::Unindent();


                if (!Menu::modSettings.isUseCustomHud) {

                    ImGui::NewLine();                   


                    ImGui::SliderFloat("Hud Offset", &Menu::modSettings.hudSafeFrameOffset, 0.01f, cachedCvarsManager::m_safeFrameValueMax);
                    ImGui::SameLine();
                    if (ImGui::Button("RESET")) {
                        Menu::modSettings.hudSafeFrameOffset = modSettingsConst::safeFrameDefaultVal;
                    }
                    insertToolTipSameLine("How far from the screen borders should the hud should be. (Default: 0.025) This option is availabled only if you don't use custom hud.");                   

                    

                    ImGui::NewLine();

                }
                else {                    


                    if (Menu::modSettings.isUseCustomHud) {

                        ImGui::Indent();

                        ImGui::NewLine();
                        if (!Menu::modSettings.isCustomCrosshair) {
                            ImGui::PushStyleColor(ImGuiCol_Text, yellowColor);
                            ImGui::Text("Game Crosshair is disabled when using custom hud, use custom crosshair instead if you need a crosshair");
                            ImGui::PopStyleColor();     
                        }
                        ImGui::Checkbox("Custom Crosshair", &Menu::modSettings.isCustomCrosshair);
                        insertToolTipSameLine("Toggles the displayer of the mod custom crosshair.");


                        if (Menu::modSettings.isCustomCrosshair) {

                            ImGui::Indent();

                            ImGui::NewLine();
                            ImGui::ColorEdit3("Crosshair Color", (float*)&Menu::modSettings.customCrosshairColor);
                            insertToolTipSameLine("Crosshair color when you are NOT aiming at an enemy");

                            ImGui::NewLine();
                            ImGui::ColorEdit3("Crosshair Color When looking at Enemy", (float*)&Menu::modSettings.customCrosshairTargetColor);
                            insertToolTipSameLine("Crosshair color when you are aiming at an enemy. you can set it the same color as above to make sure crosshair always keep the same color");

                            ImGui::NewLine();
                            ImGui::ColorEdit3("Crosshair Outline Color", (float*)&Menu::modSettings.customCrosshairOutlineColor);
                            insertToolTipSameLine("You may want to choose something that is opposite to your crosshair color so you can see the crosshair well when looking at bright or dark surfaces");


                            ImGui::NewLine();
                            if (ImGui::Button("Reset Crosshair Color")) {
                                Menu::modSettings.customCrosshairColor = ImVec4(modSettingsConst::gameHudColorVec[0], modSettingsConst::gameHudColorVec[1], modSettingsConst::gameHudColorVec[2], modSettingsConst::gameHudColorVec[3]);
                                Menu::modSettings.customCrosshairTargetColor = ImVec4(modSettingsConst::gameHudColorVec[0], modSettingsConst::gameHudColorVec[1], modSettingsConst::gameHudColorVec[2], modSettingsConst::gameHudColorVec[3]);
                                Menu::modSettings.customCrosshairOutlineColor = ImVec4(modSettingsConst::redHudColorVec[0], modSettingsConst::redHudColorVec[1], modSettingsConst::redHudColorVec[2], modSettingsConst::redHudColorVec[3]);
                            }
                            insertToolTipSameLine("Set the crosshair colors close to the game colors scheme");


                            ImGui::NewLine();
                            ImGui::NewLine();

                            int crosshairSizeIncrement = 1;
                            int crosshairSizeMin = 1;
                            int crosshairSizeMax = 20;

                            ImGui::SliderInt("Custom Crosshair Size", &Menu::modSettings.customCrosshairSize, crosshairSizeMin, crosshairSizeMax);
                            insertToolTipSameLine("How big the custom crosshair should be (in pixels)");

                            int thicknessIncrement = 1;
                            int thicknessMin = 1;
                            int thicknessMax = 5;

                            ImGui::NewLine();
                            ImGui::SliderInt("Custom Crosshair Outline Thickness ", &Menu::modSettings.customCrosshairOutlineThickness, thicknessMin, thicknessMax);
                            insertToolTipSameLine("Makes the custom crosshair easy to see when looking at very dark or very bright areas");
                            ImGui::Unindent();         
                            ImGui::NewLine();
                            ImGui::NewLine();
                        }


                        ImGui::NewLine();

                        if (cachedCvarsManager::get_WindowHeightInt() != 1080) {

                            ImGui::PushStyleColor(ImGuiCol_Text, yellowColor);
                            ImGui::TextWrapped("These presets were made for 1080p, they may not work with your resolution, if they don't, choose Custom Size Hud and experiment with Hud Scale and Hud Frame Height Mul sliders");
                            ImGui::PopStyleColor();       
                        }


                        ImGui::Combo("##HUDConfig", (int*)&Menu::modSettings.hudConfiguration, hudChoiceItemsV2, IM_ARRAYSIZE(hudChoiceItemsV2));
                        ImGui::SameLine();
                        ImGui::Text("HUD Config");
                        insertToolTipSameLine("Choose how big/where you want the health/armor/ammo and icons to be");


                        if (Menu::modSettings.hudConfiguration == (int)HUDConfigV2::CustomConfigHUD) {
                            ImGui::Indent();

                            ImGui::NewLine();
                            ImGui::SliderFloat("Hud Scale", &Menu::modSettings.hudScale, 0.1f, 3.0f);
                            insertToolTipSameLine("How big the hud should be. Experiment and see what works or not. (default 1)");


                            ImGui::NewLine();
                            ImGui::SliderFloat("Hud Frame Height Mul", &Menu::modSettings.hudFrameHeightMul, 0.1f, 3.0f);
                            insertToolTipSameLine("How close to the bottom of the screen should the hud be. Experiment and see what works or not. (default 1)");





                            ImGui::NewLine();

                            ImGui::Unindent();                             
                        }
                        ImGui::NewLine();
                        ImGui::NewLine();

                        ImGui::Unindent();         
                    }

                }


                

               

                ImGui::NewLine();
                ImGui::Checkbox("Show Objective Markers", &Menu::modSettings.isshowObjectiveMarkers);
                insertToolTipSameLine("Toggles the display of objective markers in the world but keep them on the map");
                if (!Menu::modSettings.isshowObjectiveMarkers) {
                    ImGui::Indent();
                    ImGui::PushStyleColor(ImGuiCol_Text, yellowColor);
                    ImGui::Text("markers will still show while you press down the hint key");
                    ImGui::PopStyleColor(); 
                    ImGui::Unindent();
                }

                ImGui::NewLine();
                ImGui::Checkbox("Show Alarm Icons", &Menu::modSettings.showAlarmIcons);
                insertToolTipSameLine("Toggles the red rounded Alarm icons and text at the top of the screen (default on)");

                ImGui::NewLine();
                ImGui::Checkbox("Show Maxed Out Text", &Menu::modSettings.showMaxedOutText);
                insertToolTipSameLine("Toggles the display of 'Maxed Out!' pop up when you are full on specific resource (default on)");   

                ImGui::NewLine();
                ImGui::Checkbox("Show Score Damage Numbers", &Menu::modSettings.isShowHudScoreDamageNumbers);
                insertToolTipSameLine("Toggles the Hud damage numbers like 400 Soldier Kills during simulations");


                ImGui::NewLine();
                ImGui::Checkbox("Show Score Total Number", &Menu::modSettings.isShowHudScoreTotalNumber);
                insertToolTipSameLine("Toggles the Total Score Number at the top of the hud when in a simulation but keeps the small combo bar + text");

               
                ImGui::Dummy(ImVec2(0.0f, verticalSpacingEndTab));



                ImGui::EndTabItem();
                ImGui::Unindent();         

            }




            if (ImGui::BeginTabItem("Q.O.L")) {

                ImGui::Indent(); 

                ImGui::NewLine();                 
                ImGui::Checkbox("Disable Items Highlighting", &Menu::modSettings.isDisableItemHighlighthing);  
                insertToolTipSameLine("Toggles the flashing/Highlighting of items like armor/Health/weapons in the world to make exploration more interesting, especially with the flashlight! (game default: false)");

                if (Menu::modSettings.isDisableItemHighlighthing) {
                    ImGui::Indent();                    
                    ImGui::PushStyleColor(ImGuiCol_Text, yellowColor);
                    ImGui::Text("Requires save/level reload to take effect");
                    ImGui::PopStyleColor(); 
                    ImGui::Unindent();
                }

                ImGui::NewLine();    
                ImGui::NewLine();                 
                ImGui::Checkbox("Set Default AutoMap zoom to max zoomed out", &Menu::modSettings.isSetAutoMapDefaultZoomToMin);
                insertToolTipSameLine("When you open the map it will show the map in its maxed zoomed out state and you can then zoom in/out as usual (game default: false)");

                ImGui::NewLine();         
                ImGui::NewLine();                 
                ImGui::Checkbox("Free Lean Only", &Menu::modSettings.isFreeLeanOnly);
                insertToolTipSameLine("If box is checked, it will disable the auto positioning/sliding of the player when leaning, which may gets rid of the frequent twitches/glitches that occur  (game default: false)");


                ImGui::NewLine();  
                ImGui::NewLine();    
                ImGui::SliderFloat("Headbob amount", &Menu::modSettings.headBobAmount, 0.1f, 1.0f);
                insertToolTipSameLine("How much the camera move/shakes when you walk or sprint. Higer val => more shakes (game default: 1)");

                ImGui::NewLine();  
                ImGui::SliderFloat("Camera Damage View Shake Max", &Menu::modSettings.viewKickMax, 0.5f, 2.0f);
                insertToolTipSameLine("How much the camera can move/shakes when you take damage (game default: 2)");
            

             

               

               

                ImGui::NewLine();    
                ImGui::NewLine();
                float mouseSens = idCvarManager::getCvarFloat("m_sensitivity");
               
                if (ImGui::Button("S-")) {
                    mouseSens -= 0.001f;
                    if (mouseSens <= 0.0f) {
                        mouseSens = 0.0f;
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("S+")) {
                    mouseSens += 0.001f;
                    if (mouseSens >= 10.0f) {
                        mouseSens = 10.0f;
                    }
                }
                
                ImGui::SameLine();
                ImGui::SliderFloat("Set Precise Mouse Sensitivity", &mouseSens, 0.0f, 10.0f);
                insertToolTipSameLine("This gives you more precision to change sensitivity compared to game menu (game default: 3)");
                idCvarManager::setCvar("m_sensitivity", std::to_string(mouseSens));
        

                ImGui::NewLine();    
                ImGui::NewLine();  
                if (Menu::modSettings.isAdsToggle) {
                    ImGui::PushStyleColor(ImGuiCol_Text, yellowColor);
                    ImGui::Text("DON T FORGET TO SET THE ZOOM KEY BELOW IF YOU ENABLE THIS");
                    ImGui::PopStyleColor();     
                }
                ImGui::Checkbox("ADS Key Toggle", &Menu::modSettings.isAdsToggle);
                insertToolTipSameLine("Makes the zoom key a toggle. DON T FORGET TO SET THE ZOOM KEY BELOW IF YOU ENABLE THIS");


                float comboAlpha = Menu::modSettings.isAdsToggle ? 1.0f : 0.4f;

                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, comboAlpha);

                static const char* selectedKey = GetZoomBtnKeyNameForComboBox(Menu::modSettings.zoomKeyVkCode);

                if (ImGui::BeginCombo("What key is bound to Zoom in your game?", selectedKey))
                {
                    for (const KeyInfo& keyInfo : allKeys)
                    {
                        bool isSelected = (selectedKey == keyInfo.name);
                        if (ImGui::Selectable(keyInfo.name, isSelected))
                        {
                            selectedKey = keyInfo.name;
                            Menu::modSettings.zoomKeyVkCode = keyInfo.vkCode;
                        }
                        if (isSelected)
                        {
                            ImGui::SetItemDefaultFocus();        
                        }
                    }

                    ImGui::EndCombo();
                }

                ImGui::PopStyleVar(); 

                ImGui::Dummy(ImVec2(0.0f, verticalSpacingEndTab));


                ImGui::EndTabItem();
                ImGui::Unindent();

            }

            

            if (ImGui::BeginTabItem("Graphics")) {

                ImGui::Indent();

                ImGui::NewLine();                     

                ImGui::NewLine();  
                ImGui::Checkbox("Remove Simulation Filter", &Menu::modSettings.isDisabledSimulationFilter);
                insertToolTipSameLine("Removes the 'sreen effect' post process effect when playing Simulation Missions (game default: enabled)");
                if (Menu::modSettings.isDisabledSimulationFilter) {
                    ImGui::Indent();
                    ImGui::PushStyleColor(ImGuiCol_Text, yellowColor);
                    ImGui::Text("Requires game restart to re-enable again");
                    ImGui::PopStyleColor();     
                    ImGui::Unindent();
                }               


                ImGui::NewLine();  
                ImGui::Checkbox("Disable Hdr", &Menu::modSettings.isHdrDisabled);
                insertToolTipSameLine("Removes hdr and the 'pumping' effect on the image and other filters. Goes well with the flashlight. (game default: Hdr enabled)");
               


                ImGui::NewLine();  
                ImGui::Checkbox("Enable Gaussian Blur", &Menu::modSettings.isEnableGaussianBlur);
                insertToolTipSameLine("This lets you disable Gaussian Blur which for example blurs the view when using the Dieselkraftwerk (game default: enabled)");


                ImGui::NewLine();  
                ImGui::Checkbox("Skip fog", &Menu::modSettings.isSkipFog);
                insertToolTipSameLine("Skips the rendering of fog in the game (game default: fog enabled)");


                ImGui::NewLine();  
                float lensFlareRationF = idCvarManager::getCvarFloat("r_lensFlaresRatio");
                ImGui::SliderFloat("Lens Flare Ratio", &lensFlareRationF, 0.0f, 1.0f);
                insertToolTipSameLine("How much flare should ligth create (game default: 1)");
                idCvarManager::setCvar("r_lensFlaresRatio", std::to_string(lensFlareRationF));                


                ImGui::NewLine();  
                ImGui::SliderFloat("color Saturation", &Menu::modSettings.colorSaturation, 0.0f, 1.0f);
                insertToolTipSameLine("How saturated the colors should be. Set it to 0 is you want to play the game in black and white (game default: 1)");

                ImGui::Dummy(ImVec2(0.0f, verticalSpacingEndTab));


                ImGui::EndTabItem();
                ImGui::Unindent();

            }     




            if (ImGui::BeginTabItem("Sound")) {

                ImGui::Indent();

                ImGui::NewLine();  
                ImGui::Checkbox("Quiet BJ in First Person", &Menu::modSettings.isSilentProtagonist);
                insertToolTipSameLine("This mutes BJ inner thoughs, but he will still grunt when damaged. Will not work during video cutscenes though. (game default: false)");

                ImGui::NewLine();  
                ImGui::Checkbox("Quiet Ana", &Menu::modSettings.isSilentAna);
                insertToolTipSameLine("Mutes Ana when she talks to Bj on the radio, but will also mutes her in the main hub. (game default: false)");

                ImGui::NewLine();  
                ImGui::Checkbox("Quiet Grace", &Menu::modSettings.isSilentGrace);
                insertToolTipSameLine("Mutes Grace when she talks to Bj on the radio, but will also mutes her in the main hub. (game default: false)");


                ImGui::NewLine();  
                ImGui::NewLine();  
                ImGui::Checkbox("Play Beep When Mod loads succesfully", &Menu::modSettings.isModLoadBeep);
                insertToolTipSameLine("Plays a beep when mod loads without errors which can be usefull when troubleshooting the mod (default: false)");


                ImGui::Dummy(ImVec2(0.0f, verticalSpacingEndTab));

                ImGui::EndTabItem();

                ImGui::Unindent();

            }          




            if (ImGui::BeginTabItem("Misc.")) {
               
                ImGui::Indent();

                ImGui::NewLine();
                float consoleTransparencyF = idCvarManager::getCvarFloat("com_consoleTransparency");
                ImGui::SliderFloat("Console Transparency", &consoleTransparencyF, 0.1f, 1.0f);
                insertToolTipSameLine("Console Transparency...(default: 1)");
                idCvarManager::setCvar("com_consoleTransparency", std::to_string(consoleTransparencyF));


                if (Config::getBuildType() != buildType::nexusRelease) {
                    ImGui::NewLine();
                    ImGui::Checkbox("Log Game Console To Mod Log File", &Menu::modSettings.isLogGameConsoleToLogFile);
                    insertToolTipSameLine("if checked, will log the game console output to KaibzMod_Log.txt");
                }


                ImGui::NewLine();      
                ImGui::Text(BuildInfo::getImGuiBuildStr().c_str());

                ImGui::NewLine();      
                ImGui::Text(Config::getModVersionStr().c_str());    


                
                                                        
                ImGui::Text("Made by Kaibz. (700 hours of work)");
                ImGui::Text("I hope you enjoy the mod !");


                ImGui::Dummy(ImVec2(0.0f, verticalSpacingEndTab));


                ImGui::EndTabItem();
                ImGui::Unindent();

               
            }





            ImGui::EndTabBar();
        }

        ImGui::PopStyleColor();     
        ImGui::End();     
        ImGui::PopStyleVar();     





    }
    
}   
