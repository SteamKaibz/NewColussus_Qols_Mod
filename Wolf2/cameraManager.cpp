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


 void cameraManager::updateAnimCamAmountV2(idPlayer* idPlayerPtr) {

	 static bool isPostFiring = false;

	 if (idPlayerPtr) {

		 static idPlayer_animSysEvents_t lastPreMoveEvent = EVENT_NUM;

		 movementMode_t movMode = idPlayerPtr->playerVolatile.currentMovementMode;
		 idPlayer_animSysEvents_t preMoveEvent = idPlayerPtr->playerVolatile.prevMoveEvent;


		 if (preMoveEvent == EVENT_MOVEMENTDIRECTION_IDLE) {
			 /*if (lastPreMoveEvent != EVENT_MOVEMENTDIRECTION_IDLE) {

				 cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF);
			 }
			 else {
				 cachedCvarsManager::setAnimCamAmountProgressive(camAnimDefaultValF);
			 }*/

			 cachedCvarsManager::setAnimCamAmountProgressive(camAnimDefaultValF);

			
		 }
		 else {
			 cachedCvarsManager::setAnimCamAmountProgressive(ModSettingsManager::getHeadBobAmount());
		 }

		 lastPreMoveEvent = preMoveEvent;
		
	 }
 }


void cameraManager::updateAnimCamAmount(idPlayer* idPlayerPtr)
{
	static bool isPostFiring = false;

	if (idPlayerPtr){

		movementMode_t movMode = idPlayerPtr->playerVolatile.currentMovementMode;
		idPlayer_animSysEvents_t preMoveEvent = idPlayerPtr->playerVolatile.prevMoveEvent;


		if (preMoveEvent == EVENT_MOVEMENTDIRECTION_IDLE) {
			cachedCvarsManager::setAnimCamAmountProgressive(camAnimDefaultValF);
			//cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF, AnimCamChangeReasonNotMoving);
		}

		//! this should prevent issue with camera twiching up when player is on coveyerbelt
		else if (movMode == movementMode_t::MOVEMENT_MODE_GROUNDCOMBAT) {
			cachedCvarsManager::setAnimCamAmountProgressive(camAnimDefaultValF);
			//cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF, AnimCamChangeReasonInWheelChair);
		}

		//! this should mean player is in an ingame cutscene and has to be reset to prevent player getting stuck forever. Could be the same as the condition below (isHudHidden) but because i don't have time to debut/test this atm i'm gonna leave it like this just to be sure.
		else if (movMode == movementMode_t::MOVEMENT_MODE_MIDNIGHT_LIMITVIEW_NARROW) {
			cachedCvarsManager::setAnimCamAmountProgressive(camAnimDefaultValF);
			//cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF, AnimCamChangeReasonMIDNIGHT_LIMITVIEW_NARROW);
		}

		else if (&idPlayerPtr->playerVolatile.hudInfo && hudManager::isHudHidden(&idPlayerPtr->playerVolatile.hudInfo)) { //! big chance we're in an in game cutscene, let's restore the default cam anim.
			cachedCvarsManager::setAnimCamAmountProgressive(camAnimDefaultValF);
			//cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF, AnimCamChangeReasonInCutScene);
		}

		//else if(idPlayerPtr->playerVolatile.currentMovementMode == movementMode_t)



		//todo we not only need to check the firing state BUT the player moving state as well, otherwise, when we transition from firing to not firing it's a bit jarring as the camera snaps and it is visible.
		//else if (weaponStateManager::isCurrentWeaponFiring((char*)idPlayerPtr)) {
		//	//! making sure recoil cam anim is at it should be whatever headbob setting is
		//	cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF, AnimCamChangeReasonWeaponFiring);
		//	isPostFiring = true;
		//	Dbg_isPostFiring = true;
		//}	

		//else if (isPostFiring) {
		//	//! decrement AnimCamAmount
		//	if (cachedCvarsManager::setUserAnimCamAmountProgressive()) {
		//		isPostFiring = false;
		//		Dbg_isPostFiring = false;
		//	}
		//}

		else {
			cachedCvarsManager::setAnimCamAmountProgressive(ModSettingsManager::getHeadBobAmount());
			//cachedCvarsManager::setAnimCamAmount(ModSettingsManager::getHeadBobAmount(), AnimCamChangeReasonHeadbobVal);
		}
	}
}


std::string cameraManager::animCamChangeReasonStr(AnimCamAmountChangeReson value) {
	switch (value) {
	case AnimCamChangeReasonUndefined:
		return "AnimCamChangeReasonUndefined";
	case AnimCamChangeReasonNotMoving:
		return "AnimCamChangeReasonNotMoving";
	case AnimCamChangeReasonInCutScene:
		return "AnimCamChangeReasonInCutScene";
	case AnimCamChangeReasonWeaponFiring:
		return "AnimCamChangeReasonWeaponFiring";
	case AnimCamChangeReasonInWheelChair:
		return "AnimCamChangeReasonInWheelChair";
	case AnimCamChangeReasonMIDNIGHT_LIMITVIEW_NARROW:
		return "AnimCamChangeReasonMIDNIGHT_LIMITVIEW_NARROW";
	case AnimCamChangeReasonHeadbobVal:
		return "AnimCamChangeReasonHeadbobVal";
	default:
		return "Unknown";
	}
}
