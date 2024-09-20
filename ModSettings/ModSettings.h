#pragma once

#include <Windows.h>
#include <string>
#include <unordered_map>
#include "../ImGui/dependencies/imgui/imgui.h"
#include "../Config/Config.h"



enum HUDConfigV2 {
    BiggestHud,
    BiggerHud,
    GameDefaultHud,
    SmallerHud,
    MiniHud,   
    CustomConfigHUD
};

namespace modSettingsConst {

    const inline float safeFrameDefaultVal = 0.025f;
    const inline std::vector<float>gameHudColorVec = { 0.894f, 0.871f, 0.816f, 1.0f };
    const inline std::vector<float>redHudColorVec = { 0.5f, 0.0f, 0.0f, 1.0 };
    const inline std::vector<float>headlightDefaultColorVec = { 0.894f, 0.871f, 0.816f, 1.0f };

    const inline float headlightIntensityDef = 0.5f;
    const inline float headlightTargetXDef = 2.26f;
    const inline float headlightEndXDef = 35.0f;


    const inline int hudHealthRedTriggerPrctDef = 25;
    const inline int hudArmorRedTriggerPrctDef = 25;
    const inline int hudHealthOrangeTriggerPrctDef = 40;
    const inline int hudArmorOrangeTriggerPrctDef = 40;

    const inline int debugLevelDef = (int)ModConfig::info;

}



class ModSettings {
public:
    ModSettings();

    void reset();

    bool isAutoPickUpHealth;
    bool isAutoPickUpArmor;
    bool isAutoPickUpAmmo;
    bool isAutoPickUpHatchet;
    bool isAutoPickEnigma;    


    unsigned int fastForwardKeyVkCode;
    unsigned int normalSpeedKeyVkCode;
   
    unsigned int flashLightKeyVkCode;
    ImVec4 headlightColor;
    bool isHeadLightAdvancedSettingsEnabled;
    float headlightIntensity;          
    float headlightTarget_X;                  
    float headlightLightEnd_X;          
    bool isShowFlashLightIcon;


    unsigned int highFrameMvtFixKeyVkCode;

    float handgunAdsFov;
    float handgunAdsFovSensMultiplier;

    float smgAdsFov;
    float smgAdsFovSensMultiplier;

    float battlerifleAdsFov;
    float battlerifleAdsFovSensMultiplier;

    float battlerifleScopeFov;
    float battlerifleScopeFovSensMultiplier;

    float shotgunAdsFov;
    float shotgunAdsFovSensMultiplier;
  
    float lkwAdsFov;
    float lkwAdsFovSensMultiplier;

    float lkwscopeFov;
    float lkwscopeFovSensMultiplier;

    float kampfpistolAdsFov;
    float kampfpistolAdsFovSensMultiplier;

    float heavyweaponAdsFov;
    float heavyweaponAdsFovSensMultiplier;

    float lasergewehrAdsFov;
    float lasergewehrAdsFovSensMultiplier;

    float ubergewehrAdsFov;
    float ubergewehrAdsFovSensMultiplier;       


    bool isUseCustomHud;


    float hudScale;
    int hudConfiguration;
    float hudFrameHeightMul;         
    float hudSafeFrameOffset;               
    bool showAlarmIcons;
    bool showMaxedOutText;

    bool isEnableHudWarning;
    int hudBlinkWarningSpeedMs;
    int hudHealthRedTriggerPrct;
    int hudArmorRedTriggerPrct;
    int hudHealthOrangeTriggerPrct;
    int hudArmorOrangeTriggerPrct;

    bool isCustomCrosshair;
    int customCrosshairSize;
    int customCrosshairOutlineThickness;

    ImVec4 customCrosshairColor;
    ImVec4 customCrosshairTargetColor;
    ImVec4 customCrosshairOutlineColor;


    bool isShowHudScoreDamageNumbers;
    bool isShowHudScoreTotalNumber;

    bool isshowObjectiveMarkers;     

    bool isDisableItemHighlighthing;
    bool isSetAutoMapDefaultZoomToMin;
   
    bool isAdsToggle;
    unsigned int zoomKeyVkCode;          
    bool isSwapBindsWhenDualWielding;

    bool isPauseGameOnAltTab;

    bool isFreeLeanOnly;
    float headBobAmount;
    float viewKickMax;
    bool isEnableGaussianBlur;


    bool isSkipFog;
    bool isHdrDisabled;
    bool isDisabledSimulationFilter;
    float colorSaturation;

    bool isSilentProtagonist; 
    bool isSilentAna;
    bool isSilentGrace;

    bool isModLoadBeep;
    bool isLogGameConsoleToLogFile;
    bool isUseImgui;
    
   


   



private:
    void initializeMembers();
public:
    static std::string keyCodeToString(int keyCode);

};