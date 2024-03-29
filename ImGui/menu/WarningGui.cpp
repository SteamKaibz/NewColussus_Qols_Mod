#include "WarningGui.h"





void WarningGui::showWarningWindow(bool* p_open)
{

    if (Config::getBuildType() == buildType::nexusRelease || !MenuStateManager::isInMenu()) {
        return;
    }



    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));      
    float widthPercentage = 1.0f / 8.0f;        
    float heightPercentage = 1.0f / 18.0f;       

    ImVec2 windowSize = ImVec2(viewport->Size.x * widthPercentage, viewport->Size.y * heightPercentage);

    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x + viewport->Size.x - windowSize.x, viewport->Pos.y + viewport->Size.y - windowSize.y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(windowSize);

    ImGui::Begin("Bottom-Right Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus);

    ImGui::TextWrapped(Config::getBuildTypeAsStr().c_str());
    ImGui::PopStyleColor();

    ImGui::End();
}
