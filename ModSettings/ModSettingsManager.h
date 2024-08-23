#pragma once


#include <atomic>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include "../Config/Config.h"
#include "../Wolf2/idCvarManager.h"
#include "../FileOp/FileOp.h"
#include "../Wolf2/idColor.h"
#include "ModSettings.h"
#include "../Wolf2/ImGuiManager.h"
#include "../Wolf2/cachedCvarsManager.h"
#include "../Wolf2/idSWF_Manager.h"
#include "../Wolf2/soundManager.h"
#include "../Wolf2/idAutomapManager.h"





enum AutoPickUpType
{
    none,
    health,
    armor,
    ammo,
    hatchet,          
    enigma
};

class ModSettingsManager
{
private:

    static ModSettings m_modSettings;
public:


    static void updateCvars();

    static void updateFromImGui(const ModSettings modSettings);
    static ModSettings get();

    static void resetHudSettings();



    static bool isModLoadBeep();

    static void debugPrint();


    static unsigned int getNormalSpeedKeyCode();
    static unsigned int getFastForwardKeyCode();

    static std::string getNormalSpeedKeyBindStr();

    static unsigned int getFlashLightKeyCode();

    static unsigned int getHighFrameMvtFixKeyVkCode();

    static bool isCustomCrosshairEnabled();
    static bool isAlarmIconsEnabled();
    static bool isMaxedOutEnabled();
    static bool isShowWorldMarkers();
    static bool  isShowHudScoreTotalNumber();
    static bool isSilentProtagonist();
    static bool isAutoPickItem(AutoPickUpType pickUpType);

    static bool isDisableItemHighlight();

    static bool isDisableSimulationFilter();


    static bool isDebugMidnight();
    static bool isDebugKeyPropAnim();

    static void setMainLightSettingsToDefault();

    static float getHeadLightIntensity();

    static float getHeadLightTargetX();

    static float getHeadLightEndX();

    static bool isShowFlashLightIcon();

    static idColor getUserFlashlightColor();

    static bool isAdsToggleEnabled();

    static unsigned int getZoomKeyVkCode();

    static float getHeadBobAmount();

    static bool isCustomHudEnabled();

    static bool isHudWarningEnabled();

    static int getOrangeArmorTriggerPrct();
    static int getOrangeHealthTriggerPrct();
    static int getRedHealthTriggerPrct();
    static int getRedHudArmorTriggerPrct();

    static unsigned int getHudWarningBlinkSpeedMs();    

    static void updateHudPosAndScaleValsV2();

    static float getHudSafeFrameOffset();

    static float getHudScale();

    static float gethudFrameHeightMul();

    static bool getIsLogGameConsoleToLogFile();
    static bool getIsUseImgui();
    //static void setIsLogGameConsoleToLogFile(bool isLogToFile);
    
};

