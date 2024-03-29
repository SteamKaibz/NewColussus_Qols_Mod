#pragma once
#include "idLib.h"
#include "idColor.h"
#include "idCvarManager.h"
#include "../ModSettings/ModSettings.h"
#include "cachedCvarsManager.h"
#include "idEngineLocalManager.h"
#include "../ModSettings/ModSettingsManager.h"





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

    static bool m_debugLastIsGameActive;

    static CustomDotCrosshair m_crosshair;

    static int m_cachedScreenWidth;
    static int m_cachedScreenHeight;

    static bool m_wasUserInModSettings;


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

