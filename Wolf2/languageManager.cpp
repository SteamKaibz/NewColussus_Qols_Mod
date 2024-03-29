#include "languageManager.h"


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