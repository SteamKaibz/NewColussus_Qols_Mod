#include "liveStatsGui.h"


void liveStatsGui::show(bool* p_open) {

    if (idLoadScreenManager::getLoadScreenState() != loadScreenState::NotActive) {
        return;
    } 

    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImVec2 window_pos = ImVec2(viewport->Pos.x, viewport->Pos.y);
    ImVec2 window_size = ImVec2(viewport->Size.x, viewport->Size.y);

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size);

    ImGui::SetNextWindowBgAlpha(0.0f);

    if (ImGui::Begin("LiveStats", p_open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground))
    {
        ImGui::TextUnformatted("LIVE STATS: ");

        for (const auto& statStr : statsManager::getStatsStrVecForImgui(statsManager::GameStatsEnums)) {
            ImGui::TextUnformatted(statStr.c_str());
        }
    }
    ImGui::End();
}