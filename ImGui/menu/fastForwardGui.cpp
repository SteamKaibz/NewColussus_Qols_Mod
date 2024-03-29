#include "fastForwardGui.h"



void fastForwardGui::showFastForwardIcon(bool* p_open) {
    

    static uint64_t lastBlinkMs = 0;
    static bool isBlink = true;

    if (K_Utils::EpochMillis() - lastBlinkMs > 300) {
        lastBlinkMs = K_Utils::EpochMillis();
        isBlink = !isBlink;
    }

       
  
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImVec2 window_pos = ImVec2(viewport->Pos.x, viewport->Pos.y);
    ImVec2 window_size = ImVec2(viewport->Size.x, viewport->Size.y);

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size);

    ImGui::SetNextWindowBgAlpha(0.0f);   

    if (ImGui::Begin("FastForwardGUI", p_open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground))
    {      
        if (isBlink) {
            ImVec2 iconSize = ImGui::CalcTextSize(ICON_FA_FORWARD);
            ImVec2 iconPos = ImVec2((window_size.x - iconSize.x) * 0.5f, window_size.y * 0.75f);
            ImGui::SetCursorPos(ImVec2((window_size.x * 0.5f - (iconSize.x / 2)), (window_size.y * 0.75f - (iconSize.y / 2))));
            ImGui::PushFont(Menu::icons_font_awesome);
            ImGui::Text(" ");
            ImGui::PopFont();

            float currentFontSize = ImGui::GetFontSize();
            std::string helperStr = "Press: " + ModSettingsManager::getNormalSpeedKeyBindStr() + " to go back to normal speed";
            ImVec2 textSize = ImGui::CalcTextSize(helperStr.c_str());
            float textPosX = (window_size.x - textSize.x) * 0.5f;
            ImGui::SetCursorPosX(textPosX);

            ImGui::PushStyleColor(ImGuiCol_Text, Menu::orangeColor);
            ImGui::Text(helperStr.c_str());
            ImGui::PopStyleColor();    

           
        }    
        else {

            ImVec2 iconSize = ImGui::CalcTextSize(ICON_FA_FORWARD);
            ImVec2 iconPos = ImVec2((window_size.x - iconSize.x) * 0.5f, window_size.y * 0.75f);
            ImGui::SetCursorPos(ImVec2((window_size.x * 0.5f - (iconSize.x / 2)), (window_size.y * 0.75f - (iconSize.y / 2))));
            ImGui::PushFont(Menu::icons_font_awesome);
            ImGui::Text(ICON_FA_FORWARD);
            ImGui::PopFont();

            float currentFontSize = ImGui::GetFontSize();
            std::string helperStr = "Press: " + ModSettingsManager::getNormalSpeedKeyBindStr() + " to go back to normal speed";
            ImVec2 textSize = ImGui::CalcTextSize(helperStr.c_str());
            float textPosX = (window_size.x - textSize.x) * 0.5f;
            ImGui::SetCursorPosX(textPosX);

            ImGui::PushStyleColor(ImGuiCol_Text, Menu::orangeColor);
            ImGui::Text(helperStr.c_str());
            ImGui::PopStyleColor();    

        }


       


    }
    ImGui::End();
   

}