#include "timescaleManager.h"


 //const float timescaleManager::m_normalSpeedScaleF = 1.0f;
 //const float timescaleManager::m_fastForwardSpeedScaleF = 10.0f;


 void timescaleManager::increaseSpeed() {
	 if (m_currentSpeedIndex < m_timeScaleValues.size() - 1) {
		 m_currentSpeedIndex++;
	 }
	 updateSpeed();
 }


 void timescaleManager::resetSpeed() {
	 m_currentSpeedIndex = m_defaultSpeedIndex;
	 updateSpeed();
 }


 size_t timescaleManager::getCurrentSpeedIndex() {
	 return m_currentSpeedIndex;
 }

 float timescaleManager::getCurrentTimeScaleValF() {
	 return cachedCvarsManager::getTimescaleF();
 }



 void timescaleManager::updateSpeed() {
	 if (cachedCvarsManager::getTimescaleF() != m_timeScaleValues[m_currentSpeedIndex]) {
		 logInfo("updateSpeed: updating timescale to %.3f", m_timeScaleValues[m_currentSpeedIndex]);
		 idCmdManager::setTimeScale(m_timeScaleValues[m_currentSpeedIndex]);
	 }
 }

 bool timescaleManager::isFastForwardTimeScale() {
	 //logInfo("isFastForwardTimeScale");
	 return cachedCvarsManager::getTimescaleF() > m_timeScaleValues[m_defaultSpeedIndex];
 }

//void timescaleManager::setMaxSpeed()
//{
//	//logInfo("setMaxSpeed");
//	if (cachedCvarsManager::getTimescaleF() != m_fastForwardSpeedScaleF) {
//		cachedCvarsManager::setTimescale(m_fastForwardSpeedScaleF);
//	}
//}

//void timescaleManager::setDefaultSpeed()
//{
//	//logInfo("setDefaultSpeed");
//	if (cachedCvarsManager::getTimescaleF() != m_normalSpeedScaleF) {
//		cachedCvarsManager::setTimescale(m_normalSpeedScaleF);
//	}
//	//idCvarManager::setCvar("timescale", "1");
//	//logInfo("setDefaultSpeed");
//}




