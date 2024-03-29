#include "soundManager.h"

std::string soundManager::m_skipBjRefStr = "play_bj_";
std::string soundManager::m_skipAnaRefStr = "play_anya";
std::string soundManager::m_skipGraceRefStr = "play_grace";




std::unordered_set<std::string> soundManager::skipSoundsStrSet = {};

void soundManager::updateFromUserSettings()
{
    skipSoundsStrSet.clear();
    const auto settings = ModSettingsManager::get();

    if (settings.isSilentProtagonist) {
        skipSoundsStrSet.insert(m_skipBjRefStr);
    }
    if (settings.isSilentAna) {
        skipSoundsStrSet.insert(m_skipAnaRefStr);
    }
    if (settings.isSilentGrace) {
        skipSoundsStrSet.insert(m_skipGraceRefStr);
    }

}
