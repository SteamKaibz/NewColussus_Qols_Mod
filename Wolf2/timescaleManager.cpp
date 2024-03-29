#include "timescaleManager.h"


 const float timescaleManager::m_normalSpeedScaleF = 1.0f;
 const float timescaleManager::m_fastForwardSpeedScaleF = 10.0f;


void timescaleManager::setMaxSpeed()
{
	//logInfo("setMaxSpeed");
	if (cachedCvarsManager::getTimescaleF() != m_fastForwardSpeedScaleF) {
		cachedCvarsManager::setTimescale(m_fastForwardSpeedScaleF);
	}
}

void timescaleManager::setDefaultSpeed()
{
	//logInfo("setDefaultSpeed");
	if (cachedCvarsManager::getTimescaleF() != m_normalSpeedScaleF) {
		cachedCvarsManager::setTimescale(m_normalSpeedScaleF);
	}
	//idCvarManager::setCvar("timescale", "1");
	//logInfo("setDefaultSpeed");
}

bool timescaleManager::isFastForwardTimeScale() {
	//logInfo("isFastForwardTimeScale");
	return cachedCvarsManager::getTimescaleF() == m_fastForwardSpeedScaleF;
 }


