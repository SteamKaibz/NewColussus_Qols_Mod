#pragma once
#include <vector>
#include "ClassDef.h"


class ClassDefContainer {
public:
    static std::vector<ClassDef>& getInstance() {
        static std::vector<ClassDef> classDefsVec;
        static bool isInitialized = false;

        if (!isInitialized) {
          
            classDefsVec.push_back(ClassDef("idResource", { "name", "resourceListPtr", "resourceID"}));


            classDefsVec.push_back(ClassDef("idMaterial", { "ownsMaterialIndex"}));


            classDefsVec.push_back(ClassDef("idSWFSpriteInstance", { "references", "name", "fullPathHash", "alignmentType", "xOffset", "yOffset", "xOriginal", "yOriginal", "bounds"}));

            classDefsVec.push_back(ClassDef("idSWFTextInstance", { "fullPathHash", "parent", "text", "color"}));        
           

            classDefsVec.push_back(ClassDef("idSWF", { "filename", "frameWidth", "frameHeight", "swfScale", "dictionary"}));


            classDefsVec.push_back(ClassDef("idRenderLightParms", { "lightType", "dynamicLightSpecularScale", "target", "start", "end"}));

            classDefsVec.push_back(ClassDef("idRenderLight", { "g"}));

            classDefsVec.push_back(ClassDef("idLight", { "lightColor", "lightIntensity", "lightMaterial", "lightType", "spotLight", "startOff", "renderLight", "originalColor"}));


            classDefsVec.push_back(ClassDef("idDeclWeaponReticle", { "reticleModelScale" }));

            classDefsVec.push_back(ClassDef("idDeclWeapon::zoomInfo_t", { "zoomedFOV", "sensitivity_scale_mouse", "sensitivity_scale_controller"}));

            classDefsVec.push_back(ClassDef("idDeclWeapon", { "ironSightZoom", "sensitivityWhileFiring"}));


            classDefsVec.push_back(ClassDef("idCrosshairInfo", { "infoFlags" }));


            classDefsVec.push_back(ClassDef("idFocusTracker", { "focusUsableEntityPtr", "focusedEntityFlags", "crosshairInfo" }));

           
            classDefsVec.push_back(ClassDef("idHudReticleInfo", { "decl", "weaponDecl", "targetIndication"}));

            classDefsVec.push_back(ClassDef("idHudWeaponAmmoStatusInfo", { "info"}));

            classDefsVec.push_back(ClassDef("idHudInfo", {"inScope", "isZooming", "weaponAmmoStatus", "reticle", "healthIndicator", "hudFlags"}));
            

            classDefsVec.push_back(ClassDef("idMenuWidget_Hud_Main", { "interaction", "interact_follower", "healthAndArmor", "reticleManager", "ammoGroup", "challengeHud"}));

            classDefsVec.push_back(ClassDef("idMenuScreen_Hud_MercuryMain", { "mainHud", "mainHudInfo"}));

            classDefsVec.push_back(ClassDef("idMenuManager_Hud_MercuryHud", { "hudScreen"}));

            classDefsVec.push_back(ClassDef("idPlayerHud_Render", { "mercMgr", "playerHUDFont", "floatingNumberOverlay"}));

            classDefsVec.push_back(ClassDef("localView_t", { "hudRender"}));

         
            classDefsVec.push_back(ClassDef("idPlayer::idPlayerConstant", { "screenFXDecl" }));

            classDefsVec.push_back(ClassDef("idPlayer::idPlayerEditable", { "playerType"}));

            classDefsVec.push_back(ClassDef("idPlayer::idPlayerVolatile", { "headlightIsActive", "currentMovementMode", "showMarkerHintFadeOutTime", "playerUseTime", "playerUseState", "hudInfo", "localView" }));

            classDefsVec.push_back(ClassDef("idPlayer::idPlayerVolatileUnsaved", { "headLightptr", "focusTracker", "pauseScreenIndex", "playerProgress", "screenFX"}));

            classDefsVec.push_back(ClassDef("idPlayer", { "playerConstants", "playerEditable", "playerVolatile", "playerVolatileUnsaved" }));
           
            classDefsVec.push_back(ClassDef("usercmd_t", { "buttons" }));

            classDefsVec.push_back(ClassDef("idUCmdTracker", { "prevcmd", "usercmd", "prevcmdRaw", "usercmdRaw" }));
            classDefsVec.push_back(ClassDef("idPlayerController", { "useCmdTracker1", "ucmdTracker1", "ucmdTracker2", "rawUCmdTracker" }));

            classDefsVec.push_back(ClassDef("idEntity", { "playerController" }));
           
                 
           

            isInitialized = true;    
        }

        return classDefsVec;
    }
};
