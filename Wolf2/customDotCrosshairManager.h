#pragma once
#include "idLib.h"
#include "idColor.h"
#include "idCvarManager.h"
#include "../ModSettings/ModSettings.h"
#include "cachedCvarsManager.h"
#include "idEngineLocalManager.h"
#include "../ModSettings/ModSettingsManager.h"
#include "idRenderModelGuiManager.h"




struct CustomDotCrosshair
{
    bool isShown = true;
    idVec4 outlineRect;
    idVec4 fillRect;
    /*idColor idColorOutline = colorBlack;*/   
    idColor defaultIdColorFill = colorWhite; //! from mod settings
    idColor targetIdColorFill = colorRed; //! like turn red if looking at enemy  
    idColor outlineIdColor = colorBlack; 
    idColor currentIdColorFillRef = defaultIdColorFill;
};


class customDotCrosshairManager
{

private:

    static inline bool m_debugLastIsGameActive = false;;

    static inline CustomDotCrosshair m_crosshair;

    static inline int m_cachedScreenWidth = 0;
    static inline int m_cachedScreenHeight = 0;
    
    static inline int m_last_r_mode = -1;
    static inline idPlayerProfileShell_displayMode_t m_lastDisplayMode = DISPLAY_INVALID;

    static inline bool m_wasUserInModSettings = true; //! init to true cause it will trigger at least once whe game starts.



public:

    static bool isGameActive();

    static void updateVisibility(bool isVisible);

    static bool isVisible();
    
    //static void updateAll();

    static void updateFromModSettings();

    static bool isResolutionChanged();

    static void updatePos();

    static void updateColors();

   /* static void updateDefaultFillColor(idColor color);

    static void updateTargetFillColor(idColor color);*/

    static void setColor(bool isdefaultColor);
    

    static CustomDotCrosshair get();

    static void setUserInModSettings();

    static bool wasUserInModSettings();


};

