#pragma once

#include <windows.h>
#include <cstdint>
#include "../MemHelper/MemHelper.h"


class MinHookManager {

private:
    static MH_STATUS m_initializeStatus;
    
    static uintptr_t m_idPLayerSelectWeaponForSelectionGroupAddr;
    static uintptr_t m_isKeyPressedAddr;
    static uintptr_t m_idMenu_UpdateAddr;
    static uintptr_t m_pBindsStrSetAddr;
    static uintptr_t m_setActiveReticleAddr;
    static uintptr_t m_convertIdDeclUIColorToidColorTargetAddr;
    static uintptr_t m_setSpriteInstanceAddr;
    static uintptr_t m_getFovTargetValAddr;
    static uintptr_t m_idHud_Debug_Print_SmthFuncAddr;
    static uintptr_t m_printOutlinedStringMBFuncAddr;

    static uintptr_t m_initRenderModelGuiMbFuncAdd;
    static uintptr_t m_setFontAndPrintStringMBFuncAdd;


public:


    static MH_STATUS getInitializeStatus() {
        return m_initializeStatus;
    }

    static void setInitializeStatus(MH_STATUS status) {
        m_initializeStatus = status;
    }


    static bool setPrintOutlinedStringMBFuncAddr(uintptr_t value) {
        logDebug("setPrintOutlinedStringMBFuncAddr");
        if (MemHelper::isBadReadPtr((void*)value)) {
            return false;
        }
        m_printOutlinedStringMBFuncAddr = value;
        return true;
    }

    static uintptr_t GetPrintOutlinedStringMBFuncAddr() {
        logDebug("GetPrintOutlinedStringMBFuncAddr");
        return m_printOutlinedStringMBFuncAddr;
    }



    static bool setSetFontAndPrintStringMBFuncAdd(uintptr_t value) {
        logDebug("setSetFontAndPrintStringMBFuncAdd");       
        if (MemHelper::isBadReadPtr((void*)value)) {
            return false;
        }
        m_setFontAndPrintStringMBFuncAdd = value;
        return true;
    }

    static uintptr_t GetSetFontAndPrintStringMBFuncAdd() {
        logDebug("GetSetFontAndPrintStringMBFuncAdd");
        return m_setFontAndPrintStringMBFuncAdd;
    }


    static bool setIdHud_Debug_Print_SmthFuncAddr(uintptr_t value) {
        logDebug("setIdHud_Debug_Print_SmthFuncAddr");       
        if (MemHelper::isBadReadPtr((void*)value)) {
            return false;
        }
        m_idHud_Debug_Print_SmthFuncAddr = value;
        return true;
    }

    static uintptr_t GetIdHud_Debug_Print_SmthFuncAddr() {
        logDebug("GetIdHud_Debug_Print_SmthFuncAddr");
        return m_idHud_Debug_Print_SmthFuncAddr;
    }

   
    static uintptr_t getInitRenderModelGuiMbFuncAdd() {
        logDebug("getInitRenderModelGuiMbFuncAdd");
        return m_initRenderModelGuiMbFuncAdd;
    }

    static bool setInitRenderModelGuiMbFuncAdd(uintptr_t value) {
        logDebug("setInitRenderModelGuiMbFuncAdd");       
        if (MemHelper::isBadReadPtr((void*)value)) {
            return false;
        }
        m_initRenderModelGuiMbFuncAdd = value;
        return true;
    }


    static uintptr_t GetIdPlayerSelectWeaponForSelectionGroupAddr() {
        logDebug("GetIdPlayerSelectWeaponForSelectionGroupAddr");
        return m_idPLayerSelectWeaponForSelectionGroupAddr;
    }

    static bool SetIdPlayerSelectWeaponForSelectionGroupAddr(uintptr_t value) {
        logDebug("SetIdPlayerSelectWeaponForSelectionGroupAddr");        
        if (MemHelper::isBadReadPtr((void*)value)) {
            return false;
        }
        m_idPLayerSelectWeaponForSelectionGroupAddr = value;
        return true;
    }

    static uintptr_t GetIsKeyPressedAddr() {
        logDebug("GetIsKeyPressedAddr");
        return m_isKeyPressedAddr;
    }

    static bool SetIsKeyPressedAddr(uintptr_t value) {
        logDebug("SetIsKeyPressedAddr");        
        if (MemHelper::isBadReadPtr((void*)value)) {
            return false;
        }
        m_isKeyPressedAddr = value;
        return true;
    }

    static uintptr_t GetIdMenuUpdateAddr() {
        logDebug("GetIdMenuUpdateAddr");
        return m_idMenu_UpdateAddr;
    }

    static bool SetIdMenuUpdateAddr(uintptr_t value) {
        logDebug("SetIdMenuUpdateAddr");        
        if (MemHelper::isBadReadPtr((void*)value)){
            return false;
        }
        m_idMenu_UpdateAddr = value;
        return true;
    }

    static uintptr_t GetPBindsStrSetAddr() {
        logDebug("GetPBindsStrSetAddr");
        return m_pBindsStrSetAddr;
    }

    static bool SetPBindsStrSetAddr(uintptr_t value) {
        logDebug("SetPBindsStrSetAddr");        
        if (MemHelper::isBadReadPtr((void*)value)) {
            return false;
        }
        m_pBindsStrSetAddr = value;
        return true;
    }

    static uintptr_t GetSetActiveReticleAddr() {
        logDebug("GetSetActiveReticleAddr");
        return m_setActiveReticleAddr;
    }

    static bool SetSetActiveReticleAddr(uintptr_t value) {
        logDebug("SetSetActiveReticleAddr");               
        if (MemHelper::isBadReadPtr((void*)value)) {
            return false;
        }
        m_setActiveReticleAddr = value;
        return true;
    }

    static uintptr_t GetConvertIdDeclUIColorToIdColorTargetAddr() {
        logDebug("GetConvertIdDeclUIColorToIdColorTargetAddr");
        return m_convertIdDeclUIColorToidColorTargetAddr;
    }

    static bool SetConvertIdDeclUIColorToIdColorTargetAddr(uintptr_t value) {
        logDebug("SetConvertIdDeclUIColorToIdColorTargetAddr");        
        if (MemHelper::isBadReadPtr((void*)value)) {
            return false;
        }
        m_convertIdDeclUIColorToidColorTargetAddr = value;
        return true;
    }

    static uintptr_t GetSetSpriteInstanceAddr() {
        logDebug("GetSetSpriteInstanceAddr");
        return m_setSpriteInstanceAddr;
    }

    static bool SetSetSpriteInstanceAddr(uintptr_t value) {
        logDebug("SetSetSpriteInstanceAddr");        
        if (MemHelper::isBadReadPtr((void*)value)) {
            return false;
        }
        m_setSpriteInstanceAddr = value;
        return true;
    }

    static uintptr_t GetGetFovTargetValAddr() {
        logDebug("GetGetFovTargetValAddr");
        return m_getFovTargetValAddr;
    }

    static bool SetGetFovTargetValAddr(uintptr_t value) {
        logDebug("SetGetFovTargetValAddr");        
        if (MemHelper::isBadReadPtr((void*)value)) {
            return false;
        }
        m_getFovTargetValAddr = value;
        return true;
    }

};


MH_STATUS MinHookManager::m_initializeStatus = MH_UNKNOWN;

uintptr_t MinHookManager::m_idPLayerSelectWeaponForSelectionGroupAddr = 0;
uintptr_t MinHookManager::m_isKeyPressedAddr = 0;
uintptr_t MinHookManager::m_idMenu_UpdateAddr = 0;
uintptr_t MinHookManager::m_pBindsStrSetAddr = 0;
uintptr_t MinHookManager::m_setActiveReticleAddr = 0;
uintptr_t MinHookManager::m_convertIdDeclUIColorToidColorTargetAddr = 0;
uintptr_t MinHookManager::m_setSpriteInstanceAddr = 0;
uintptr_t MinHookManager::m_getFovTargetValAddr = 0;
uintptr_t MinHookManager::m_idHud_Debug_Print_SmthFuncAddr = 0;
uintptr_t MinHookManager::m_printOutlinedStringMBFuncAddr = 0;

uintptr_t MinHookManager::m_setFontAndPrintStringMBFuncAdd = 0;
uintptr_t MinHookManager::m_initRenderModelGuiMbFuncAdd = 0;