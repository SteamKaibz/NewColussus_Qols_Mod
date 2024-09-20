#include "customDotCrosshairManager.h"






void customDotCrosshairManager::setUserInModSettings() {
    m_wasUserInModSettings = true;
}


bool customDotCrosshairManager::wasUserInModSettings() {
    if (m_wasUserInModSettings) {
        m_wasUserInModSettings = false;
        return true;
    }
    return false;
}


//bool customDotCrosshairManager::isGameActive()
//{
//    __int64 idRenderSystemLocal = idEngineLocalManager::idRenderSystemLocal();
//    if (idRenderSystemLocal) {
//        bool isActive = *(bool*)(idRenderSystemLocal + 0x1D0);
//        if (isActive != m_debugLastIsGameActive) {
//            m_debugLastIsGameActive = isActive;
//            if (isActive) {
//                logInfo("isGameActive: game is now Active");
//            }
//            else {
//                logInfo("isGameActive: game is now PAUSED");
//            }
//        }
//        return isActive;
//    }
//    return false;
//}

void customDotCrosshairManager::updateVisibility(bool isVisible)
{
    m_crosshair.isShown = isVisible;
}

bool customDotCrosshairManager::isVisible()
{
    return m_crosshair.isShown;
}

//void customDotCrosshairManager::updateAll()
//{
//    updatePos();
//    updateColors();
//    //updateDefaultFillColor(ModSettings::getCrosshairFillIdColor());
//}


void customDotCrosshairManager::updateFromModSettings() {
    updatePos();
    updateColors();
}


bool customDotCrosshairManager::isResolutionChanged()
{
    if (cachedCvarsManager::get_r_mode() != m_last_r_mode || cachedCvarsManager::getDisplayMode() != m_lastDisplayMode) {

        logInfo("Resolution has changed: %s", idRenderModelGuiManager::getDisplayDbgInfoStr().c_str());

        m_last_r_mode = cachedCvarsManager::get_r_mode();
        m_lastDisplayMode = cachedCvarsManager::getDisplayMode();

        return true;
    }

  /*  if ((cachedCvarsManager::get_WindowWidthInt() != m_cachedScreenWidth) || (cachedCvarsManager::get_WindowHeightInt() != m_cachedScreenHeight)) {
        m_cachedScreenWidth = cachedCvarsManager::get_WindowWidthInt();
        m_cachedScreenHeight = cachedCvarsManager::get_WindowHeightInt();
        logInfo("isResolutionChanged: resolution has changed, width: %.d heigth: %.d", m_cachedScreenWidth, m_cachedScreenHeight);
        return true;
    }*/
    return false;    
}




void customDotCrosshairManager::updatePos()
{
    logInfo("updating custom crosshair Pos");

    const ModSettings& modSettings = ModSettingsManager::get();

    //! size and outline must always be even values.
    int size = modSettings.customCrosshairSize;
    int outlineThickness = modSettings.customCrosshairOutlineThickness;

    auto centerX = cachedCvarsManager::get_WindowWidthInt() / 2;
    auto centerY = cachedCvarsManager::get_WindowHeightInt() / 2;

    //? might need a check if those value are <1 ?

    m_crosshair.fillRect.x = (float) (centerX - (size / 2));
    m_crosshair.fillRect.y = (float) (centerY - (size / 2));
    m_crosshair.fillRect.w = (float) size;
    m_crosshair.fillRect.h = (float) size;

    m_crosshair.outlineRect.x = (float) (m_crosshair.fillRect.x - outlineThickness);
    m_crosshair.outlineRect.y = (float) (m_crosshair.fillRect.y - outlineThickness);
    m_crosshair.outlineRect.w = (float) (size + 2 * outlineThickness);
    m_crosshair.outlineRect.h = (float) (size + 2 * outlineThickness);

}


void customDotCrosshairManager::updateColors() {

    const ModSettings& modSettings = ModSettingsManager::get();

    m_crosshair.defaultIdColorFill.r = modSettings.customCrosshairColor.x;
    m_crosshair.defaultIdColorFill.g = modSettings.customCrosshairColor.y;
    m_crosshair.defaultIdColorFill.b = modSettings.customCrosshairColor.z;
    m_crosshair.defaultIdColorFill.a = modSettings.customCrosshairColor.w;

    m_crosshair.targetIdColorFill.r = modSettings.customCrosshairTargetColor.x;
    m_crosshair.targetIdColorFill.g = modSettings.customCrosshairTargetColor.y;
    m_crosshair.targetIdColorFill.b = modSettings.customCrosshairTargetColor.z;
    m_crosshair.targetIdColorFill.a = modSettings.customCrosshairTargetColor.w; 

    m_crosshair.outlineIdColor.r = modSettings.customCrosshairOutlineColor.x;
    m_crosshair.outlineIdColor.g = modSettings.customCrosshairOutlineColor.y;
    m_crosshair.outlineIdColor.b = modSettings.customCrosshairOutlineColor.z;
    m_crosshair.outlineIdColor.a = modSettings.customCrosshairOutlineColor.w;               

}

//void customDotCrosshairManager::updateDefaultFillColor(idColor color)
//{
//    m_crosshair.defaultIdColorFill = color;
//}
//
//void customDotCrosshairManager::updateTargetFillColor(idColor color) {
//
//    m_crosshair.targetIdColorFill = color;
//}

void customDotCrosshairManager::setColor(bool isdefaultColor) {
    if (isdefaultColor) {
        m_crosshair.currentIdColorFillRef = m_crosshair.defaultIdColorFill;
    }
    else {
        m_crosshair.currentIdColorFillRef = m_crosshair.targetIdColorFill;
    }
}

CustomDotCrosshair customDotCrosshairManager::get()
{
    return m_crosshair;
}
