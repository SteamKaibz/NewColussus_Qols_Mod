#include "ADS_Manager.h"

__int64 ADS_Manager::m_zoomBtnReleaseCheckAddr = 0;
bool ADS_Manager::m_isToggleFlag = false;
bool ADS_Manager::m_isZoomInTrigger = false;
bool ADS_Manager::m_isZoomBtnReleasedFlag = false;
AdsZoomCheckInstructionState ADS_Manager::m_zoomInstructionState = zoomCodeOriginal;


bool ADS_Manager::acquireZoomBtnReleaseInsctructionAddr(__int64 instructAddr) {
	if (MemHelper::isBadReadPtr((void*)instructAddr)) {
		logErr("acquireZoomBtnReleaseInsctructionAddr: failed to acquirre zoomBtnReleaseCheckAddr: %p", (void*)instructAddr);
		return false;
	}
	m_zoomBtnReleaseCheckAddr = instructAddr;
	logInfo("acquireZoomBtnReleaseInsctructionAddr: succes acquiring m_zoomBtnReleaseCheckAddr: %p", (void*)m_zoomBtnReleaseCheckAddr);
	return true;
}


//void acquireZoomKeyVkCode(unsigned int vkCode) {
//
//}

void ADS_Manager::checkZoomBtnState() {
	//static bool isZoomBtnReleasedFlag = false;

	
	//! is btn pressed
	//if ((GetAsyncKeyState(VK_RBUTTON) & 0x8001)) { 
	if ((GetAsyncKeyState(ModSettingsManager::getZoomKeyVkCode()) & 0x8001)) {
		if (m_isZoomBtnReleasedFlag) {
			ADS_Manager::raiseToggleFlag();
			m_isZoomBtnReleasedFlag = false;
		}
	}

	else { //! if btn released
		m_isZoomBtnReleasedFlag = true;
	}
}

void ADS_Manager::reset() {
	m_isZoomInTrigger = false;
	//restoreZoomBtnReleaseCheck();
}

//! triggered by key press in mod main loop
void ADS_Manager::raiseToggleFlag() {
	m_isToggleFlag = true;
}

bool ADS_Manager::isToggleFlag() {
	return m_isToggleFlag;
}

void ADS_Manager::Toggle(bool isInScope) {
		
	if (isInScope) {
		restoreZoomBtnReleaseCheck();
	}
	else {
		preventZoomBtnReleaseCheck();
	}
	m_isToggleFlag = false;
}

void ADS_Manager::restoreZoomBtnReleaseCheck(){
	
	if (Patcher::patchIfNeeded("", m_zoomBtnReleaseCheckAddr, ZoomBtnReleaseCheckInstructionVec)) {
		
		m_zoomInstructionState = zoomCodeOriginal;
	}
}

void ADS_Manager::preventZoomBtnReleaseCheck()
{
	if (Patcher::patchIfNeeded("", m_zoomBtnReleaseCheckAddr, PreventZoomBtnReleaseNewInstructionVec)) {
	
		m_zoomInstructionState = zoomCodePatched;

	}
}

AdsZoomCheckInstructionState ADS_Manager::getPatchState() {
	return m_zoomInstructionState;
}
