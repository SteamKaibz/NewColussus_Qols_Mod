#include "idLightManager.h"






const int idLightManager::m_headLightptrOffset = 0x4EE0;

//bool idLightManager::m_isSetLightOnFlag = false;

//bool idLightManager::m_isToggleHeadLightStateFlag = false;

//uint64_t idLightManager::m_lastCheckMs = 0;

__int64 idLightManager::debugLastHeadLightPtr = 0;

const char* idLightManager::m_headLightEntityName = "player headlight";

//bool idLightManager::m_isLastKnowLightStateOff = true;

//bool idLightManager::m_isRefreshLightFlag = false;

//idLight* idLightManager::m_lastKnowHeadLightPtr = nullptr;
idLight* idLightManager::m_debug_lastKnowHeadLightPtr = nullptr;

//const std::vector<unsigned char> idLightManager::InstantSwitchLightVec = { 0x8C };
//const std::vector<unsigned char> idLightManager::FadeLightVecVec = { 0x8D };

setLightOn_E926A0 idLightManager::m_setLightOnFp = 0;

setLightLighOff_E92730 idLightManager::m_setLightOffFp = 0;

refreshLight_E92230 idLightManager::m_refreshLightFp = 0;

setMaterial_E924B0 idLightManager::m_setMaterialFp = 0;

const float idLightManager::m_defautlLightStartX = 0.0f;
const float idLightManager::m_inScopelLightStartX = 0.3f;

bool idLightManager::m_wasFlashlightOn = false;


//const std::string idLightManager::m_mapBonusRiversideName = "game/wolf/bonusmaps/bonusmap01";

//const float idLightManager::m_headlightSpecularScope = 1.0f;
//const float idLightManager::m_headlightSpecularDefault = 1.0f;

//bool idLightManager::isLastKnownHeadLightStateOff =



//? KEEP IN MIND THAT IF YOU USE A SPOTLIGHT TYPE, THE MTR YOU WANT IS A SPOT LIGHT MTR, SO IF YOU USE biground1 THE LIGHT WILL NOT WORK AT VERY CLOSE RANGE
// 
//? works for reuniong but not for at least one of the extra mission so won't be using it:
//const char* idLightManager::m_headLighMaterialName = "lights/analytical/spot/p50/spot_focus2_frac40";

//? works for a extra mission but can not be found for the Reunion level but
//! update it seems we can not load any materials we want....
//const char* idLightManager::m_headLighMaterialName = "lights/analytical/spot/p100/spot_focus1_frac80";

//? Not good for spotlight
//const char* idLightManager::m_headLighMaterialName = "lights/biground1";

//? Not good for spotlight
//const char* idLightManager::m_headLighMaterialName = "lights/biground2";

//? Not good for spotlight
//const char* idLightManager::m_headLighMaterialName = "lights/gaus";

//? does't work for extra mission but works for reunion.
//const char* idLightManager::m_headLighMaterialName = "lights/analytical/spot/p100/spot_focus4_frac80";



__int64 idLightManager::m_headLighMaterialPtr = 0;



//? Update spawnId is not reliadaed to identify an entiry, its spawnId will change depending on which map/part ofthe map you are. 
//x experiment to check if spawnid is always the same for each different entities types
//const int idLightManager::m_headLightSpawnId = 0x1575;


void idLightManager::logChangedHeadLightPtr(idLight* headlighPtr) {
	if (headlighPtr != m_debug_lastKnowHeadLightPtr) {
		logInfo("logChangedHeadLightPtr: headlighPtr has changed from %p to %p", m_debug_lastKnowHeadLightPtr,  headlighPtr);
		m_debug_lastKnowHeadLightPtr = headlighPtr;
	}	
}


//bool idLightManager::isHeadLightPtr(idLight* headlighPtr) {
//	return headlighPtr && (headlighPtr == m_lastKnowHeadLightPtr);	
//}



idLight* idLightManager::getHeadLightPtr() {

	//logInfo("getHeadLightPtr:  WTF????????????????????????????????????????????");
	auto idPlayerPtr = idGameLocalManager::getIdPlayer();
	if (!idPlayerPtr) {
		logWarn("getHeadLightPtr: can not get ptr cause idPlayer is null or bad ptr retuning null");
		return nullptr;
	}
	//logInfo("getHeadLightPtr: &idPlayerPtr->playerVolatileUnsaved.headLightptr: %p", idPlayerPtr->playerVolatileUnsaved.headLightptr);
	return idPlayerPtr->playerVolatileUnsaved.headLightptr;
}


idLight* idLightManager::getHeadLightPtr(idPlayer* idPlayerPtr) {

	if (idPlayerPtr) {
		return idPlayerPtr->playerVolatileUnsaved.headLightptr;
	}
	logWarn("getHeadLightPtr: can not get ptr cause idPlayer is null");
	return nullptr;
	//logInfo("getHeadLightPtr:  WTF????????????????????????????????????????????");
	//auto idPlayerPtr = idGameLocalManager::getIdPlayer();
	//if (!idPlayerPtr) {
	//	logWarn("getHeadLightPtr: can not get ptr cause idPlayer is null or bad ptr retuning null");
	//	return nullptr;
	//}
	////logInfo("getHeadLightPtr: &idPlayerPtr->playerVolatileUnsaved.headLightptr: %p", idPlayerPtr->playerVolatileUnsaved.headLightptr);
	//return idPlayerPtr->playerVolatileUnsaved.headLightptr;
}


void idLightManager::debugGetLastHeadLightPtr() {
	auto ptr = idLightManager::getHeadLightPtr();
	logInfo("debugGetLastHeadLightPtr: headlight ptr: %p", ptr);
}

void idLightManager::getCurrentMapHeadLighMaterialPtr()
{
	m_headLighMaterialPtr = idMaterialManager::getCurrentMapSpotLightMaterialPtr();
	logInfo("getCurrentMapHeadLighMaterialPtr found headlight ptr at %p", (void*)m_headLighMaterialPtr);
	/*if (MemHelper::isBadReadPtr((void*)m_headLighMaterialPtr)) {
		m_headLighMaterialPtr = 0;
	}*/

}

//bool idLightManager::isLastKnownHeadLightStateOff() {
//	return m_isLastKnowLightStateOff;
//}


//!  as as test i identified the headligth idManagedClass::objectNumber as 0x145E let's see if it's consistent.....
//!  after relaunching obj num is still 0x145E. Update just before the moment with wheelchair where your wife saves you the obj number is 0x149A, but this is also where we have the bug so....

//void idLightManager::setRefreshFlag(bool isOn) {
//	logInfo("setRefreshFlag: setting m_isRefreshLightFlag: %d", isOn);
//	m_isRefreshLightFlag = isOn;
//}
//
//bool idLightManager::isRefreshFlag() {
//	return m_isRefreshLightFlag;
//}

void idLightManager::setHeadlightOn(idLight* headlightPtr)
{
	if (isCurrentMapRiversideBonus()) {
		logWarn("setHeadlightOn: current map 'could be' riverside bonus, not setting lightOff to prevent crash");
		return;
	}

	if (!m_setLightOnFp) {
		//! result: matches @ 0xE926A0, sig direct: 48 89 5C 24 ? 57 48 83 EC 20 0F 10 81
		m_setLightOnFp = reinterpret_cast<setLightOn_E926A0>(MemHelper::getFuncAddr(0xE926A0)); 
	}

	if (m_setLightOnFp && headlightPtr) {
		//logInfo("setHeahlightOn called...");
		m_setLightOnFp(headlightPtr);
	}
}

void idLightManager::setHeadlightOff(idLight* headlightPtr)
{
	if (isCurrentMapRiversideBonus()) {
		logWarn("setHeadlightOff: current map 'could be' riverside bonus, not setting lightOff to prevent crash");
		return;
	}

	if (!m_setLightOffFp) {
		//! result: matches @ 0xE92730, sig direct : 40 53 48 83 EC 20 0F 10 05
		m_setLightOffFp = reinterpret_cast<setLightLighOff_E92730>(MemHelper::getFuncAddr(0xE92730));
	}

	if (m_setLightOffFp && headlightPtr) {
		//logInfo("setHeahlightOff called...");
		m_setLightOffFp(headlightPtr);
	}

}

void idLightManager::toggleHeadLight()
{
	
	idLight* headlightPtr = getHeadLightPtr();
	if (headlightPtr) {

		if (isHeadLightColorBlack(headlightPtr)) {
			setHeadlightOn(headlightPtr);
		}
		else {
			setHeadlightOff(headlightPtr);
		}		
	}
}

//? have to try this again now that we don't change the light intensity....
void idLightManager::refreshHeadLight(idLight* headlightPtr)
{
	if (!m_refreshLightFp) {
		//! result: matches @ 0xE92230, sig direct: 40 53 48 83 EC 20 45 33 C9 45 33 C0 B2 01
		m_refreshLightFp = reinterpret_cast<refreshLight_E92230>(MemHelper::getFuncAddr(0xE92230));
	}

	if (m_refreshLightFp && headlightPtr) {
		logInfo("refresh Light called...");
		m_refreshLightFp(headlightPtr);
	}
}

//! atm this is called when we leave menu and when level is loaded
void idLightManager::updateHeadLight()
{
	if (isCurrentMapRiversideBonus()) {
		logWarn("updateHeadLight: current map 'could be' riverside bonus, not updating light");
		return;
	}


	idLight* headlightPtr = getHeadLightPtr();

	if (!headlightPtr) {
		logWarn("updateHeadLight: can not update cause headlightPtr is bad ptr: %p", headlightPtr);
		return;
	}

	if (!headlightPtr->lightMaterial) {
		idLightManager::setLightMaterialFromVec();
	}


	idSpotLight* spotLight = (idSpotLight*)&headlightPtr->spotLight;

	if (headlightPtr->lightType != lightType_t::LIGHT_SPOT) {
		headlightPtr->lightType = lightType_t::LIGHT_SPOT;
		logInfo("updateHeadLight: updating lightType to %d", (int)headlightPtr->lightType);
	}

	//! making sure light doesn't add glare to scope.
	if (headlightPtr->spotLight.lightStart.x != m_defautlLightStartX) {
		headlightPtr->spotLight.lightStart.x = m_defautlLightStartX;
		logInfo("updateHeadLight: updating spotLight.lightStart.x to %f", m_defautlLightStartX);
	}


	float newIntensity = ModSettingsManager::getHeadLightIntensity();
	if (headlightPtr->lightIntensity != newIntensity) {
		headlightPtr->lightIntensity = newIntensity;
		logInfo("updateHeadLight: updating Intensity: %.2f", headlightPtr->lightIntensity);
	}

	float newTargetX = ModSettingsManager::getHeadLightTargetX();
	if (spotLight->lightTarget.x != newTargetX) {
		spotLight->lightTarget.x = newTargetX;
		logInfo("updateHeadLight: updating lightTarget.x : %.2f", spotLight->lightTarget.x);
		//isUserSettingChange = true;		
	}

	//! this exist cause we want to change this value when in scope
	if (spotLight->lightStart.x != m_defautlLightStartX) {
		spotLight->lightStart.x = m_defautlLightStartX;
		logInfo("updateHeadLight: updating lightStart.x : %.2f", spotLight->lightStart.x);
	}


	float newEndX = ModSettingsManager::getHeadLightEndX();
	if (spotLight->lightEnd.x != newEndX) {
		spotLight->lightEnd.x = newEndX;
		logInfo("updateHeadLight: updating lightEnd.x: %.2f", spotLight->lightEnd.x);

	}


	headlightPtr->originalColor = ModSettingsManager::getUserFlashlightColor();

	//! this didn't seem to update the color.
	//refreshHeadLight(headlightPtr);
	
	if (!isHeadLightColorBlack(headlightPtr)) { //! if headlight is on
		setHeadlightOff(headlightPtr);
		setHeadlightOn(headlightPtr);
	}
}




bool idLightManager::isHeadLightColorBlack(idLight* headlightPtr) {
	return headlightPtr->lightColor.isEqual(colorHeadLighOff);
}



bool idLightManager::isHeadLightOn()
{//! used by gui
	idLight* headlightPtr = getHeadLightPtr();
	if (headlightPtr) {
		return !(headlightPtr->lightColor.isEqual(colorHeadLighOff));
	}
	return false;
}





bool idLightManager::shouldFlashLightBeOff(movementMode_t curMovementMode) {
	switch (curMovementMode)
	{
	case MOVEMENT_MODE_MIDNIGHT_LIMITVIEW_NARROW: //! enigma machine is in this category		
		return true; //! we return cause there is not point checking lightStart.x is light is off 
	case MOVEMENT_MODE_WARTABLE:
		return true;
	}
	return false;
}


bool idLightManager::shouldFlashLightBeOff() {
	auto idPlayerPtr = idGameLocalManager::getIdPlayer();

	if (!idPlayerPtr) {
		return true;
	}	

	movementMode_t curMovementMode = idPlayerPtr->playerVolatile.currentMovementMode;
	switch (curMovementMode)
	{
	case MOVEMENT_MODE_MIDNIGHT_LIMITVIEW_NARROW: //! enigma machine is in this category		
		return true; //! we return cause there is not point checking lightStart.x is light is off 
	case MOVEMENT_MODE_WARTABLE:
		return true;
	}
	return false;
}



//! reseting this between levels loads.
void idLightManager::resetWasFlashlightOn() {
	logInfo("reseting wasFlashlightOn");
	m_wasFlashlightOn = false;
}


bool idLightManager::isCurrentMapRiversideBonus(idPlayer* idPlayerPtr)
{
	//! this will be true only in ubetkommando riverside level
	return idPlayerPtr->playerVolatile.headlightIsActive;
	//std::string currentMapName = idGameLocalManager::getCurrentMapName();
	//return currentMapName == m_mapBonusRiversideName;
}

bool idLightManager::isCurrentMapRiversideBonus()
{
	auto idPlayerPtr = idGameLocalManager::getIdPlayer();
	if (!idPlayerPtr) {
		logWarn("isCurrentMapRiversideBonus: could not get idPlayer: returning true as it's the safest choice...");
		return true;
	}
	//! this will be true only in ubetkommando riverside level
	return idPlayerPtr->playerVolatile.headlightIsActive;	
}



//! will adjustLightStartX and will toggle it off if in specific movement state to prevent glare when using screens
//! using 1 func for both so it's more efficient
void idLightManager::AdjustLight(idPlayer* idPlayerPtr) {

	//static bool wasFlashLightOn = false;

	if ((MemHelper::isBadReadPtr(idPlayerPtr))) {
		return;
	}

	if (isCurrentMapRiversideBonus(idPlayerPtr)) {
		return;
	}

	idLight* headlightPtr = getHeadLightPtr(idPlayerPtr);
	if (!headlightPtr) return;

	//! if flashlight on and it should be off:
	if (!isHeadLightColorBlack(headlightPtr) && idLightManager::shouldFlashLightBeOff(idPlayerPtr->playerVolatile.currentMovementMode)) {
		m_wasFlashlightOn = true;
		setHeadlightOff(headlightPtr);
		return; //! return cause there is not point checking lightStart.x is light is off 
	}

	//! if flashlight was on when we forced it off because of movement state (enigma/wartabel/recharging...)
	else if (m_wasFlashlightOn && !idLightManager::shouldFlashLightBeOff(idPlayerPtr->playerVolatile.currentMovementMode)) {
		m_wasFlashlightOn = false;
		setHeadlightOn(headlightPtr);		
	}


	bool isUpdateLightTrigger = false;

	idSpotLight* spotLight = (idSpotLight*)&headlightPtr->spotLight;

	if (idPlayerPtr->playerVolatile.hudInfo.inScope || idPlayerPtr->playerVolatile.hudInfo.isZooming) {
		if (spotLight->lightStart.x != m_inScopelLightStartX) {
			spotLight->lightStart.x = m_inScopelLightStartX;
			isUpdateLightTrigger = true;
			logInfo("adjustLightStartX: lightStart.x to scope mode: %.2f", spotLight->lightStart.x);
		}
	}
	else {
		if (spotLight->lightStart.x != m_defautlLightStartX) {
			spotLight->lightStart.x = m_defautlLightStartX;
			isUpdateLightTrigger = true;
			logInfo("adjustLightStartX: updating lightStart.x : %.2f", spotLight->lightStart.x);
		}
	}

	//? this actually works to update the lightStart.x so i guess it's better that the alt we had before.
	if (isUpdateLightTrigger) {
		refreshHeadLight(headlightPtr);
	}

}




bool idLightManager::setSpotLighMaterial(std::string matName)
{	
	//if (isCurrentMapRiversideBonus()) return true;


	if (!m_setMaterialFp) {
		//! result: matches @ 0xE924B0, sig direct: 40 53 48 83 EC 20 48 8B D9 48 85 D2 74 7A 45 33 C9
		m_setMaterialFp = reinterpret_cast<setMaterial_E924B0>(MemHelper::getFuncAddr(0xE924B0));
	}

	idLight* headlightPtr = getHeadLightPtr();
	if (!headlightPtr) {
		logWarn("setSpotLighMaterial: can not set matr cause headlightPtr is bad ptr: %p", headlightPtr);
		return false;
	}

	if (m_setMaterialFp) {

		m_setMaterialFp(headlightPtr, matName.c_str());
		if (headlightPtr->lightMaterial) {
			logInfo("setSpotLighMaterial succes setting light material %s (%p) to headlight", matName.c_str(), headlightPtr->lightMaterial);
			return true;
		}
		else {
			logWarn("setSpotLighMaterial FAILED applying material %s to headlight", matName.c_str());
			return false;
		}		
	}
	logWarn("setSpotLighMaterial: failed to find setMaterialFp ");
	return false;	
}



//? unfortunately the material "lights/headlight/headlight01" is not available on many maps and i suspect on any map unless it's the last uberkomando map so that's that.

bool idLightManager::setLightMaterialFromVec()
{
	if (isCurrentMapRiversideBonus()) {
		logWarn("current map 'could be' riverside bonus, not touching headlight material to prevent crash and it should already be assigned");
		return true;
	}


	std::vector<std::string> materialsNamesCandidates{ "lights/analytical/spot/p50/spot_focus1_frac80", "lights/analytical/spot/p100/spot_focus1_frac80", "lights/analytical/spot/p100/spot_focus4_frac80", "lights/analytical/spot/p50/spot_focus2_frac40" };

	for (size_t i = 0; i < materialsNamesCandidates.size(); i++)
	{
		if (idLightManager::setSpotLighMaterial(materialsNamesCandidates[i])) {
			return true;
		}
	}
	logWarn("setLightMaterialFromVec: failed to find any suitable materials for headlight. Attempting to use available mtrs for current map...");

	auto altCandidatesNames = idMaterialManager::getCurrentMapSpotLightMaterialNames();
	for (size_t i = 0; i < altCandidatesNames.size(); i++)
	{
		if (idLightManager::setSpotLighMaterial(altCandidatesNames[i])) {
			return true;
		}
	}	
	return false;
}














//! After trying many lights...they all look the same to me it's just that the intensity if different, and may be the borders more or less blurry(?)

void idLightManager::debugSetLightMaterialFromVec()
{
	static int index = 0;

	std::vector<std::string> materialsNamesCandidates{ "lights/analytical/spot/p100/spot_focus1_frac80", "lights/analytical/spot/p100/spot_focus4_frac80", "lights/analytical/spot/p50/spot_focus2_frac40" };
	
	auto mapMatrVec = idMaterialManager::getCurrentMapSpotLightMaterialNames();

	for (size_t i = 0; i < mapMatrVec.size(); i++)
	{
		materialsNamesCandidates.push_back(mapMatrVec[i]);
	}

	if (materialsNamesCandidates.empty()) {
		logWarn("debugSetLightMaterialFromVec: materialsNamesCandidates vec is empty can not set material");
		return;
	}

	if (index < materialsNamesCandidates.size()) {
		logInfo("debugSetLightMaterialFromVec: setting light matr: %s (vec size: %zu)", materialsNamesCandidates[index].c_str(), materialsNamesCandidates.size());
		idLightManager::setSpotLighMaterial(materialsNamesCandidates[index]);
		index++;
	}
	else {
		index = 0;
	}
}








//? this used to make the game crash on level load i believe because this func was using the cached m_lastKnowHeadLightPtr and even if it was not a bad ptr it was making the game crash...so now get get the light ptr form idPlayer...
//! this is used because otherwiser there is a glare in the scope
//void idLightManager::adjustLightStartX(idPlayer* idPlayerPtr) {
//
//	//if (MemHelper::isBadReadPtr(m_lastKnowHeadLightPtr) || (MemHelper::isBadReadPtr(idPlayerPtr))) {
//	//	return;
//	//}
//
//	if ((MemHelper::isBadReadPtr(idPlayerPtr))) {
//		return;
//	}
//
//	//? we can not change anything in the renderLight obj as it can and will cause a crash at some point.
//	/*if (!m_lastKnowHeadLightPtr->renderLight) {
//		logWarn("adjustLightStartX: renderLight is null (?!) returning");	
//		return;
//	}*/
//
//	idLight* headlightPtr = getHeadLightPtr();
//	if (!headlightPtr) return;
//
//
//	bool isUpdateLightTrigger = false;
//
//	idSpotLight* spotLight = (idSpotLight*)&headlightPtr->spotLight;
//
//	if (idPlayerPtr->playerVolatile.hudInfo.inScope || idPlayerPtr->playerVolatile.hudInfo.isZooming) {
//		if (spotLight->lightStart.x != m_inScopelLightStartX) {			
//			spotLight->lightStart.x = m_inScopelLightStartX;
//			isUpdateLightTrigger = true;
//			logInfo("adjustLightStartX: lightStart.x to scope mode: %.2f", spotLight->lightStart.x);
//		}
//	}
//	else {
//		if (spotLight->lightStart.x != m_defautlLightStartX) {
//			spotLight->lightStart.x = m_defautlLightStartX;
//			isUpdateLightTrigger = true;
//			logInfo("adjustLightStartX: updating lightStart.x : %.2f", spotLight->lightStart.x);
//		}
//	}
//
//	
//	//? this actually works to update the lightStart.x so i guess it's better that the alt we had before.
//	if (isUpdateLightTrigger) {
//		refreshHeadLight(headlightPtr);
//	}
//
//	
//	//! if trig and light is on:
//	/*if (isUpdateLightTrigger && !isHeadLightColorBlack(headlightPtr)) {
//		setHeadlightOff(headlightPtr);
//		setHeadlightOn(headlightPtr);
//	}*/
//}



//! no need for that anymore we're setting spotLight.lightStart.x instead to prevent scope glare
//void idLightManager::adjustHeadLigthSpecular(idPlayer* idPlayerPtr) {
//
//	if (MemHelper::isBadReadPtr(m_lastKnowHeadLightPtr) || (!idPlayerPtr)) {
//		return;
//	}
//
//	//! not using this as we have to check 4 floats instead of 1....
//	//if (isHeadLightColorBlack(m_lastKnowHeadLightPtr)) return;
//	
//	if (!m_lastKnowHeadLightPtr->renderLight) {
//		logWarn("adjustHeadLigthSpecular: renderLight is null (?!) returning");
//		//logWarn("adjustHeadLigthSpecular: renderLight is null (?!) m_lastKnowHeadLightPtr: %p &m_lastKnowHeadLightPtr->renderLight: %p  &m_lastKnowHeadLightPtr->lightCenterZ: %p &m_lastKnowHeadLightPtr->allowEnvOverride: %p", m_lastKnowHeadLightPtr, &m_lastKnowHeadLightPtr->renderLight, &m_lastKnowHeadLightPtr->lightCenterZ, &m_lastKnowHeadLightPtr->allowEnvOverride);
//		return;
//	}
//
//	if (idPlayerPtr->playerVolatile.hudInfo.inScope) {
//		if (m_lastKnowHeadLightPtr->renderLight->g.dynamicLightSpecularScale != m_headlightSpecularScope) {
//			logInfo("adjustHeadLigthSpecular: debug setting specular to scope");
//			m_lastKnowHeadLightPtr->renderLight->g.dynamicLightSpecularScale = m_headlightSpecularScope;
//		}
//	}
//	else {
//		if (m_lastKnowHeadLightPtr->renderLight->g.dynamicLightSpecularScale != m_headlightSpecularDefault) {
//			logInfo("adjustHeadLigthSpecular: debug setting specular to default");
//			m_lastKnowHeadLightPtr->renderLight->g.dynamicLightSpecularScale = m_headlightSpecularDefault;
//		}
//	}
//}



