#include "Tests.h"
#include "../Wolf2/idKisculeNodeActionMidnightControlManager.h"


movementMode_t Tests::m_lastPendingMovementMode = MOVEMENT_MODE_NUM;
movementMode_t Tests::m_lastCurrentMovementMode = MOVEMENT_MODE_NUM;

std::vector<__int64> Tests::addArgFrom_371DB0_Vec = {};


void Tests::printUseKeyState()
{
    auto idplayer = idGameLocalManager::getIdPlayer();
    if (MemHelper::isBadReadPtr(idplayer)) {
        logErr("printUseKeyState: idplayer is bad ptr returning");
        return;
    }
    logInfo("playerUseState addr: %p", &idplayer->playerVolatile.playerUseState);
}

void Tests::PrintIdPlayerInfo() {
    auto idplayer = idGameLocalManager::getIdPlayer();
    if (MemHelper::isBadReadPtr(idplayer)) {
        logErr("PrintIdPlayerInfo: idplayer is bad ptr returning");
        return;
    }
    char* idplayerCharPtr = (char*)idplayer;
    logInfo("idPlayer addr: %p", idplayerCharPtr);
    logInfo("idPlayer::idPlayerConstant addr: %p", (idplayerCharPtr + 0x44B8));
    logInfo("idPlayer::idPlayerEditable addr: %p", (idplayerCharPtr + 0x4B80));

    char* idPlayerVolatile = idplayerCharPtr + 0x4EE0;
    char* idPlayerVolatileUnsaved = idplayerCharPtr + 0x20380;
    logInfo("idPlayer::idPlayerVolatile addr: %p", (idPlayerVolatile));
    logInfo("idPlayer::idPlayerVolatile: controlledEntities addr: %p", (idPlayerVolatile + 0x9B78));

    char* idHudInfo = idPlayerVolatile + 0x7718;
    logInfo("idPlayer::idPlayerVolatile: idHudInfo addr: %p", (idHudInfo));
    logInfo("idPlayer::idPlayerVolatile: idHudInfo: idHudWeaponAmmoStatusInfo addr: %p", (idHudInfo + 0x5E8));     
    logInfo("idPlayer::idPlayerVolatile: idHudInfo: idHudReticleInfo addr: %p", (idHudInfo + 0x930));
    logInfo("idPlayer::idPlayerVolatile: idHudInfo: idHudHealthIndicatorInfo addr: %p", (idHudInfo + 0x9A0));


    char* coverModEnterDirV = idPlayerVolatile + 0x2468;
    logInfo("coverModEnterDirV  addr: %p", coverModEnterDirV);

    char* coverPoseAvoidanceBlend = idPlayerVolatile + 0x2510;
    logInfo("coverPoseAvoidanceBlend  addr: %p", coverPoseAvoidanceBlend);



    logInfo("idPlayer::idPlayerVolatile: idPlayerHud addr: %p", (idPlayerVolatile + 0x3BC0));

    logInfo("idPlayer::idPlayerVolatile: zoomedIn addr: %p", (idPlayerVolatile + 0xD8 + 0x68));
   


    logInfo("idPlayer::idPlayerVolatileUnsaved addr: %p", (idPlayerVolatileUnsaved));
    logInfo("idPlayer::idPlayerVolatileUnsaved: idFocusTracker_Player addr: %p", (idPlayerVolatileUnsaved + 0x2A68));

    logInfo("idEntity:playerController addr: %p", (idplayerCharPtr + 0x310));
    logInfo("idEntity:midnightHandle addr: %p", (idplayerCharPtr + 0x848));


    logInfo("");
    logInfo("***********************   idPlayer Info NEW to confirm  ***********************");

    logInfo("&idplayer->playerConstants: %p", (&idplayer->playerConstants));
    logInfo("&idplayer->playerEditable: %p", (&idplayer->playerEditable));
    logInfo("&idplayer->playerVolatile: %p", (&idplayer->playerVolatile));
    logInfo("&idplayer->playerVolatileUnsaved: %p", (&idplayer->playerVolatileUnsaved));
    logInfo("");

    logInfo("&idplayer->playerVolatile.hudInfo: %p", (&idplayer->playerVolatile.hudInfo));
    logInfo("&idplayer->playerVolatile.hudInfo.weaponAmmoStatus: %p", (&idplayer->playerVolatile.hudInfo.weaponAmmoStatus));
    logInfo("&idplayer->playerVolatile.hudInfo.reticle (idHudReticleInfo): %p", (&idplayer->playerVolatile.hudInfo.reticle));
    logInfo("&idplayer->playerVolatile.hudInfo.healthIndicator: %p", (&idplayer->playerVolatile.hudInfo.healthIndicator));
    logInfo("current maxArmor: %d", (idplayer->playerVolatile.hudInfo.healthIndicator.armorMax));
    logInfo("current armor: %.2f", (idplayer->playerVolatile.hudInfo.healthIndicator.armor));
    logInfo("current maxHealth: %d", (idplayer->playerVolatile.hudInfo.healthIndicator.healthMax));
    logInfo("current health: %.2f", (idplayer->playerVolatile.hudInfo.healthIndicator.health));

    logInfo("&idplayer->playerVolatile.currentMovementMod: %p", (&idplayer->playerVolatile.currentMovementMode));
    logInfo("");

    idEntity* entityPtr = (idEntity*)idplayer;
    logInfo("&entityPtr->playerController->ucmdTracker1: %p", &entityPtr->playerController->ucmdTracker1);
    logInfo("&entityPtr->playerController->ucmdTracker1.usercmd: %p", &entityPtr->playerController->ucmdTracker1.usercmd);
    logInfo("&entityPtr->playerController->ucmdTracker1.usercmd.buttons: %p", &entityPtr->playerController->ucmdTracker1.usercmd.buttons);
    auto buttons = entityPtr->playerController->ucmdTracker1.usercmd.buttons;



}


void Tests::printChangedIdPlayerData() {
    auto idplayer = idGameLocalManager::getIdPlayer();
    if (idplayer != m_lastIdPlayer) {
        m_lastIdPlayer = idplayer;
        logWarn("printChangedIdPlayerData: idPlayer has changed to %p", idplayer);
    }
}


std::string Tests::MovementModeToString(movementMode_t mode) {
    switch (mode) {
    case MOVEMENT_MODE_STANDING:
        return "STANDING";
    case MOVEMENT_MODE_CROUCHED:
        return "CROUCHED";
    case MOVEMENT_MODE_WANDERER:
        return "WANDERER";
    case MOVEMENT_MODE_GROUNDCOMBAT:
        return "GROUNDCOMBAT";
    case MOVEMENT_MODE_CRAWLSPACE:
        return "CRAWLSPACE";
    case MOVEMENT_MODE_ACTIVATION:
        return "ACTIVATION";
    case MOVEMENT_MODE_ACTIVATION_EXIT:
        return "ACTIVATION_EXIT";
    case MOVEMENT_MODE_JUMPING_OVER_STUFF:
        return "JUMPING_OVER_STUFF";
    case MOVEMENT_MODE_PRONE:
        return "PRONE";
    case MOVEMENT_MODE_LADDER:
        return "LADDER";
    case MOVEMENT_MODE_MIDNIGHT_LIMITVIEW_NARROW:
        return "MIDNIGHT_LIMITVIEW_NARROW";
    case MOVEMENT_MODE_MIDNIGHT_LIMITVIEW_WIDE:
        return "MIDNIGHT_LIMITVIEW_WIDE";
    case MOVEMENT_MODE_MIDNIGHT_TAKEDOWN:
        return "MIDNIGHT_TAKEDOWN";
    case MOVEMENT_MODE_WARTABLE:
        return "WARTABLE";
    case MOVEMENT_MODE_MIDNIGHT_KAMPFHUND_CLINCH:
        return "MIDNIGHT_KAMPFHUND_CLINCH";
    case MOVEMENT_MODE_PLAYERCONTROLLED:
        return "PLAYERCONTROLLED";
    case MOVEMENT_MODE_SWIMMING_UNDER_SURFACE:
        return "SWIMMING_UNDER_SURFACE";
    case MOVEMENT_MODE_SPRINT_SLIDE:
        return "SPRINT_SLIDE";
    case MOVEMENT_MODE_WHEELCHAIR:
        return "WHEELCHAIR";
    case MOVEMENT_MODE_WHEELCHAIR_ARMED:
        return "WHEELCHAIR_ARMED";
    case MOVEMENT_MODE_FIRE_EXTINGUISHER:
        return "FIRE_EXTINGUISHER";
    case MOVEMENT_MODE_HEAD_IN_A_JAR:
        return "HEAD_IN_A_JAR";
    case MOVEMENT_MODE_TURRET:
        return "TURRET";
    case MOVEMENT_MODE_PERISCOPE:
        return "PERISCOPE";
    case MOVEMENT_MODE_GROUND_POUND:
        return "GROUND_POUND";
    case MOVEMENT_MODE_LEVER:
        return "LEVER";
    case MOVEMENT_MODE_MIDNIGHT_TAKEDOWN_WHEELCHAIR:
        return "MIDNIGHT_TAKEDOWN_WHEELCHAIR";
    case MOVEMENT_MODE_SWIMMING_ON_SURFACE:
        return "SWIMMING_ON_SURFACE";
    case MOVEMENT_MODE_NUM:
        return "NUM";
    default:
        return "UNKNOWN";
    }
}



void Tests::print_ChangedMovementMode_t() {
    auto idplayer = idGameLocalManager::getIdPlayer();
    if (MemHelper::isBadReadPtr(idplayer)) {
        logErr("PrintIdPlayerInfo: idplayer is bad ptr returning");
        return;
    }
    char* idplayerCharPtr = (char*)idplayer;
    movementMode_t pendingMovementMode = *(movementMode_t*)(idplayerCharPtr + 0x4EE0 + 0x8E0);
    if (pendingMovementMode != m_lastPendingMovementMode) {
        m_lastPendingMovementMode = pendingMovementMode;
        std::string lastPendingMovementModeStr = MovementModeToString(pendingMovementMode);
        logInfo("pendingMovementMode has changed to: %s", lastPendingMovementModeStr.c_str());
    }
    movementMode_t currentMovementMode = *(movementMode_t*)(idplayerCharPtr + 0x4EE0 + 0x8E4);
    if (currentMovementMode != m_lastCurrentMovementMode) {
        m_lastCurrentMovementMode = currentMovementMode;
        std::string currentMovementModeStr = MovementModeToString(currentMovementMode);
        logInfo("currentMovementMode has changed to: %s", currentMovementModeStr.c_str());
    }
}


void Tests::set_all_idDeclProp_HealthComponent_pickupEffect_to_zero() {
    __int64 idDeclProp_HealthComponentlistOffset = 0x3DC6E00;
    __int64 idDeclProp_HealthComponentlistObj = MemHelper::getAddr(idDeclProp_HealthComponentlistOffset);
    if (MemHelper::isBadReadPtr((void*)idDeclProp_HealthComponentlistObj)) {
        return;
    }
    __int64 idMaterialResourceList_IdListPtr = idDeclProp_HealthComponentlistObj + 0x20;
    auto idList_idDeclProp_HealthComponentlist = (idList*)idMaterialResourceList_IdListPtr;

    auto firstidDeclProp_HealthComponentPtr = idList_idDeclProp_HealthComponentlist->list;       
    logInfo("set_all_idDeclProp_HealthComponent_pickupEffect_to_zero: firstidDeclProp_HealthComponentPtr %p", firstidDeclProp_HealthComponentPtr);

    for (size_t i = 0; i < idList_idDeclProp_HealthComponentlist->num; i++)
    {
        auto declPtr = i * 8 + (char*)firstidDeclProp_HealthComponentPtr;
        logInfo("set_all_idDeclProp_HealthComponent_pickupEffect_to_zero: declPtr %p", declPtr);
        if (MemHelper::isBadReadPtr(declPtr)) {
            logErr("set_all_idDeclProp_HealthComponent_pickupEffect_to_zero: declPtr bad ptr: %p", declPtr);
            return;
        }
        __int64 decl = *(__int64*)declPtr;
        logInfo("set_all_idDeclProp_HealthComponent_pickupEffect_to_zero: decl %p", (void*)decl);
        int fxInt = *(int*)(decl + 0xF8);
        logInfo("set_all_idDeclProp_HealthComponent_pickupEffect_to_zero: found fx: %d setting it to 0", fxInt);
        *(int*)(decl + 0xF8) = 0;
    }


}

void Tests::addArgFrom_371DB0_ToVec(__int64 arg)
{
    for (size_t i = 0; i < addArgFrom_371DB0_Vec.size(); i++)
    {
        if (addArgFrom_371DB0_Vec[i] == arg) return;
    }
    addArgFrom_371DB0_Vec.push_back(arg);
}

bool Tests::isPickUpModel(__int64 idRenderModel_Addr) {
    if (MemHelper::isBadReadPtr((void*)idRenderModel_Addr)) {
        return false;
    }
    auto nameAddr = idRenderModel_Addr + 0x48;
    if (MemHelper::isBadReadPtr((void*)nameAddr)) {
        return false;
    }
    if (MemHelper::isBadReadPtr(*(void**)nameAddr)) {
        return false;
    }
    auto name = *(const char**)(nameAddr);
    if (!name) {         
        return false;
    }
    std::string nameStr = name;
    if (nameStr.starts_with("models/pickups/")) {
        return true;
    }
    return false;

}



bool Tests::isRenderModelNameStartsWith(__int64 idRenderModel_Addr, std::string renderModelNameStr) {
    if (MemHelper::isBadReadPtr((void*)idRenderModel_Addr)) {
        return false;
    }
    auto nameAddr = idRenderModel_Addr + 0x48;
    if (MemHelper::isBadReadPtr((void*)nameAddr)) {
        return false;
    }
    if (MemHelper::isBadReadPtr(*(void**)nameAddr)) {
        return false;
    }
    auto name = *(const char**)(nameAddr);
    if (!name) {         
        return false;
    }
    std::string nameStr = name;
    if (nameStr.starts_with(renderModelNameStr.c_str())) {
        return true;
    }
    return false;

}

void Tests::printArgsNamesFrom_371DB0()
{
    logInfo("printArgsNamesFrom_371DB0 vec size: %zu", addArgFrom_371DB0_Vec.size());
    for (size_t i = 0; i < addArgFrom_371DB0_Vec.size(); i++)
    {
        __int64 idRenderModelAddr = addArgFrom_371DB0_Vec[i];
        if (MemHelper::isBadReadPtr((void*)idRenderModelAddr)) {
            logWarn("printArgsNamesFrom_371DB0 found bad ptr....");
        }
        else {
            auto nameAddr = idRenderModelAddr + 0x48;
            if (MemHelper::isBadReadPtr((void*)nameAddr)) {
                logWarn("printArgsNamesFrom_371DB0 nameAddr is bad ptr %p", (void*)nameAddr);
                continue;
            }
            if (MemHelper::isBadReadPtr(*(void**)nameAddr)) {
                logWarn("nameAddr does not point to a valid string pointer. idRenderModelAddr: %p", (void*)idRenderModelAddr);
                continue;
            }
            auto name = *(const char**)(nameAddr);
            if (!name) {         
                logWarn("name is not a valid string");
                continue;
            }
            std::string nameStr = name;

            logInfo("idRenderModelAddr: %p name: %s", (void*)idRenderModelAddr, name);


        }
    }
}
