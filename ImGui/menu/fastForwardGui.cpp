#include "fastForwardGui.h"



//

std::string fastForwardGui::getCurrentSpeedStr() {

   return "Current Speed : X" + std::to_string((int)timescaleManager::getCurrentTimeScaleValF());
}


ImVec4& fastForwardGui::getSpeedTextColorVec4() {

    size_t currentSpeedIndex = timescaleManager::getCurrentSpeedIndex();   

    if (currentSpeedIndex == 1) {
        return Menu::whiteColor;
    }
    else if (currentSpeedIndex == 2) {
        return Menu::orangeColor;
    }
    else {
        return Menu::redColor;
    }

}

void printMultiColoredHelperString() {
    //ImVec4 colorKey1 = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Red color
    //ImVec4 colorKey2 = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // Green color

    std::string keyBindStr1 = ModSettingsManager::getFastForwardKeyBindStr();
    std::string keyBindStr2 = ModSettingsManager::getNormalSpeedKeyBindStr();

    // Display the string with different colors for keys
    ImGui::TextColored(Menu::whiteColor, "Press:"); 
    ImGui::SameLine();
    ImGui::TextColored(Menu::yellowColor, keyBindStr1.c_str()); 
    ImGui::SameLine();
    ImGui::TextColored(Menu::whiteColor, "To Increase Speed Or"); 
    ImGui::SameLine();
    ImGui::TextColored(Menu::yellowColor, keyBindStr2.c_str());
    ImGui::SameLine();
    ImGui::TextColored(Menu::whiteColor, "To Reset Speed");
}



//! from Metro Exodus Qols:
void fastForwardGui::show(bool* p_open) {
    

    static uint64_t lastBlinkMs = 0;
    static bool isBlink = true;

    if (K_Utils::EpochMillis() - lastBlinkMs > 300) {
        lastBlinkMs = K_Utils::EpochMillis();
        isBlink = !isBlink;
    }


    ImGuiViewport* viewport = ImGui::GetMainViewport();

    // Set the window position and size to cover the entire screen
    ImVec2 window_pos = ImVec2(viewport->Pos.x, viewport->Pos.y);
    ImVec2 window_size = ImVec2(viewport->Size.x, viewport->Size.y);

    // Set the window position and size
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size);

    // Make the window background transparent
    ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background

    ImVec4 IconColorImVec4 = Menu::whiteColor;

    // Create the window
    if (ImGui::Begin("FastForwardGUI", p_open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground))
    {
        if (isBlink) {
            IconColorImVec4 = Menu::invisibleColor;
        }

        ImVec2 iconSize = ImGui::CalcTextSize(ICON_FA_FORWARD);
        ImVec2 iconPos = ImVec2((window_size.x - iconSize.x) * 0.5f, window_size.y * 0.75f);
        ImGui::SetCursorPos(ImVec2((window_size.x * 0.5f - (iconSize.x / 2)), (window_size.y * 0.75f - (iconSize.y / 2))));
        ImGui::PushFont(Menu::icons_font_awesome);
        //! doesn't work. it fucks up the font size for other windows.
        //ImGui::SetWindowFontScale(4.0f);  // Adjust the scaling factor as needed
        ImGui::TextColored(IconColorImVec4, ICON_FA_FORWARD);
        ImGui::PopFont();

        float currentFontSize = ImGui::GetFontSize();      
       
        //? make sure you also modify printMultiColoredHelperString() if you change this string as atm, the only way to print multicolor string is to do it this way, which is not ideal but we should manage.
        std::string helperStr = "Press: " + ModSettingsManager::getFastForwardKeyBindStr() + " To Increase Speed Or " + ModSettingsManager::getNormalSpeedKeyBindStr() + " To Reset Speed";
        ImVec2 textSize = ImGui::CalcTextSize(helperStr.c_str());
        float helperTextPosX = (window_size.x - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(helperTextPosX);
        printMultiColoredHelperString();
        //ImGui::TextColored(Menu::yellowColor, helperStr.c_str());

        //std::string currentSpeedStr = "current Speed : " + gameSpeedManager::getCurrentSpeedStr();
        ImVec2 speedTextSize = ImGui::CalcTextSize(getCurrentSpeedStr().c_str());
        float centeredSpeedTextPosX = (window_size.x - speedTextSize.x) * 0.5f;
        ImGui::SetCursorPosX(centeredSpeedTextPosX);
        ImGui::TextColored(getSpeedTextColorVec4(), getCurrentSpeedStr().c_str());


    }
    ImGui::End();


}



//void fastForwardGui::showFastForwardIcon(bool* p_open) {
    //    
    //
    //    static uint64_t lastBlinkMs = 0;
    //    static bool isBlink = true;
    //
    //    if (K_Utils::EpochMillis() - lastBlinkMs > 300) {
    //        lastBlinkMs = K_Utils::EpochMillis();
    //        isBlink = !isBlink;
    //    }
    //
    //       
    //  
    //    ImGuiViewport* viewport = ImGui::GetMainViewport();
    //
    //    ImVec2 window_pos = ImVec2(viewport->Pos.x, viewport->Pos.y);
    //    ImVec2 window_size = ImVec2(viewport->Size.x, viewport->Size.y);
    //
    //    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    //    ImGui::SetNextWindowSize(window_size);
    //
    //    ImGui::SetNextWindowBgAlpha(0.0f);   
    //
    //    if (ImGui::Begin("FastForwardGUI", p_open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground))
    //    {      
    //        if (isBlink) {
    //            ImVec2 iconSize = ImGui::CalcTextSize(ICON_FA_FORWARD);
    //            ImVec2 iconPos = ImVec2((window_size.x - iconSize.x) * 0.5f, window_size.y * 0.75f);
    //            ImGui::SetCursorPos(ImVec2((window_size.x * 0.5f - (iconSize.x / 2)), (window_size.y * 0.75f - (iconSize.y / 2))));
    //            ImGui::PushFont(Menu::icons_font_awesome);
    //            ImGui::Text(" ");
    //            ImGui::PopFont();
    //
    //            float currentFontSize = ImGui::GetFontSize();
    //            std::string helperStr = "Press: " + ModSettingsManager::getNormalSpeedKeyBindStr() + " to go back to normal speed";
    //            ImVec2 textSize = ImGui::CalcTextSize(helperStr.c_str());
    //            float textPosX = (window_size.x - textSize.x) * 0.5f;
    //            ImGui::SetCursorPosX(textPosX);
    //
    //            ImGui::PushStyleColor(ImGuiCol_Text, Menu::orangeColor);
    //            ImGui::Text(helperStr.c_str());
    //            ImGui::PopStyleColor();    
    //
    //           
    //        }    
    //        else {
    //
    //            ImVec2 iconSize = ImGui::CalcTextSize(ICON_FA_FORWARD);
    //            ImVec2 iconPos = ImVec2((window_size.x - iconSize.x) * 0.5f, window_size.y * 0.75f);
    //            ImGui::SetCursorPos(ImVec2((window_size.x * 0.5f - (iconSize.x / 2)), (window_size.y * 0.75f - (iconSize.y / 2))));
    //            ImGui::PushFont(Menu::icons_font_awesome);
    //            ImGui::Text(ICON_FA_FORWARD);
    //            ImGui::PopFont();
    //
    //            float currentFontSize = ImGui::GetFontSize();
    //            std::string helperStr = "Press: " + ModSettingsManager::getNormalSpeedKeyBindStr() + " to go back to normal speed";
    //            ImVec2 textSize = ImGui::CalcTextSize(helperStr.c_str());
    //            float textPosX = (window_size.x - textSize.x) * 0.5f;
    //            ImGui::SetCursorPosX(textPosX);
    //
    //            ImGui::PushStyleColor(ImGuiCol_Text, Menu::orangeColor);
    //            ImGui::Text(helperStr.c_str());
    //            ImGui::PopStyleColor();    
    //
    //        }
    //
    //
    //       
    //
    //
    //    }
    //    ImGui::End();
    //   
    //
    //}