#include "idPlayerManager.h"

 idPlayer* idPlayerManager::m_lastIdPlayerPtr;




 idHudInfo* idPlayerManager::getIdHudInfo() {
	 idPlayer* idplayerPtr = idGameLocalManager::getIdPlayer();
	 if (idplayerPtr) {
		 return &idplayerPtr->playerVolatile.hudInfo;
	 }
	 return nullptr;
 }

 idPlayer_animSysEvents_t idPlayerManager::getPreMoveEvent() {

	 idPlayer* idplayerPtr = idGameLocalManager::getIdPlayer();
	 if (idplayerPtr) {
		 return idplayerPtr->playerVolatile.prevMoveEvent;
	 }

	 logWarn("idPlayerManager::getPreMoveEvent(): failed to get event");
	 return EVENT_NUM;
 }


 void idPlayerManager::triggerHighFramerateMvtFix()
 {
	 bool isAdaptiveTick = (bool)idCvarManager::getCvarInt("com_adaptiveTick");
	 if (isAdaptiveTick) {
		 idCmdManager::executeCmd("com_adaptiveTick 0");
		 logInfo("triggerHighFramerateMvtFix, setting com_adaptiveTick to 0...");
		 last_com_adaptiveTickCmdSetMs = K_Utils::EpochMillis();
	 }
 }

 void idPlayerManager::checkForHighFramerateMvtFixTimerEnd()
 {
	 if (K_Utils::EpochMillis() - last_com_adaptiveTickCmdSetMs > 200) {
		 bool isAdaptiveTick = (bool)idCvarManager::getCvarInt("com_adaptiveTick");
		 if (!isAdaptiveTick) {
			 idCmdManager::executeCmd("com_adaptiveTick 1");
			 logInfo("checkForHighFramerateMvtFixTimerEnd: setting com_adaptiveTick back to 1...");
		 }
	 }
 }


void idPlayerManager::handleChange(idPlayer* idPlayerPtr)
{
	if (idPlayerPtr != m_lastIdPlayerPtr) {
		logInfo("handleChange: idPlayer has changed from: %p to: %p", m_lastIdPlayerPtr, idPlayerPtr);
		m_lastIdPlayerPtr = idPlayerPtr;

		timescaleManager::resetSpeed();
	}
}

//x magick offset yeah but i'm tired....
bool idPlayerManager::isLeaning()
{
	idPlayer* idplayerPtr = idGameLocalManager::getIdPlayer();
	if (idplayerPtr) {	
		//int leanVal = *(int*)((char*)idplayerPtr + 0x1131C);
		return idplayerPtr->playerVolatile.environmentAnalyzer.forceLeanMode != 0;
	}
	logWarn("isLeaning: failed to get idPlayer, returning false");
	return false;	
}


//! meaning does it have weapons in BOTH hands whether both weapons are different types or not.
bool idPlayerManager::isDualWielding() {

	//! no, it is too cumbersome....as you would soon need big structs/class so not good.
	//x 18/9/24 testing to see if the typeInfo manager at runtime to get offsets is manageable and not too cumbersome. if it's ok we should implement it everywhere...meaning lots of work...

	idPlayer* idplayerPtr = idGameLocalManager::getIdPlayer();
	if (idplayerPtr) {
		
		idActor* idActorPtr = (idActor*)idplayerPtr;
		//! we check left hand because if player has 1 weapon it will be in his right hand.
		idManagedClassPtrBase* managedClasPtr =  (idManagedClassPtrBase*) ((__int64)&idActorPtr->actorVolatile.equipped + equipSlot_t::EQUIP_LEFT_HAND * sizeof(idManagedClassPtrBase));
		if (managedClasPtr && managedClasPtr->ptr) {
			return true;
		}	

		//logInfo("isDualWielding: dbg: managedClasPtr: %p managedClasPtr->ptr: %p", managedClasPtr, managedClasPtr->ptr);
		/*if (managedClasPtr->ptr) {
			logInfo("isDualWielding: dbg: player is dual wielding");
		}
		else {
			logInfo("isDualWielding: dbg: player is NOT dual wielding !!!!!");
		}*/	

	}
	
	return false;
}

//! version to be used in a hook
bool idPlayerManager::isDualWielding(idPlayer* idplayerPtr) {	

	if (idplayerPtr) {
		idActor* idActorPtr = (idActor*)idplayerPtr;
		//! we check left hand because if player has 1 weapon it will be in his right hand.
		idManagedClassPtrBase* managedClasPtr = (idManagedClassPtrBase*)((__int64)&idActorPtr->actorVolatile.equipped + equipSlot_t::EQUIP_LEFT_HAND * sizeof(idManagedClassPtrBase));
		if (managedClasPtr && managedClasPtr->ptr) {
			return true;
		}
	}

	return false;
}


bool idPlayerManager::isInScope() {
	idPlayer* idplayerPtr = idGameLocalManager::getIdPlayer();
	if (idplayerPtr) {
		return idplayerPtr->playerVolatile.hudInfo.inScope;
	}

	return false;
}



std::string idPlayerManager::getAnimSysEventsDgbStrForImgui() {

	idPlayer_animSysEvents_t preMovEvent = getPreMoveEvent();
	std::string enumValStr = TypeInfoManager::getEnumMemberName("idPlayer::animSysEvents_t", (long long)preMovEvent);
	return "PreMoveEvent: " + enumValStr;
}


void idPlayerManager::Dbg_LogPreMoveAdd() {

	idPlayer* idplayerPtr = idGameLocalManager::getIdPlayer();
	if (idplayerPtr) {
		logInfo("Dbg_LogPreMoveAdd: &idplayerPtr->playerVolatile.prevMoveEvent: %p", &idplayerPtr->playerVolatile.prevMoveEvent);
		return;
	}

	logWarn("Dbg_LogPreMoveAdd failed to get addr");
	
}