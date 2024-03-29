#include "cachedCvarsManager.h"

idCVar* cachedCvarsManager::m_windowWidthCached = nullptr;
idCVar* cachedCvarsManager::m_windowHeightCached = nullptr;
idCVar* cachedCvarsManager::m_win_hasFocusCached = nullptr;
idCVar* cachedCvarsManager::m_swf_safeFrameCached = nullptr;
idCVar* cachedCvarsManager::m_swf_timescaleCached = nullptr;
idCVar* cachedCvarsManager::m_swf_skipRenderText = nullptr;
idCVar* cachedCvarsManager::m_pm_animCamAmount = nullptr;
idCVar* cachedCvarsManager::m_sensitivity = nullptr;

 const float cachedCvarsManager::m_safeFrameValueMax = 0.93f;
 const float cachedCvarsManager::m_swf_safeFrameDefaultVal = 0.025f;


//idCVar* cachedCvarsManager::m_gFovCached = nullptr;
//idCVar* cachedCvarsManager::m_showDevMenuCached = nullptr;
//idCVar* cachedCvarsManager::m_unlockMouseInMenusCached = nullptr;
//idCVar* cachedCvarsManager::m_win_pauseOnAltTabCached = nullptr;
//idCVar* cachedCvarsManager::m_testMaterialCached = nullptr;
//idCVar* cachedCvarsManager::m_setTimeScaleCached = nullptr;
//idCVar* cachedCvarsManager::m_showWorldMarkersCached = nullptr;




bool cachedCvarsManager::cacheCriticalCvars()
{

	m_windowWidthCached = (idCVar*)idCvarManager::getCvarPtr("r_windowWidth");
	if (MemHelper::isBadReadPtr(m_windowWidthCached)) {
		logErr("acquireCvarsPtrs: failed to find r_windowWidth");
		return false;
	}

	m_windowHeightCached = (idCVar*)idCvarManager::getCvarPtr("r_windowHeight");
	if (MemHelper::isBadReadPtr(m_windowHeightCached)) {
		logErr("acquireCvarsPtrs: failed to find r_windowWidth");
		return false;
	}


	m_win_hasFocusCached = (idCVar*)idCvarManager::getCvarPtr("win_hasFocus");	
	if (MemHelper::isBadReadPtr(m_win_hasFocusCached)) {
		logErr("acquireCvarsPtrs: failed to find win_hasFocus");
		return false;
	}

	m_swf_safeFrameCached = (idCVar*)idCvarManager::getCvarPtr("swf_safeFrame");
	if (MemHelper::isBadReadPtr(m_swf_safeFrameCached)) {
		logErr("acquireCvarsPtrs: failed to find swf_safeFrame");
		return false;
	}

	m_swf_timescaleCached = (idCVar*)idCvarManager::getCvarPtr("timescale"); 
	if (MemHelper::isBadReadPtr(m_swf_timescaleCached)) {
		logErr("acquireCvarsPtrs: failed to find timescale");
		return false;
	}

	m_swf_skipRenderText = (idCVar*)idCvarManager::getCvarPtr("swf_skipRenderText");
	if (MemHelper::isBadReadPtr(m_swf_skipRenderText)) {
		logErr("acquireCvarsPtrs: failed to find swf_skipRenderText");
		return false;
	}
	
	m_pm_animCamAmount = (idCVar*)idCvarManager::getCvarPtr("pm_animCamAmount");
	if (MemHelper::isBadReadPtr(m_pm_animCamAmount)) {
		logErr("acquireCvarsPtrs: failed to find pm_animCamAmount");
		return false;
	}

	m_sensitivity = (idCVar*)idCvarManager::getCvarPtr("m_sensitivity");
	if (MemHelper::isBadReadPtr(m_sensitivity)) {
		logErr("acquireCvarsPtrs: failed to find m_sensitivity");
		return false;
	}
	/*else {
		logInfo("cacheCriticalCvars: debug: m_sensitivity cvar: %p", m_sensitivity);
	}*/

	/*m_showDevMenuCached = (idCVar*)idCvarManager::getCvarPtr("menu_showOptionForDevMenu");
	if (MemHelper::isBadReadPtr(m_showDevMenuCached)) {
		logErr("acquireCvarsPtrs: failed to find menu_showOptionForDevMenu");
		return false;
	}*/


	return true;
}

int cachedCvarsManager::get_WindowWidthInt() {	
	if (m_windowWidthCached) {
		return m_windowWidthCached->valueInteger;		
	}
	logErr("get_WindowWidthInt: cached cvar is null, mod should not be running, how could that happen???");
	return 0;
}


int cachedCvarsManager::get_WindowHeightInt() {
	if (m_windowHeightCached) {
		return m_windowHeightCached->valueInteger;
	}
	logErr("get_WindowWidthInt: cached cvar is null, mod should not be running, how could that happen???");
	return 0;
}


bool cachedCvarsManager::isWindowFocused() {
	if (m_win_hasFocusCached) {
		return (bool)m_win_hasFocusCached->valueInteger;
	}
	logErr("isWindowFocused: cached cvar is null, mod should not be running, how could that happen???");
	return false;
}


void cachedCvarsManager::debugLogWin_hasFocusCvar() {
	logInfo("debugLogWin_hasFocusCvar: %p", (void*)m_win_hasFocusCached);

}

float cachedCvarsManager::getMouseSens() {
	if (m_sensitivity) {
		return m_sensitivity->valueFloat;
	}
	logErr("getMouseSens: cached cvar is null, mod should not be running, how could that happen???");
	return -1.0f;
}

void cachedCvarsManager::setMouseSens(float sens) {
	if (m_sensitivity) {
		m_sensitivity->valueFloat = sens;
		return;
	}
	logErr("setMouseSens: cached cvar is null, mod should not be running, how could that happen???");
	
}



void cachedCvarsManager::setSafeFrame(float safeFrameFloat) {
	if (m_swf_safeFrameCached) {
		if (m_swf_safeFrameCached->valueMax != m_safeFrameValueMax) {
			m_swf_safeFrameCached->valueMax = m_safeFrameValueMax;
		}
		if (m_swf_safeFrameCached->valueFloat != safeFrameFloat) {
			m_swf_safeFrameCached->valueFloat = safeFrameFloat;
			logInfo("setSafeFrame: m_swf_safeFrameCached->valueFloat is being changed to: %.2f", m_swf_safeFrameCached->valueFloat);
		}		
		return;
	}
	logErr("setSafeFrame: failed to find cvar");
}


void cachedCvarsManager::setSafeFrameToDefault() {
	if (m_swf_safeFrameCached) {
		
		if (m_swf_safeFrameCached->valueFloat != m_swf_safeFrameDefaultVal) {
			m_swf_safeFrameCached->valueFloat = m_swf_safeFrameDefaultVal;
		}
		return;
	}
	logErr("setSafeFrameToDefault: failed to find cvar");
}



void cachedCvarsManager::setTimescale(float timeScaleF) {
	if (m_swf_timescaleCached) {		
		if (m_swf_timescaleCached->valueFloat != timeScaleF) {
			logInfo("setTimescale: changing timescale from: %.2f to %.2f", m_swf_timescaleCached->valueFloat, timeScaleF);
			m_swf_timescaleCached->valueFloat = timeScaleF;
		}
		return;
	}
	logErr("setTimescale: failed to find cvar");
}


float cachedCvarsManager::getTimescaleF() {
	if (m_swf_timescaleCached) {
		return m_swf_timescaleCached->valueFloat;		
	}
	logErr("setTimescale: failed to find cvar returning 0.0");
	return 0.0f;
}

void cachedCvarsManager::skipRenderText(bool isSkipRenderText) {
	if (m_swf_skipRenderText) {
		m_swf_skipRenderText->valueInteger = (int)isSkipRenderText;
		return;
	}
	logErr("skipRenderText: failed to find cvar, this is bad !");	
}


void cachedCvarsManager::setAnimCamAmount(float animCamAmountF, AnimCamAmountChangeReson changeReason) {
	if (m_pm_animCamAmount) {
		if (m_pm_animCamAmount->valueFloat != animCamAmountF) {
			std::string reasonStr = cameraManager::animCamChangeReasonStr(changeReason);
			logInfo("setAnimCamAmount: changing m_pm_animCamAmount from: %.2f to %.2f because: %s", m_pm_animCamAmount->valueFloat, animCamAmountF, reasonStr.c_str());
			m_pm_animCamAmount->valueFloat = animCamAmountF;
		}
		return;
	}
	logErr("setAnimCamAmount: failed to find cvar");
}

bool cachedCvarsManager::setUserAnimCamAmountProgressive()
{
	if (m_pm_animCamAmount) {
		if (m_pm_animCamAmount->valueFloat > ModSettingsManager::getHeadBobAmount()) {
			//logInfo("setUserAnimCamAmountProgressive:  animCamAmount float current val: %.3f decrementing it by %.3f", m_pm_animCamAmount->valueFloat, m_headbobResetIncrements);
			m_pm_animCamAmount->valueFloat -= m_headbobResetIncrements;
			if (m_pm_animCamAmount->valueFloat < 0) {
				m_pm_animCamAmount->valueFloat = 0;
				logErr("setUserAnimCamAmountProgressive: m_pm_animCamAmount->valueFloat was being set to negative...something is wrong...");
			}
			return false;
		}
		else if(m_pm_animCamAmount->valueFloat < ModSettingsManager::getHeadBobAmount()) {
			logInfo("setUserAnimCamAmountProgressive: overshoot, setting m_pm_animCamAmount->valueFloat to ModSettingsManager::getHeadBobAmount(): %.3f", ModSettingsManager::getHeadBobAmount());
			m_pm_animCamAmount->valueFloat = ModSettingsManager::getHeadBobAmount();			
		}
		else {
			logInfo("setUserAnimCamAmountProgressive: done setting m_pm_animCamAmount->valueFloat to ModSettingsManager::getHeadBobAmount(): %.3f", ModSettingsManager::getHeadBobAmount());
		}
		return true; //! here m_pm_animCamAmount->valueFloat has to be == ModSettingsManager::getHeadBobAmount();
	}
	logErr("setUserAnimCamAmountProgressive: failed to find cvar");
	return true; //! returning true here even if in theory mod should not be running anyway 
}


//bool cachedCvarsManager::isFastForwardTimeScale() {
//	if (m_swf_timescaleCached) {
//		return false;
//	}
//	return m_swf_timescaleCached->valueFloat == 
//
//}
//float cachedCvarsManager::get_Fov() {
//	if (m_gFovCached) {
//		return m_gFovCached->valueFloat;
//	}
//	logErr("get_Fov: cached cvar is null, mod should not be running, how could that happen???");
//	return 0.0f;
//}
//
//void cachedCvarsManager::setShowOptionForDevMenu(bool isOn) {
//	if (m_showDevMenuCached) {
//		if (isOn) {
//			idCvarManager::setCvarFast(m_showDevMenuCached, "1");
//		}
//		else {
//			idCvarManager::setCvarFast(m_showDevMenuCached, "0");
//		}
//	}
//	else {
//		logErr("setShowOptionForDevMenu: cached cvar is null, mod should not be running, how could that happen???");
//	}
//}
//
//void cachedCvarsManager::setUnlockMouseInMenu(bool isTrue) {
//	if (m_unlockMouseInMenusCached) {
//		if (isTrue) {
//			idCvarManager::setCvarFast(m_unlockMouseInMenusCached, "1");
//		}
//		else {
//			idCvarManager::setCvarFast(m_unlockMouseInMenusCached, "0");
//		}
//	}
//	else {
//		logErr("setUnlockMouseInMenu: cached cvar is null, mod should not be running, how could that happen???");
//	}
//}
//
//void cachedCvarsManager::setPauseGameOnAltTab(bool isTrue) {
//	if (m_win_pauseOnAltTabCached) {
//		if (isTrue) {
//			idCvarManager::setCvarFast(m_win_pauseOnAltTabCached, "1");
//		}
//		else {
//			idCvarManager::setCvarFast(m_win_pauseOnAltTabCached, "0");
//		}
//	}
//	else {
//		logErr("setPauseGameOnAltTab: cached cvar is null, mod should not be running, how could that happen???");
//	}
//}
//
//void cachedCvarsManager::testMaterial(const char* matrName) {
//	if (m_testMaterialCached) {
//		idCvarManager::setCvarFast(m_testMaterialCached, matrName);		
//	}
//	else {
//		logErr("testMaterial: cached cvar is null, mod should not be running, how could that happen???");
//	}
//}
//
//void cachedCvarsManager::setTimeScale(const char* scaleStr) {
//	if (m_setTimeScaleCached) {
//		idCvarManager::setCvarFast(m_setTimeScaleCached, scaleStr);
//	}
//	else {
//		logErr("setTimeScale: cached cvar is null, mod should not be running, how could that happen???");
//	}
//}


//void cachedCvarsManager::showWorldMarkers(bool isTrue) {
//	if (m_showWorldMarkersCached) {
//		idCvarManager::setCvarFast(m_setTimeScaleCached, scaleStr);
//	}
//	else {
//		logErr("setTimeScale: cached cvar is null, mod should not be running, how could that happen???");
//	}
//}

//m_showWorldMarkersCached