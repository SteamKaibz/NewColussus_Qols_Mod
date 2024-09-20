#include "ModSettings.h"


ModSettings::ModSettings() {
    initializeMembers();
}

void ModSettings::reset() {
    initializeMembers();
}


std::string ModSettings::keyCodeToString(int keyCode) {
   
    if (keyCode == 0) {
        return "Not Bound";
    }
    
    if (keyCode >= VK_F1 && keyCode <= VK_F24) {
        return "F" + std::to_string(keyCode - VK_F1 + 1);
    }

    else if (keyCode == VK_SPACE) {
        return "Space";
    }
    else if (keyCode == VK_SHIFT) {
        return "Shift";
    }
    else if (keyCode == VK_LSHIFT) {
        return "L Shift";
    }
    else if (keyCode == VK_RSHIFT) {
        return "R Shift";
    }

    std::unordered_map<int, std::string> numpadKeyNames = {
        {VK_NUMPAD0, "Numpad 0"},
        {VK_NUMPAD1, "Numpad 1"},
        {VK_NUMPAD2, "Numpad 2"},
        {VK_NUMPAD3, "Numpad 3"},
        {VK_NUMPAD4, "Numpad 4"},
        {VK_NUMPAD5, "Numpad 5"},
        {VK_NUMPAD6, "Numpad 6"},
        {VK_NUMPAD7, "Numpad 7"},
        {VK_NUMPAD8, "Numpad 8"},
        {VK_NUMPAD9, "Numpad 9"},
        {VK_MULTIPLY, "Numpad *"},
        {VK_ADD, "Numpad +"},
        {VK_SEPARATOR, "Numpad Enter"},
        {VK_SUBTRACT, "Numpad -"},
        {VK_DECIMAL, "Numpad ."},
        {VK_DIVIDE, "Numpad /"},
    };

    auto numpadKey = numpadKeyNames.find(keyCode);
    if (numpadKey != numpadKeyNames.end()) {
        return numpadKey->second;
    }

    UINT scanCode = MapVirtualKey(keyCode, MAPVK_VK_TO_VSC);
    UINT extended = MapVirtualKey(keyCode, MAPVK_VK_TO_VSC_EX);

    if (extended != 0) {
        scanCode |= 0x100;       
    }

    LONG lParam = (scanCode << 16) | 1;

    char keyName[50];
    if (GetKeyNameText(lParam, keyName, sizeof(keyName)) > 0) {
        return std::string(keyName);
    }

    return "???";
}

void ModSettings::initializeMembers() {
    fastForwardKeyVkCode = VK_F1;
    normalSpeedKeyVkCode = VK_F2;

    isAutoPickUpHealth = false;
    isAutoPickUpArmor = false;
    isAutoPickUpAmmo = false;
    isAutoPickUpHatchet = false;
    isAutoPickEnigma = false;
    
    isAdsToggle = false;
    zoomKeyVkCode = VK_RBUTTON;
    isSwapBindsWhenDualWielding = false;


    isUseCustomHud = false;
    hudConfiguration = (int)HUDConfigV2::BiggerHud;
    hudScale = 1.0f;
    hudFrameHeightMul = 1.0f;
    hudSafeFrameOffset = modSettingsConst::safeFrameDefaultVal;
    showAlarmIcons = true;
    showMaxedOutText = true;

    isEnableHudWarning = true;
    hudBlinkWarningSpeedMs = 300;

    hudHealthRedTriggerPrct = modSettingsConst::hudHealthRedTriggerPrctDef;
    hudArmorRedTriggerPrct = modSettingsConst::hudArmorRedTriggerPrctDef;

    hudHealthOrangeTriggerPrct = modSettingsConst::hudHealthOrangeTriggerPrctDef;
    hudArmorOrangeTriggerPrct = modSettingsConst::hudArmorOrangeTriggerPrctDef;

    isCustomCrosshair = false;
    customCrosshairSize = 3;
    customCrosshairOutlineThickness = 1;

    customCrosshairColor = ImVec4(modSettingsConst::gameHudColorVec[0], modSettingsConst::gameHudColorVec[1], modSettingsConst::gameHudColorVec[2], modSettingsConst::gameHudColorVec[3]);
    customCrosshairTargetColor = ImVec4(modSettingsConst::gameHudColorVec[0], modSettingsConst::gameHudColorVec[1], modSettingsConst::gameHudColorVec[2], modSettingsConst::gameHudColorVec[3]);
    customCrosshairOutlineColor = ImVec4(modSettingsConst::redHudColorVec[0], modSettingsConst::redHudColorVec[1], modSettingsConst::redHudColorVec[2], modSettingsConst::redHudColorVec[3]);
    isSkipFog = false;
    isHdrDisabled = false;
    colorSaturation = 1.0f;
    isDisabledSimulationFilter = false;

    isDisableItemHighlighthing = false;
    isSetAutoMapDefaultZoomToMin = false;

    isshowObjectiveMarkers = true;

    isShowHudScoreDamageNumbers = true;
    isShowHudScoreTotalNumber = true;
   

    isFreeLeanOnly = false;
    headBobAmount = 0.1f;
    viewKickMax = 0.5f;
    isEnableGaussianBlur = false;

    flashLightKeyVkCode = VK_F3;
    headlightColor = ImVec4(modSettingsConst::headlightDefaultColorVec[0], modSettingsConst::headlightDefaultColorVec[1], modSettingsConst::headlightDefaultColorVec[2], modSettingsConst::headlightDefaultColorVec[3]);

    isHeadLightAdvancedSettingsEnabled = false;
    headlightIntensity = modSettingsConst::headlightIntensityDef;
    headlightTarget_X = modSettingsConst::headlightTargetXDef;
    headlightLightEnd_X = modSettingsConst::headlightEndXDef;
    isShowFlashLightIcon = true;


    highFrameMvtFixKeyVkCode = 0;
   

    handgunAdsFov = 85.0f;
    handgunAdsFovSensMultiplier = .5f;

    smgAdsFov = 80.0f;
    smgAdsFovSensMultiplier = .5f;

    battlerifleAdsFov = 65.0f;
    battlerifleAdsFovSensMultiplier = .5f;

    battlerifleScopeFov = 40.0f;
    battlerifleScopeFovSensMultiplier = .35f;

    shotgunAdsFov = 75.0f;
    shotgunAdsFovSensMultiplier = .5f;

    lkwAdsFov = 65.0f;
    lkwAdsFovSensMultiplier = .5f;

    lkwscopeFov = 40.0f;
    lkwscopeFovSensMultiplier = .35f;

    kampfpistolAdsFov = 85.0f;
    kampfpistolAdsFovSensMultiplier = .5f;

    heavyweaponAdsFov = 65.0f;
    heavyweaponAdsFovSensMultiplier = .5f;

    lasergewehrAdsFov = 65.0f;
    lasergewehrAdsFovSensMultiplier = .5f;

    ubergewehrAdsFov = 65.0f;
    ubergewehrAdsFovSensMultiplier = .5f;


    isSilentProtagonist = false;
    isSilentAna = false;
    isSilentGrace = false;

    isPauseGameOnAltTab = true;

    isModLoadBeep = false;
    isLogGameConsoleToLogFile = false;
    isUseImgui = true;
}