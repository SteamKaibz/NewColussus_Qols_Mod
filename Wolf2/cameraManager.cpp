#include "cameraManager.h"


 const float cameraManager::camAnimDefaultValF = 1.0f;


//void cameraManager::updateAnimCamAmount()
//{
//	if (hudManager::isHudHiddenAlt()) { //! big chance we're in an in game cutscene, let's restore the default cam anim.
//		cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF);
//	}
//	else {
//		cachedCvarsManager::setAnimCamAmount(ModSettingsManager::getHeadBobAmount());
//	}
//}


//void cameraManager::updateAnimCamAmount_OnTimer(idPlayer* idPlayerPtr, uint64_t updateFreqsMs)
//{
//	static uint64_t lastUpdateMs = 0;
//
//	if (idPlayerPtr && &idPlayerPtr->playerVolatile.hudInfo && (K_Utils::EpochMillis() - lastUpdateMs > updateFreqsMs)) {
//		lastUpdateMs = K_Utils::EpochMillis();
//		//logInfo("debug updateAnimCamAmount_OnTimer: updating...");
//
//		if (hudManager::isHudHidden(&idPlayerPtr->playerVolatile.hudInfo)) { //! big chance we're in an in game cutscene, let's restore the default cam anim.
//			cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF);
//		}
//		else {
//			cachedCvarsManager::setAnimCamAmount(ModSettingsManager::getHeadBobAmount());
//		}
//	}
//
//	
//}

 //todo add the firing check
void cameraManager::updateAnimCamAmount(idPlayer* idPlayerPtr)
{
	static bool isPostFiring = false;

	if (idPlayerPtr){

		if (&idPlayerPtr->playerVolatile.hudInfo && hudManager::isHudHidden(&idPlayerPtr->playerVolatile.hudInfo)) { //! big chance we're in an in game cutscene, let's restore the default cam anim.
			cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF, AnimCamChangeReasonInCutScene);
		}
		//todo we not only need to check the firing state BUT the player moving state as well, otherwise, when we transition from firing to not firing it's a bit jarring as the camera snaps and it is visible.
		else if (weaponStateManager::isCurrentWeaponFiring((char*)idPlayerPtr)) {
			//! making sure recoil cam anim is at it should be whatever headbob setting is
			cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF, AnimCamChangeReasonWeaponFiring);
			isPostFiring = true;
		}	

		else if (isPostFiring) {
			//! decrement AnimCamAmount
			if (cachedCvarsManager::setUserAnimCamAmountProgressive()) {
				isPostFiring = false;
			}
		}

		else {
			cachedCvarsManager::setAnimCamAmount(ModSettingsManager::getHeadBobAmount(), AnimCamChangeReasonHeadbobVal);
		}
	}
}


std::string cameraManager::animCamChangeReasonStr(AnimCamAmountChangeReson value) {
	switch (value) {
	case AnimCamChangeReasonUndefined:
		return "AnimCamChangeReasonUndefined";
	case AnimCamChangeReasonInCutScene:
		return "AnimCamChangeReasonInCutScene";
	case AnimCamChangeReasonWeaponFiring:
		return "AnimCamChangeReasonWeaponFiring";
	case AnimCamChangeReasonHeadbobVal:
		return "AnimCamChangeReasonHeadbobVal";
	default:
		return "Unknown";
	}
}
