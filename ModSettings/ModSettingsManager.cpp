#include "ModSettingsManager.h"




ModSettings ModSettingsManager::m_modSettings;


void ModSettingsManager::updateCvars() {
	logInfo("updating cvars... ");
	if (Config::getConfig() != ModConfig::debug) {
		idCvarManager::setCvar("win_pauseOnAltTab", "1");
	}	

	idCvarManager::setCvar("view_showWorldMarkers", "1");
	idCvarManager::setCvar("view_kickAmplitude_max", std::to_string(m_modSettings.viewKickMax));     
	idCvarManager::setCvar("r_blurGaussian", std::to_string(m_modSettings.isEnableGaussianBlur));
	idCvarManager::setCvar("r_skipFog", std::to_string(m_modSettings.isSkipFog));
	idCvarManager::setCvar("r_hdrDebug", std::to_string(m_modSettings.isHdrDisabled));
	idCvarManager::setCvar("r_saturation", std::to_string(m_modSettings.colorSaturation));
	idCvarManager::setCvar("view_scoreScale", std::to_string(m_modSettings.isShowHudScoreDamageNumbers));
	idCvarManager::setCvar("player_analyzeEnvFreeLeanOnly", std::to_string(m_modSettings.isFreeLeanOnly));
	idCvarManager::setCvar("swf_safeFrame", std::to_string(m_modSettings.hudSafeFrameOffset));

}


void ModSettingsManager::updateFromImGui(const ModSettings modSettings)
{
	m_modSettings = modSettings;

	updateHudPosAndScaleValsV2();
	
	if (!m_modSettings.isHeadLightAdvancedSettingsEnabled) {
		setMainLightSettingsToDefault();
	}

	soundManager::updateFromUserSettings();

	idAutomapManager::setAutoMapDefaultZoomToMinZoom(m_modSettings.isSetAutoMapDefaultZoomToMin);

	updateCvars();	

	logInfo("debug updateFromImGui: hudConfiguration is %d", m_modSettings.hudConfiguration);
}


ModSettings ModSettingsManager::get() {
	return m_modSettings;
}


void ModSettingsManager::resetHudSettings() {

	m_modSettings.isCustomCrosshair = false;
	m_modSettings.showAlarmIcons = true;
	m_modSettings.showMaxedOutText = true;
}


bool ModSettingsManager::isCustomHudEnabled() {
	return m_modSettings.isUseCustomHud;
}

bool ModSettingsManager::isHudWarningEnabled() {
	return  m_modSettings.isUseCustomHud && m_modSettings.isEnableHudWarning;
}

int ModSettingsManager::getOrangeArmorTriggerPrct()
{
	return m_modSettings.hudArmorOrangeTriggerPrct;
}

int ModSettingsManager::getOrangeHealthTriggerPrct()
{
	return m_modSettings.hudHealthOrangeTriggerPrct;
}

int ModSettingsManager::getRedHealthTriggerPrct() {
	return  m_modSettings.hudHealthRedTriggerPrct;
}

int ModSettingsManager::getRedHudArmorTriggerPrct() {
	return  m_modSettings.hudArmorRedTriggerPrct;
}

unsigned int ModSettingsManager::getHudWarningBlinkSpeedMs() {
	return  m_modSettings.hudBlinkWarningSpeedMs;
}



void ModSettingsManager::updateHudPosAndScaleValsV2() {
	HUDConfigV2 ImGuihudConfig = (HUDConfigV2)m_modSettings.hudConfiguration;
	switch (ImGuihudConfig)
	{
	case BiggestHud:
		m_modSettings.hudScale = 1.887f;
		m_modSettings.hudFrameHeightMul = 1.148f;
		break;
	case BiggerHud:
		m_modSettings.hudScale = 1.131f; 
		m_modSettings.hudFrameHeightMul = 1.107f; 
		break;
	case GameDefaultHud:
		m_modSettings.hudScale = 1.0f;
		m_modSettings.hudFrameHeightMul = 1.0f;
		break;
	case SmallerHud:
		m_modSettings.hudScale = 0.5f;
		m_modSettings.hudFrameHeightMul = 1.1f;
		break;
	case MiniHud:
		m_modSettings.hudScale = 0.821f;
		m_modSettings.hudFrameHeightMul = 1.74f;
		break;
	case CustomConfigHUD:
		break;
	default:
		logWarn("default case in updateHudPosAndScaleValsV2, how did that happen?! (setting default values)");
		m_modSettings.hudScale = 1.0f;
		m_modSettings.hudFrameHeightMul = 1.0f;
		break;
	}
}



float ModSettingsManager::getHudSafeFrameOffset() {
	return  m_modSettings.hudSafeFrameOffset;
}


float ModSettingsManager::getHudScale()
{
	return m_modSettings.hudScale;
}


float ModSettingsManager::gethudFrameHeightMul() {
	return m_modSettings.hudFrameHeightMul;
}

bool ModSettingsManager::getIsLogGameConsoleToLogFile()
{
	return m_modSettings.isLogGameConsoleToLogFile;
}


bool ModSettingsManager::getIsUseImgui() {
	static bool isFirstTime = true;


	//qsdflogInfo("ModSettingsManager::getIsUseImgui: m_modSettings.isUseImgui: %d", m_modSettings.isUseImgui);

	if (isFirstTime) {
		if (!m_modSettings.isUseImgui) {
			logWarn("user has disabled the mod gui in the json file, imgui will not be initialized. If you wanto re-enable the mod UI interface, close the game and delete the KaibzMod in the game folder or edit the json file again manually");
		}
		isFirstTime = false;
	}

	return m_modSettings.isUseImgui;
}

//void ModSettingsManager::setIsLogGameConsoleToLogFile(bool isLogToFile)
//{
//	m_modSettings.isLogGameConsoleToLogFile = isLogToFile;
//}



bool ModSettingsManager::isCustomCrosshairEnabled() {
	return m_modSettings.isCustomCrosshair;
}

bool ModSettingsManager::isAlarmIconsEnabled() {
	return m_modSettings.showAlarmIcons;
}

bool ModSettingsManager::isMaxedOutEnabled() {
	return m_modSettings.showMaxedOutText;
}

bool ModSettingsManager::isShowWorldMarkers() {
	return m_modSettings.isshowObjectiveMarkers;
}

bool ModSettingsManager::isShowHudScoreTotalNumber() {
	return m_modSettings.isShowHudScoreTotalNumber;
}


unsigned int ModSettingsManager::getNormalSpeedKeyCode() {
	return m_modSettings.normalSpeedKeyVkCode;
}

unsigned int ModSettingsManager::getFastForwardKeyCode() {
	return m_modSettings.fastForwardKeyVkCode;
}

std::string ModSettingsManager::getNormalSpeedKeyBindStr() {
	return ModSettings::keyCodeToString(m_modSettings.normalSpeedKeyVkCode);
}

unsigned int ModSettingsManager::getFlashLightKeyCode() {
	return m_modSettings.flashLightKeyVkCode;
}

unsigned int ModSettingsManager::getHighFrameMvtFixKeyVkCode()
{
	return m_modSettings.highFrameMvtFixKeyVkCode;
}


bool ModSettingsManager::isSilentProtagonist() {
	return m_modSettings.isSilentProtagonist;
 }

bool ModSettingsManager::isAutoPickItem(AutoPickUpType pickUpType)
{
	if (pickUpType == health && m_modSettings.isAutoPickUpHealth) return true;
	if (pickUpType == armor && m_modSettings.isAutoPickUpArmor) return true;
	if (pickUpType == ammo && m_modSettings.isAutoPickUpAmmo) return true;
	if (pickUpType == hatchet && m_modSettings.isAutoPickUpHatchet) return true;
	if (pickUpType == enigma && m_modSettings.isAutoPickEnigma) return true;
	return false;
}



bool ModSettingsManager::isDisableItemHighlight()
{
	return m_modSettings.isDisableItemHighlighthing;
}

bool ModSettingsManager::isDisableSimulationFilter()
{
	return m_modSettings.isDisabledSimulationFilter;;
}




void ModSettingsManager::setMainLightSettingsToDefault() {
	logInfo("setMainLightSettingsToDefault: triggered");
	m_modSettings.headlightIntensity = modSettingsConst::headlightIntensityDef;
	m_modSettings.headlightTarget_X = modSettingsConst::headlightTargetXDef;
	m_modSettings.headlightLightEnd_X = modSettingsConst::headlightEndXDef;
}


float ModSettingsManager::getHeadLightIntensity() {
	return m_modSettings.headlightIntensity;
}

float ModSettingsManager::getHeadLightTargetX() {
	return m_modSettings.headlightTarget_X;
}

float ModSettingsManager::getHeadLightEndX() {
	return m_modSettings.headlightLightEnd_X;
}

bool ModSettingsManager::isShowFlashLightIcon() {
	return m_modSettings.isShowFlashLightIcon;
}


idColor ModSettingsManager::getUserFlashlightColor() {
	return idColor(m_modSettings.headlightColor.x, m_modSettings.headlightColor.y, m_modSettings.headlightColor.z, m_modSettings.headlightColor.w);
}



bool ModSettingsManager::isAdsToggleEnabled() {
	return m_modSettings.isAdsToggle;
}

unsigned int ModSettingsManager::getZoomKeyVkCode() {
	return m_modSettings.zoomKeyVkCode;
}

float ModSettingsManager::getHeadBobAmount() {
	return m_modSettings.headBobAmount;
}


bool ModSettingsManager::isModLoadBeep() {
	return m_modSettings.isModLoadBeep;
}




void ModSettingsManager::debugPrint()
{
	logInfo("ModSettings debugPrint: have to rewrite this function...");

	logInfo("");
}










