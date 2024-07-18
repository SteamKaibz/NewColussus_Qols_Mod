#pragma once

#include <string>

#include "idResourceManager.h"
#include "idCvarManager.h"




class languageManager
{

private:
	
	//static const char* m_modMenuBtnStr; //! the btn people will press to go to mod menu
	//static const char* m_modMenuHelpStr; //! the string at the bottom of the string when user hover over the mod menu btn

	static const char* m_devLocalisedLabelStrPtr;
	static const char* m_devLocalisedHelpTextStrPtr;

	static bool m_isGetStringsPtrAttempt;


public:

	static bool acquireDevStringsPtrs();

	//static void replaceDevText(idSWFTextInstance* textInst);


	static const char* getModMenuBtnStr();
	static const char* getModMenuHelpStr();

	static const char* getLocalizedDevStr();

	static const char* getLocalizedDevHelpTextStr();

	static bool isGetStringsPtrAttempt();

	static void LogGameLocalisation();


	//static inline std::u8string RussianDevStr = u8"Frag Grenade";
	/*static inline std::u8string IceGrenadeEnglishStr = u8"Ice Grenade";
	static inline std::u8string FragGrenadeFrenchStr = u8"Grenade Frag";
	static inline std::u8string IceGrenadeFrenchStr = u8"Grenade Glace";
	static inline std::u8string FragGrenadeGermanStr = u8"Sprenggranate";
	static inline std::u8string IceGrenadeGermanStr = u8"Eisgranate";
	static inline std::u8string FragGrenadeItalianStr = u8"Granata Frag";
	static inline std::u8string IceGrenadeItalianStr = u8"Granata Ghiaccio";
	static inline std::u8string FragGrenadeJapanStr = u8"破片グレネード";
	static inline std::u8string IceGrenadeJapanStr = u8"氷グレネード";
	static inline std::u8string FragGrenadePolishStr = u8"Granat Frag";
	static inline std::u8string IceGrenadePolishStr = u8"Granat Lodowy";*/

};

