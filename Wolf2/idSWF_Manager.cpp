#include "idSWF_Manager.h"


bool idSWF_Manager::m_debug_IsMercuryLogComplete = false;
const char* idSWF_Manager::m_mercuryHudFileName = "swf/merchud.swf";
idSWF* idSWF_Manager::m_mercuryHudIdSWFPtr = nullptr;

 std::vector<std::string>idSWF_Manager::m_debug_AllMercuryHudSpriteInstStrVec;
 std::vector<std::string>idSWF_Manager::m_debug_TestingHudSpriteInstStrVec;

 //! do we fill the the vector with all the hud names elements from the hook
 bool idSWF_Manager::isFillAllMercuryHudFlag = false;

 std::mutex idSWF_Manager::g_mutex;

 // ImVec4(0.894f, 0.871f, 0.816f, 1.0f);
 const swfColorRGBA_t idSWF_Manager::m_defaultHudTextColor = { 228, 222, 208, 255 };  // White
 const swfColorRGBA_t idSWF_Manager::m_orangeHudTextColor = { 255, 165, 0, 255 };      
 const swfColorRGBA_t idSWF_Manager::m_redHudTextColor = { 255, 0, 0, 255 };      

 //std::vector<idSWFSpriteInstance*>idSWF_Manager::m_debug_AllMercuryHudSpriteInstStrVec;
 //std::vector<std::string> idSWF_Manager::m_debugAllHudSpriteInstancesNames;


 //! public:
 const int idSWF_Manager::armorTextInstanceHash = 0x7D29253A;
 const int idSWF_Manager::healthTextInstanceHash = 0x389D0C5F;
 const int idSWF_Manager::devMenuTextInstanceHash = 0x370DFD62;
 const int idSWF_Manager::devMenuLvlLoadedTextInstanceHash = 0x79534510;

 const int idSWF_Manager::maxedOutSwfHash = 0xB50D61ED;
 const int idSWF_Manager::alarmIconsSwfHash = 0x87307F0C;
 const int idSWF_Manager::simulationTopHudScoreTextHash = 0x9808CE0D;
 const float idSWF_Manager::swfScaleDefault = 1.0f;








 //static swfColorRGBA_t idSWF_Manager::lerp(const swfColorRGBA_t& color1, const swfColorRGBA_t& color2, float t) {
	// swfColorRGBA_t result;
	// result.r = static_cast<unsigned char>(color1.r + (color2.r - color1.r) * t);
	// result.g = static_cast<unsigned char>(color1.g + (color2.g - color1.g) * t);
	// result.b = static_cast<unsigned char>(color1.b + (color2.b - color1.b) * t);
	// result.a = static_cast<unsigned char>(color1.a + (color2.a - color1.a) * t);
	// return result;
 //}


 float idSWF_Manager::smoothlyChangingFloat(float speed) {
	 // Set the initial time only once
	 static auto startTime = std::chrono::high_resolution_clock::now();

	 // Calculate elapsed time
	 auto currentTime = std::chrono::high_resolution_clock::now();
	 auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;

	 // Calculate the value using a sine function
	 float value = 0.5f * std::sin(speed * elapsedTime) + 0.5f;

	 return value;
 }

 bool idSWF_Manager::isBlink(int blinkFreqMillis) {
	 static bool isBlink = false;
	 static uint64_t lastBlinkMs = 0;

	 if (K_Utils::EpochMillis() - lastBlinkMs > blinkFreqMillis) {
		 lastBlinkMs = K_Utils::EpochMillis();
		 isBlink = !isBlink;
	 }
	 return isBlink;
 }


 //! color transitions/blinking
void idSWF_Manager::lerp(idSWFTextInstance* textInst) {	

	//float t = (float)idSWF_Manager::smoothlyChangingFloat(ModSettingsManager::getHudWarningBlinkSpeedMs());
	float t = 5.0f;

	textInst->color.r = static_cast<unsigned char>(m_defaultHudTextColor.r + (m_redHudTextColor.r - m_defaultHudTextColor.r) * t);
	textInst->color.g = static_cast<unsigned char>(m_defaultHudTextColor.g + (m_redHudTextColor.g - m_defaultHudTextColor.g) * t);
	textInst->color.b = static_cast<unsigned char>(m_defaultHudTextColor.b + (m_redHudTextColor.b - m_defaultHudTextColor.b) * t);
	textInst->color.a = static_cast<unsigned char>(m_defaultHudTextColor.a + (m_redHudTextColor.a - m_defaultHudTextColor.a) * t);
 }


void idSWF_Manager::blink(idSWFTextInstance* textInst) {
	
	if (isBlink(ModSettingsManager::getHudWarningBlinkSpeedMs())) {
		textInst->color.r = m_redHudTextColor.r;
		textInst->color.g = m_redHudTextColor.g;
		textInst->color.b = m_redHudTextColor.b;
		textInst->color.a = m_redHudTextColor.a;
	}
	else {
		textInst->color.r = m_defaultHudTextColor.r;
		textInst->color.g = m_defaultHudTextColor.g;
		textInst->color.b = m_defaultHudTextColor.b;
		textInst->color.a = m_defaultHudTextColor.a;
	}
}


void idSWF_Manager::setOrangeColor(idSWFTextInstance* textInst) {

	textInst->color.r = m_orangeHudTextColor.r;
	textInst->color.g = m_orangeHudTextColor.g;
	textInst->color.b = m_orangeHudTextColor.b;
	textInst->color.a = m_orangeHudTextColor.a;
}


void idSWF_Manager::setDefaultColor(idSWFTextInstance* textInst) {

	textInst->color.r = m_defaultHudTextColor.r;
	textInst->color.g = m_defaultHudTextColor.g;
	textInst->color.b = m_defaultHudTextColor.b;
	textInst->color.a = m_defaultHudTextColor.a;
}





void idSWF_Manager::debug_LogUniqueTextInstances(idSWFTextInstance* textInst) {
	static std::vector<std::string> uniqueTxtVec;

	if (!textInst) return;

	std::string instanceName = textInst->text.data;
	// Check if spriteInstPtr is not already in the vector
	if (std::find(uniqueTxtVec.begin(), uniqueTxtVec.end(), instanceName) == uniqueTxtVec.end()) {
		uniqueTxtVec.push_back(instanceName);
		logInfo("found: text instance: %p, with name: %s", textInst, textInst->text.data);
	}
}




bool idSWF_Manager::addMercuryHudSpriteInstanceNameToVec(idSWF* idSWF_Ptr, idSWFSpriteInstance* spriteInstPtr) {

	//if (!isFillAllMercuryHudFlag) return false;;

	if (idSWF_Ptr && (std::string(idSWF_Ptr->filename.str) == m_mercuryHudFileName)) {

		std::string instName = std::string(spriteInstPtr->name.str);

		if (instName.empty()) return false;
		if (instName.starts_with("wheel")) return false;

		// Check if spriteInstPtr is not already in the vector
		if (std::find(m_debug_AllMercuryHudSpriteInstStrVec.begin(), m_debug_AllMercuryHudSpriteInstStrVec.end(), instName) == m_debug_AllMercuryHudSpriteInstStrVec.end()) {
			m_debug_AllMercuryHudSpriteInstStrVec.push_back(instName);
			logInfo("addMercuryHudSpriteInstance: adding: %s", spriteInstPtr->name.str);
			return true;
		}
	}
	return false;
}





  std::vector<std::string> idSWF_Manager::getTestingInstNamesVec() {

	  return m_debug_TestingHudSpriteInstStrVec;
  }


 void idSWF_Manager::debug_AllMercuryHudNamesInVec()
 {
	 logInfo("debug_logSpriteInstance: m_debug_AllMercuryHudSpriteInstStrVec size: %zu", m_debug_AllMercuryHudSpriteInstStrVec.size());
	 for (size_t i = 0; i < m_debug_AllMercuryHudSpriteInstStrVec.size(); i++)
	 {

		 auto instName = m_debug_AllMercuryHudSpriteInstStrVec[i];
		 logInfo("sprite instance name: %s", instName.c_str());	

	 }
 }




 //? doesn't work as intended. rewrite it don't use it.
 void idSWF_Manager::TestHudElements() {
	 /*static uint64_t lastGetAsyncKeyPress = 0;

	 if (GetAsyncKeyState(VK_NUMPAD8) && ((K_Utils::EpochMillis() - lastGetAsyncKeyPress) > 300)) {
		 lastGetAsyncKeyPress = K_Utils::EpochMillis();

		 if (!isFillAllMercuryHudFlag) {
			 logWarn("VK_NUMPAD8 pressed, Acquiring Sprite Instance names, press numpad 8 again to stop.....");
			 std::lock_guard<std::mutex> lock(g_mutex);
			 m_debug_AllMercuryHudSpriteInstStrVec.clear();
			 m_debug_TestingHudSpriteInstStrVec.clear();
			 isFillAllMercuryHudFlag = true;
		 }
		 else {
			 logWarn("VK_NUMPAD8 pressed, stopping Acquiring Sprite Instance names");
			 isFillAllMercuryHudFlag = false;
		 }
	 }

	 if (GetAsyncKeyState(VK_NUMPAD9) && ((K_Utils::EpochMillis() - lastGetAsyncKeyPress) > 300)) {
		 lastGetAsyncKeyPress = K_Utils::EpochMillis();

		 std::lock_guard<std::mutex> lock(g_mutex);
		 if (!m_debug_AllMercuryHudSpriteInstStrVec.empty()) {
			 std::string addedString = m_debug_AllMercuryHudSpriteInstStrVec.back();
			 m_debug_TestingHudSpriteInstStrVec.push_back(addedString);
			 m_debug_AllMercuryHudSpriteInstStrVec.pop_back();
			 logInfo("adding name to test vec: %s (Testing vec size: %zu) ", addedString.c_str(), m_debug_TestingHudSpriteInstStrVec.size());
		 }
		 else {
			 logWarn("m_debug_AllMercuryHudSpriteInstStrVec is empty!");
		 }
	 }

	 if (GetAsyncKeyState(VK_NUMPAD7) && ((K_Utils::EpochMillis() - lastGetAsyncKeyPress) > 300)) {
		 lastGetAsyncKeyPress = K_Utils::EpochMillis();

		 std::lock_guard<std::mutex> lock(g_mutex);
		 if (!m_debug_TestingHudSpriteInstStrVec.empty()) {
			 std::string removedString = m_debug_TestingHudSpriteInstStrVec.back();
			 m_debug_AllMercuryHudSpriteInstStrVec.push_back(removedString);
			 m_debug_TestingHudSpriteInstStrVec.pop_back();
			 logInfo("removing name from test vec: %s (Testing vec size: %zu) ", removedString.c_str(), m_debug_TestingHudSpriteInstStrVec.size());
		 }
		 else {
			 logWarn("m_debug_TestingHudSpriteInstStrVec is empty!");
		 }
	 }*/
 }




//void idSWF_Manager::acquireMercuryHudidSWFPtr(idSWF* idSWF_Ptr) {
//
//	if (idSWF_Ptr && (std::string(idSWF_Ptr->filename.str) == m_mercuryHudFileName)) {
//		if (m_mercuryHudIdSWFPtr != idSWF_Ptr) {
//			m_mercuryHudIdSWFPtr = idSWF_Ptr;
//			logInfo("acquireMercuryHudidSWFPtr: acquirred mercuryHudIdSWFPtr: %p", m_mercuryHudIdSWFPtr);
//		}		
//	}	
//}


//void idSWF_Manager::acquireMercuryHudidSWFPtr(idSWF* idSWF_Ptr) {
//	// Check if idSWF_Ptr is not null and has the correct filename
//	if (idSWF_Ptr && (strcmp(idSWF_Ptr->filename.str, m_mercuryHudFileName) == 0)) {
//		// Check if m_mercuryHudIdSWFPtr is different
//		if (m_mercuryHudIdSWFPtr != idSWF_Ptr) {
//			m_mercuryHudIdSWFPtr = idSWF_Ptr;
//			logInfo("acquireMercuryHudidSWFPtr: acquired mercuryHudIdSWFPtr: %p", m_mercuryHudIdSWFPtr);
//		}
//	}
//}


//todo still need to check when res actually changes, may be set the m_mercuryHudIdSWFPtr->frameHeight back to m_idSWF_frameHeightForThisRes is user acces video menu (?) so that we are sure to always get the correct value for m_mercuryHudIdSWFPtr->frameHeight and which would prompt us to reaquire m_idSWF_frameHeightForThisRes. Aslo side not need to have a check box in debug tab of debug mod version that doesn't log the game console
void idSWF_Manager::acquireMercuryHudidSWFPtrFast(idSWF* idSWF_Ptr) {
	if (m_mercuryHudIdSWFPtr != idSWF_Ptr) {
		m_mercuryHudIdSWFPtr = idSWF_Ptr;

		m_idSWF_frameHeightForThisRes = m_mercuryHudIdSWFPtr->frameHeight;

		logInfo("acquireMercuryHudidSWFPtrFast: m_mercuryHudIdSWFPtr has changed to: %p setting m_idSWF_frameHeightForThisRes to m_mercuryHudIdSWFPtr->frameHeight: %.2f", m_mercuryHudIdSWFPtr, m_idSWF_frameHeightForThisRes);
	}
}



void idSWF_Manager::setCustomHudPosAndScale(idSWF* idSWF_Ptr) {

	if (m_idSWF_frameHeightForThisRes == 0.0f) {
		logWarn("setCustomHudPosAndScale: m_idSWF_frameHeightForThisRes is undefined can not touch the hud");
		return;
	}

	//float targetFramHeight = ModSettingsManager::gethudFrameHeightMul() * (float)cachedCvarsManager::get_WindowHeightInt();
	float targetFramHeight = ModSettingsManager::gethudFrameHeightMul() * m_idSWF_frameHeightForThisRes;

	if (idSWF_Ptr->swfScale != ModSettingsManager::getHudScale()) {
		logInfo("setCustomHudPosAndScale setting idSWF_Ptr->swfScale: from %.2f to %.2f", idSWF_Ptr->swfScale, ModSettingsManager::getHudScale());
		idSWF_Ptr->swfScale = ModSettingsManager::getHudScale();
	}

	if (idSWF_Ptr->frameHeight != targetFramHeight) {
		idSWF_Ptr->frameHeight = targetFramHeight;
		logInfo("updateHudPosAndScale: idSWF_Ptr->frameHeight is being changed to: %.2f (hudFrameHeightMul: %.2f WindowHeightInt: %d , m_idSWF_frameHeightForThisRes: %.2f)", idSWF_Ptr->frameHeight, ModSettingsManager::gethudFrameHeightMul(), cachedCvarsManager::get_WindowHeightInt(), m_idSWF_frameHeightForThisRes);
	}	
}




void idSWF_Manager::resetHudPosAndScaleToDefault(idSWF* idSWF_Ptr) {

	if (m_idSWF_frameHeightForThisRes == 0.0f) {
		logWarn("resetHudPosAndScaleToDefault: m_idSWF_frameHeightForThisRes is undefined can not reset the hud");
		return;
	}

	static int lastWinHeigth = -1;
	int cachedWindowHeight = cachedCvarsManager::get_WindowHeightInt();

	//? maybe for some users the swfScale is not 1.0 by default when they play on higher resolution? Update no i think it's one the issue was with frame height default val.
	
	if (idSWF_Ptr->swfScale != swfScaleDefault) {
		logInfo("resetHudPosAndScaleToDefault resetting idSWF_Ptr->swfScale: %.2f to swfScaleDefault: %.2f", idSWF_Ptr->swfScale, swfScaleDefault);
		idSWF_Ptr->swfScale = swfScaleDefault;
	}

	//? this was the cause of the hud being offset toward the top and the cause of the crosshair being offcentered in res other than 1080p imo:
	//idSWF_Ptr->frameHeight = (float)cachedWindowHeight;


	if (idSWF_Ptr->frameHeight != m_idSWF_frameHeightForThisRes) {
		logInfo("resetHudPosAndScaleToDefault: setting idSWF_Ptr->frameHeight from: %.2f to %.2f", idSWF_Ptr->frameHeight, m_idSWF_frameHeightForThisRes);
		idSWF_Ptr->frameHeight = m_idSWF_frameHeightForThisRes;		
	}

	if (cachedWindowHeight != lastWinHeigth) {
		logInfo("resetHudPosAndScaleToDefault: WindowHeight has changed from %d to: %d (swfScale : %2.f m_idSWF_frameHeightForThisRes: %.2f)", lastWinHeigth, cachedWindowHeight, idSWF_Ptr->swfScale, m_idSWF_frameHeightForThisRes);
		lastWinHeigth = cachedWindowHeight;
	}
}


//void idSWF_Manager::scaleHud(float scale) {
//	if (MemHelper::isBadReadPtr(m_mercuryHudIdSWFPtr)) {
//		logWarn("offsetHudr: m_mercuryHudIdSWFPtr is bad ptr: %p which is ok if no level is loaded.", m_mercuryHudIdSWFPtr);
//		return;
//	}
//	m_mercuryHudIdSWFPtr->swfScale = scale;
//}








void idSWF_Manager::debug_LogMercuryHudDictionary()
{
	if (MemHelper::isBadReadPtr(m_mercuryHudIdSWFPtr)) {
		logErr("debug_LogMercuryHudDictionary: can not log m_mercuryHudIdSWFPtr is a bad pointer: %p", m_mercuryHudIdSWFPtr);
		return;
	}

	logInfo("debug_LogMercuryHudDictionary: logging mercury hud (%p) dict ", m_mercuryHudIdSWFPtr);
	logInfo("debug_LogMercuryHudDictionary: &m_mercuryHudIdSWFPtr->dictionary is: %p", &m_mercuryHudIdSWFPtr->dictionary);

	auto dictionalyIdList = (idList*)&m_mercuryHudIdSWFPtr->dictionary;

	if (dictionalyIdList == nullptr || dictionalyIdList->list == nullptr) {
		logErr("debug_LogMercuryHudDictionary: dictionary is null or invalid.");
		return;
	}

	logInfo("dictionalyIdList->list is %p  and dictionalyIdList->num is: %d", (void*)dictionalyIdList->list, dictionalyIdList->num);

	for (size_t i = 0; i < dictionalyIdList->num; i++)
	{
		auto entry = (idSWFDictionaryEntry*)(dictionalyIdList->list + (i * 88));

		if (entry == nullptr) {
			logErr("debug_LogMercuryHudDictionary: dictionary entry at index %zu is null.", i);
			continue;
		}

		
		idSWF_Manager::debug_changeidSWFShapeChannelScale(entry);


		/*logInfo("Entry %zu: addr: %p", i, entry);

		if (!MemHelper::isBadReadPtr(&entry->type)) {
			logInfo("  type: %d", entry->type);
		}
		if (!MemHelper::isBadReadPtr(&entry->idMaterial_material)) {
			logInfo("  idMaterial_material: %p", entry->idMaterial_material);
		}
		if (!MemHelper::isBadReadPtr(&entry->idSWFShape_shape)) {
			logInfo("  idSWFShape_shape: %p", entry->idSWFShape_shape);
		}
		if (!MemHelper::isBadReadPtr(&entry->idSWFSprite_sprite)) {
			logInfo("  idSWFSprite_sprite: %p", entry->idSWFSprite_sprite);
		}
		if (!MemHelper::isBadReadPtr(&entry->idSWFFont_font)) {
			logInfo("  idSWFFont_font: %p", entry->idSWFFont_font);
		}
		if (!MemHelper::isBadReadPtr(&entry->idSWFText_text)) {
			logInfo("  idSWFText_text: %p", entry->idSWFText_text);
		}
		if (!MemHelper::isBadReadPtr(&entry->idSWFEditText_edittext)) {
			logInfo("  idSWFEditText_edittext: %p", entry->idSWFEditText_edittext);
		}*/
		
	}
}

void  idSWF_Manager::debug_changeidSWFShapeChannelScale(idSWFDictionaryEntry* entry) {

	if (MemHelper::isBadReadPtr(&entry->type)) {
		logWarn("&entry->type is bad ptr %p", &entry->type);
		return;
	}

	if (MemHelper::isBadReadPtr(&entry->channelScale)) {
		logWarn("&entry->channelScale is bad ptr %p", &entry->channelScale);
		return;
	}

	if (entry->type == swfDictType_t::SWF_DICT_SHAPE ) {

		logInfo("debug_changeidSWFShapeChannelScale changing channel scale....");		
		entry->channelScale.x += 200.0f;
		//entry->channelScale.y -= 200.0f;
	}

}



void idSWF_Manager::debug_offsetSpriteInstances(idSWF* idSWF_Ptr, idSWFSpriteInstance* spriteInstPtr)
{
	if (idSWF_Ptr && (std::string(idSWF_Ptr->filename.str) == m_mercuryHudFileName)) {
		
		if (spriteInstPtr) {


			spriteInstPtr->alignmentType = ALIGNMENTTYPE_CENTER;

			//if (std::string(spriteInstPtr->name.str).starts_with("health")) {
			//if (std::string(spriteInstPtr->name.str).starts_with("health")) {

			//	spriteInstPtr->alignmentType = ALIGNMENTTYPE_CENTER;

			//	//logInfo("triggg");
			//	//spriteInstPtr->yOriginal = 160.0f; // doesn't work no change



			//}
		}

		

	}
	

}



//void idSWF_Manager::debug_LogMercuryHudDictionary()
//{
//	if (MemHelper::isBadReadPtr(m_mercuryHudIdSWFPtr)) {
//		logErr("debug_LogMercuryHudDictionary: can not log m_mercuryHudIdSWFPtr is bad ptr: %p", m_mercuryHudIdSWFPtr);
//		return;
//	}
//
//	logInfo("debug_LogMercuryHudDictionary: logging mercury hud (%p) dict ", m_mercuryHudIdSWFPtr);
//	auto dictionalyIdList = (idList*)&m_mercuryHudIdSWFPtr->dictionary;
//	for (size_t i = 0; i < dictionalyIdList->num; i++)
//	{
//		auto entry = (idSWFDictionaryEntry*)dictionalyIdList->list[i];
//		logInfo("type: %d", entry->type);
//		logInfo("idMaterial_material: %p", entry->idMaterial_material);
//		logInfo("idSWFShape_shape: %p", entry->idSWFShape_shape);
//		logInfo("idSWFSprite_sprite: %p", entry->idSWFSprite_sprite);
//		logInfo("idSWFFont_font: %p", entry->idSWFFont_font);
//		logInfo("idSWFText_text: %p", entry->idSWFText_text);
//		logInfo("idSWFEditText_edittext: %p", entry->idSWFEditText_edittext);
//
//	}
//
//}


