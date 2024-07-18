#include "languageManager.h"


//const char* languageManager::m_modMenuBtnStr = "KaibzMod";
//const char* languageManager::m_modMenuHelpStr = "Mod Menu";

const char* languageManager::m_devLocalisedLabelStrPtr = nullptr;
const char* languageManager::m_devLocalisedHelpTextStrPtr = nullptr;

bool languageManager::m_isGetStringsPtrAttempt = false;

bool languageManager::acquireDevStringsPtrs()
{
	m_devLocalisedLabelStrPtr = idResourceManager::getLocalizedStrPtrForRef("#str_menu_root_dev_label");
	m_devLocalisedHelpTextStrPtr = idResourceManager::getLocalizedStrPtrForRef("#str_menu_root_dev_help");

	m_isGetStringsPtrAttempt = true;

	if (m_devLocalisedLabelStrPtr && m_devLocalisedHelpTextStrPtr) {
		return true;
	}
	return false;
}


//void languageManager::replaceDevText(idSWFTextInstance* textInst) {
//	if (textInst) {
//		std::string newText = "KaibzMod";
//		strncpy(textInst->text.data, newText.c_str(), newText.size() + 1);
//	}	
//}


//const char* languageManager::getModMenuBtnStr() {
//	return; m_modMenuBtnStr;
//}
//
//const char* languageManager::getModMenuHelpStr() {
//	return m_modMenuHelpStr;
//}

const char* languageManager::getLocalizedDevStr() {
	return m_devLocalisedLabelStrPtr;
}


const char* languageManager::getLocalizedDevHelpTextStr() {
	return m_devLocalisedHelpTextStrPtr;
}

bool languageManager::isGetStringsPtrAttempt() {
	return m_isGetStringsPtrAttempt;
}

void languageManager::LogGameLocalisation() {
	std::string langStr = idCvarManager::getCvarString("sys_lang");
	logInfo("LogGameLocalisation: %s", langStr.c_str());

}