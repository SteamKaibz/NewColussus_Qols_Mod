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

//! cam anim is actually a big deal. Imo this is the reason why Machine game removed the cvar from the base game. If you change it to a low value (meaning no headbob) it will get player stuck in at least one custscene, it will prevent weapon recoil. Those checks prevent those to happen and still let player use close to no headbob is they want.
void cameraManager::updateAnimCamAmount(idPlayer* idPlayerPtr)
{
	static bool isPostFiring = false;

	if (idPlayerPtr){

		movementMode_t movMode = idPlayerPtr->playerVolatile.currentMovementMode;
		idPlayer_animSysEvents_t preMoveEvent = idPlayerPtr->playerVolatile.prevMoveEvent;


		if (preMoveEvent == EVENT_MOVEMENTDIRECTION_IDLE) {
			cachedCvarsManager::setAnimCamAmountProgressive(camAnimDefaultValF);
			//cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF, AnimCamChangeReasonNotMoving);

			Dbg_updateAnimCamAmountCondRef = 1;
		}

		//! this should prevent issue with camera twiching up when player is on coveyerbelt
		else if (movMode == movementMode_t::MOVEMENT_MODE_GROUNDCOMBAT) {
			cachedCvarsManager::setAnimCamAmountProgressive(camAnimDefaultValF);
			//cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF, AnimCamChangeReasonInWheelChair);
			Dbg_updateAnimCamAmountCondRef = 2;
		}

		//! this should mean player is in an ingame cutscene and has to be reset to prevent player getting stuck forever. Could be the same as the condition below (isHudHidden) but because i don't have time to debut/test this atm i'm gonna leave it like this just to be sure.
		else if (movMode == movementMode_t::MOVEMENT_MODE_MIDNIGHT_LIMITVIEW_NARROW) {
			cachedCvarsManager::setAnimCamAmountProgressive(camAnimDefaultValF);
			Dbg_updateAnimCamAmountCondRef = 3;
			//cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF, AnimCamChangeReasonMIDNIGHT_LIMITVIEW_NARROW);
		}

		else if (&idPlayerPtr->playerVolatile.hudInfo && hudManager::isHudHidden(&idPlayerPtr->playerVolatile.hudInfo)) { //! big chance we're in an in game cutscene, let's restore the default cam anim.
			cachedCvarsManager::setAnimCamAmountProgressive(camAnimDefaultValF);
			Dbg_updateAnimCamAmountCondRef = 5;

			//cachedCvarsManager::setAnimCamAmount(camAnimDefaultValF, AnimCamChangeReasonInCutScene);
		}

		//! attempting to fix the annoying extra camera roll speed when leaning left/right after a sprint or a move when camAnim is set close to 0. Update it works !!!!
		else if (idPlayerManager::isLeaning()) {

			cachedCvarsManager::setAnimCamAmountProgressive(camAnimDefaultValF);
			Dbg_updateAnimCamAmountCondRef = 6;
		}


		else {
			cachedCvarsManager::setAnimCamAmountProgressive(ModSettingsManager::getHeadBobAmount());
			//cachedCvarsManager::setAnimCamAmount(ModSettingsManager::getHeadBobAmount(), AnimCamChangeReasonHeadbobVal);

			Dbg_updateAnimCamAmountCondRef = 7;

		}

		


		//! this is not needed anymore: 
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

		
	}
	else {
		Dbg_updateAnimCamAmountCondRef = 8;
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

std::string cameraManager::getAnimCamAmountDbgStrForImgui() {

	return "Dbg_updateAnimCamAmountCondRef: " + std::to_string(Dbg_updateAnimCamAmountCondRef);
}