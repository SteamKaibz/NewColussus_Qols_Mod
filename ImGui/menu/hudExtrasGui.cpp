#include "hudExtrasGui.h"





void hudExtrasGui::showHudExtrasWindow(bool* p_open)
{



    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImVec2 window_pos = ImVec2(viewport->Pos.x, viewport->Pos.y);
    ImVec2 window_size = ImVec2(viewport->Size.x, viewport->Size.y);

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size);

    ImGui::SetNextWindowBgAlpha(0.0f);   

    float xOffset = window_size.x * 0.04f;
    float yOffset = window_size.y * 0.04f;

    if (ImGui::Begin("FastForwardGUI", p_open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground))
    {
        ImGui::PushFont(Menu::icons_font_awesome);

        ImDrawList* drawList = ImGui::GetWindowDrawList();

        ImVec2 iconPos = ImVec2(window_size.x - xOffset, yOffset);
        ImVec2 textSize = ImGui::CalcTextSize(ICON_FA_LIGHTBULB);

        drawList->AddText(iconPos, IM_COL32_REDK, ICON_FA_LIGHTBULB);
        drawList->AddText(ImVec2(iconPos.x + 1, iconPos.y + 1), IM_COL32_HUDCOLOR, ICON_FA_LIGHTBULB);
        ImGui::PopFont();
    }
    ImGui::End();
}


















