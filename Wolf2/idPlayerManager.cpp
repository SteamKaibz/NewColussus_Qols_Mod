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
		 idCvarManager::setCvar("com_adaptiveTick", "0");
		 logInfo("triggerHighFramerateMvtFix, setting com_adaptiveTick to 0...");
		 last_com_adaptiveTickCmdSetMs = K_Utils::EpochMillis();
	 }
 }

 void idPlayerManager::checkForHighFramerateMvtFixTimerEnd()
 {
	 if (K_Utils::EpochMillis() - last_com_adaptiveTickCmdSetMs > 200) {
		 bool isAdaptiveTick = (bool)idCvarManager::getCvarInt("com_adaptiveTick");
		 if (!isAdaptiveTick) {
			 idCvarManager::setCvar("com_adaptiveTick", "1");
			 logInfo("checkForHighFramerateMvtFixTimerEnd: setting com_adaptiveTick back to 1...");
		 }
	 }
 }


void idPlayerManager::handleChange(idPlayer* idPlayerPtr)
{
	if (idPlayerPtr != m_lastIdPlayerPtr) {
		logInfo("handleChange: idPlayer has changed from: %p to: %p", m_lastIdPlayerPtr, idPlayerPtr);
		m_lastIdPlayerPtr = idPlayerPtr;

		timescaleManager::setDefaultSpeed();
	}
}
