#include "idFocusTrackerManager.h"




idPlayer* idFocusTrackerManager::m_idPlayerPtr = nullptr;

crosshairInfoIconState_t idFocusTrackerManager::m_lastCrosshairInfoIconState = CROSSHAIRINFOICON_NONE;

std::vector<std::string> idFocusTrackerManager::m_debugCrosshairInfoMaterialsNamesVec;

const char* idFocusTrackerManager::m_grenadeMatrSuffix = "grenade";
const size_t idFocusTrackerManager::m_grenadeMatrSuffixLen = strlen(m_grenadeMatrSuffix);

const char* idFocusTrackerManager::m_axeMatrSuffix = "axe";
const size_t idFocusTrackerManager::m_axeMatrSuffixLen = strlen(m_axeMatrSuffix);

const char* idFocusTrackerManager::m_hatchetMatrSuffix = "hatchet";
const size_t idFocusTrackerManager::m_hatchetMatrSuffixLen = strlen(m_hatchetMatrSuffix);

const char* idFocusTrackerManager::m_enigmaMatrSuffix = "enigma";
const size_t idFocusTrackerManager::m_enigmaMatrSuffixLen = strlen(m_enigmaMatrSuffix);

const char* idFocusTrackerManager::m_hudIconMatrPrefix = "textures/guis/hud/icons/mercury/64/";
const size_t idFocusTrackerManager::m_hudIconMatrPrefixLen = strlen("textures/guis/hud/icons/mercury/64/");

const char* idFocusTrackerManager::m_crosshairInfoTextUse = "_use";
const char* idFocusTrackerManager::m_crosshairInfoTextMelee = "_melee";





//! here are all spotted material names when CROSSHAIRINFOICON_SINGLE:
//! textures/guis/hud/icons/mercury/64/battery_big
//! textures/guis/hud/icons/mercury/64/readable
//! textures/guis/hud/icons/mercury/64/dkw
//! textures/guis/hud/icons/mercury/64/enigma
//! textures/guis/hud/icons/mercury/64/grenade      Yes (especially cause you can find those in the world as well)
//! textures/guis/hud/icons/mercury/64/hatchet      Maybe  
//! textures/guis/hud/icons/mercury/64/axe          Maybe 
//! textures/guis/hud/icons/mercury/64/door_unavaliable
//! textures/guis/hud/icons/mercury/64/use 
//! textures/guis/hud/icons/mercury/64/kits     weapon upgrade items
//! textures/guis/hud/icons/mercury/64/gold     yes
//! textures/guis/hud/icons/mercury/64/starcard yes
//! The problem with the hatchet icon is that it's the icon to open hatches but also the icon to auto pick up the hatchet when thrown.



 /// we're now logging everytime we get a new material so that we can identify all the "use btn" situations also make sure that the scenario where we have a CROSSHAIRINFOICON_SINGLE and a null matr ptr is unique to the dropped helmet situation.
bool idFocusTrackerManager::shouldItemBePickedUp(idPlayer* idPlayerPtr) {
    if (idPlayerPtr) {
        
        crosshairInfoIconState_t iconState = idPlayerPtr->playerVolatileUnsaved.focusTracker.crosshairInfo.flags;

        //? remove the log when done playing the game to the end
        if (iconState & CROSSHAIRINFOICON_SINGLE) {
            debug_LogAll_CROSSHAIRINFOICON_SINGLE_Materials((idResource*)m_idPlayerPtr->playerVolatileUnsaved.focusTracker.crosshairInfo.material, &idPlayerPtr->playerVolatileUnsaved.focusTracker.crosshairInfo);
        }
        //! if we're maxxed out on something no need to press use.
        if (iconState & CROSSHAIRINFOICON_MAXED) {
            return false;
        }
        else if ((iconState & CROSSHAIRINFOICON_HEALTH) && ModSettingsManager::isAutoPickItem(health)) {
            auto healthIndicator = idPlayerPtr->playerVolatile.hudInfo.healthIndicator;
            return healthIndicator.health < healthIndicator.healthMax;
        }
        else if ((iconState & CROSSHAIRINFOICON_ARMOR) && ModSettingsManager::isAutoPickItem(armor)) {
            return true;
        }
        //? tis is the one i'm not 100% sure about as it could return true in situation we might not want but i guess we'll spot it soon enough while playing...
        else if ((iconState & CROSSHAIRINFOICON_AMMO) && ModSettingsManager::isAutoPickItem(ammo)) {
            return true;
        }
        else if (iconState & CROSSHAIRINFOICON_SINGLE ) {
            auto matr = m_idPlayerPtr->playerVolatileUnsaved.focusTracker.crosshairInfo.material;
            if (matr) {
               //const char* matrName = m_idPlayerPtr->playerVolatileUnsaved.focusTracker.crosshairInfo.getMaterial()->name.str;
                const char* matrName = matr->name.str;
               

               //? if use Text is not _use we don't bother checking the rest as we don't want to auto open hatches or takedown. it means use Text will certainly be _melee
               if (!(strncmp(m_idPlayerPtr->playerVolatileUnsaved.focusTracker.crosshairInfo.useText, m_crosshairInfoTextUse, 4) == 0)) {
                   return false;
               }

               if (ModSettingsManager::isAutoPickItem(ammo) && (strncmp(matrName + m_hudIconMatrPrefixLen, m_grenadeMatrSuffix, m_grenadeMatrSuffixLen) == 0)) {
                   return true;
               }               
               if (ModSettingsManager::isAutoPickItem(hatchet) && (strncmp(matrName + m_hudIconMatrPrefixLen, m_axeMatrSuffix, m_axeMatrSuffixLen) == 0)) {
                   return true;
               }
               if (ModSettingsManager::isAutoPickItem(hatchet) && (strncmp(matrName + m_hudIconMatrPrefixLen, m_hatchetMatrSuffix, m_hatchetMatrSuffixLen) == 0)) {
                   return true;
               }
               if (ModSettingsManager::isAutoPickItem(enigma) && (strncmp(matrName + m_hudIconMatrPrefixLen, m_enigmaMatrSuffix, m_enigmaMatrSuffixLen) == 0)) {
                   return true;
               }
            }
            else {//! if matr is null and CROSSHAIRINFOICON_SINGLE it should be a helmet dropped by enemy
                if (ModSettingsManager::isAutoPickItem(armor)) {
                    return true;
                }
            }
        }              
      
    }
    return false;

}


void idFocusTrackerManager::debug_LogAll_CROSSHAIRINFOICON_SINGLE_Materials(idResource* resPtr, void* crosshairInfoAddr) {
    static std::vector<std::string> uniqueMaterialNamesVec;

    if (!resPtr) return;

    std::string materialName= idResourceManager::getDeclName(resPtr);
    if (std::find(uniqueMaterialNamesVec.begin(), uniqueMaterialNamesVec.end(), materialName) == uniqueMaterialNamesVec.end()) {
        uniqueMaterialNamesVec.push_back(materialName);
        logInfo("Debug: found CrosshairInfo material: %p, with name: %s (crosshairInfo: %p)", resPtr, materialName.c_str(),  crosshairInfoAddr);
    }
}


//bool idFocusTrackerManager::isMaxHealth(idPlayer* idplayer)
//{
//    if (!idplayer) {
//        return true; //! not sure what to return here but this seems the best choice.
//    }
//    idHudHealthIndicatorInfo* idHudHealthIndicatorInfoPtr = (idHudHealthIndicatorInfo*)((char*)idplayer + m_idHudHealthIndicatorInfoOffset);
//    bool isMaxHealth = idHudHealthIndicatorInfoPtr->health >= idHudHealthIndicatorInfoPtr->healthMax;
//    /*if (isMaxHealth) {
//        logInfo("isMaxHealth: health is max or overcharge, not auto picking up health item");
//    }*/
//    return isMaxHealth;
//
//}
//
//bool idFocusTrackerManager::isMaxArmor(idPlayer* idplayer)
//{
//    if (!idplayer) {
//        return true; //! not sure what to return here but this seems the best choice.
//    }
//    idHudHealthIndicatorInfo* idHudHealthIndicatorInfoPtr = (idHudHealthIndicatorInfo*)((char*)idplayer + m_idHudHealthIndicatorInfoOffset);
//    bool isMaxArmor = idHudHealthIndicatorInfoPtr->armor >= idHudHealthIndicatorInfoPtr->armorMax;
//    //if (isMaxArmor) {
//    //	//logInfo("isMaxArmor: armor is max, not auto pressing use key");
//    //}
//    return isMaxArmor;
//}


//? i tried to use idFocusTracker_PlayerSmth_F81030_Hook get the crosshairInfoIconState from the tracker...basically you can not cause the game must be writing/reading to it so fast you will always get a value of 0 even i CE and Reclass show you the value in realite. 
//! this is used mainly for debugging atm
void idFocusTrackerManager::acquirecrosshairInfoDataForDebug(idPlayer* idPlayer_a1) {


    if (idPlayer_a1) {
        m_idPlayerPtr = idPlayer_a1;
        m_lastCrosshairInfoIconState = idPlayer_a1->playerVolatileUnsaved.focusTracker.crosshairInfo.flags;
    }
    else {
        m_idPlayerPtr = nullptr;
        m_lastCrosshairInfoIconState = CROSSHAIRINFOICON_NONE;
    }    
}

//! used in RenderSpriteInstance_Hook to cancel display of maxed out
bool idFocusTrackerManager::islastFocusedCrosshairIconStateMaxedOut() {
    return m_lastCrosshairInfoIconState & CROSSHAIRINFOICON_MAXED;
}



//! used by imgui debug
std::string idFocusTrackerManager::getCrosshairInfoStr() {
    if (!MemHelper::isBadReadPtr(m_idPlayerPtr)) {

        std::string matrName = "No Material.";
        idMaterial* matr = m_idPlayerPtr->playerVolatileUnsaved.focusTracker.crosshairInfo.material;
        //logWarn("getCrosshairInfoStr: skipping rendering of info for debug: matr is: %p", matr);

        if (!MemHelper::isBadReadPtr(matr)) {
            matrName = idResourceManager::getDeclName((idResource*)m_idPlayerPtr->playerVolatileUnsaved.focusTracker.crosshairInfo.material);
        } 
        else {
            matrName = "Material is bad ptr.";
        }
     
       
        std::string iconStateStr = getCrosshairInfoIconStateStr(m_idPlayerPtr->playerVolatileUnsaved.focusTracker.crosshairInfo.flags);

        std::string itemCountStr = std::to_string(m_idPlayerPtr->playerVolatileUnsaved.focusTracker.crosshairInfo.count);

        return "Flags: " + iconStateStr + "\nMatr Name: " + matrName + "\nitem count: " + itemCountStr;
    }
    else {
        return "idPlayer is BAD PTR can not get info.";
    }
}


std::string idFocusTrackerManager::getCrosshairInfoIconStateStr(crosshairInfoIconState_t crosshairInfoIconState) {
    std::string result;     

    if (crosshairInfoIconState & CROSSHAIRINFOICON_NONE) result += "CROSSHAIRINFOICON_NONE | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_SHOW) result += "CROSSHAIRINFOICON_SHOW | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_NORMALCOLOR) result += "CROSSHAIRINFOICON_NORMALCOLOR | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_NEGATIVECOLOR) result += "CROSSHAIRINFOICON_NEGATIVECOLOR | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_SUBDUEDTEXTCOLOR) result += "CROSSHAIRINFOICON_SUBDUEDTEXTCOLOR | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_CANTUSE) result += "CROSSHAIRINFOICON_CANTUSE | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_TEXT) result += "CROSSHAIRINFOICON_TEXT | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_HEALTH) result += "CROSSHAIRINFOICON_HEALTH | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_AMMO) result += "CROSSHAIRINFOICON_AMMO | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_ARMOR) result += "CROSSHAIRINFOICON_ARMOR | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_BATTERY) result += "CROSSHAIRINFOICON_BATTERY | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_WEAPON) result += "CROSSHAIRINFOICON_WEAPON | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_SINGLE) result += "CROSSHAIRINFOICON_SINGLE | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_CONT) result += "CROSSHAIRINFOICON_CONT | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_MAXED) result += "CROSSHAIRINFOICON_MAXED | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_NOTMAXED) result += "CROSSHAIRINFOICON_NOTMAXED | ";
    if (crosshairInfoIconState & CROSSHAIRINFOICON_ONEVALID) result += "CROSSHAIRINFOICON_ONEVALID | ";

    // Remove the trailing " | "
    if (!result.empty()) {
        result = result.substr(0, result.size() - 3);
    }
    else {
        result = "NO CROSSHAIR INFO";
    }
    return result;
}


/*td::string idFocusTrackerManager::crosshairInfoIconStateToString(crosshairInfoIconState_t state) {
    static const std::unordered_map<crosshairInfoIconState_t, std::string> stateToString = {
        {CROSSHAIRINFOICON_NONE, "CROSSHAIRINFOICON_NONE"},
        {CROSSHAIRINFOICON_SHOW, "CROSSHAIRINFOICON_SHOW"},
        {CROSSHAIRINFOICON_NORMALCOLOR, "CROSSHAIRINFOICON_NORMALCOLOR"},
        {CROSSHAIRINFOICON_NEGATIVECOLOR, "CROSSHAIRINFOICON_NEGATIVECOLOR"},
        {CROSSHAIRINFOICON_SUBDUEDTEXTCOLOR, "CROSSHAIRINFOICON_SUBDUEDTEXTCOLOR"},
        {CROSSHAIRINFOICON_CANTUSE, "CROSSHAIRINFOICON_CANTUSE"},
        {CROSSHAIRINFOICON_TEXT, "CROSSHAIRINFOICON_TEXT"},
        {CROSSHAIRINFOICON_HEALTH, "CROSSHAIRINFOICON_HEALTH"},
        {CROSSHAIRINFOICON_AMMO, "CROSSHAIRINFOICON_AMMO"},
        {CROSSHAIRINFOICON_ARMOR, "CROSSHAIRINFOICON_ARMOR"},
        {CROSSHAIRINFOICON_BATTERY, "CROSSHAIRINFOICON_BATTERY"},
        {CROSSHAIRINFOICON_WEAPON, "CROSSHAIRINFOICON_WEAPON"},
        {CROSSHAIRINFOICON_SINGLE, "CROSSHAIRINFOICON_SINGLE"},
        {CROSSHAIRINFOICON_CONT, "CROSSHAIRINFOICON_CONT"},
        {CROSSHAIRINFOICON_MAXED, "CROSSHAIRINFOICON_MAXED"},
        {CROSSHAIRINFOICON_NOTMAXED, "CROSSHAIRINFOICON_NOTMAXED"},
        {CROSSHAIRINFOICON_ONEVALID, "CROSSHAIRINFOICON_ONEVALID"}
    };

    auto it = stateToString.find(state);
    if (it != stateToString.end()) {
        return it->second;
    }

    return "Unknown";
}*/
