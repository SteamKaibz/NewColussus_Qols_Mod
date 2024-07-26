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


void idPlayerManager::handleChange(idPlayer* idPlayerPtr)
{
	if (idPlayerPtr != m_lastIdPlayerPtr) {
		logInfo("handleChange: idPlayer has changed from: %p to: %p", m_lastIdPlayerPtr, idPlayerPtr);
		m_lastIdPlayerPtr = idPlayerPtr;

		timescaleManager::setDefaultSpeed();
	}
}
