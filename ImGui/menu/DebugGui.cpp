#include "DebugGui.h"


void DebugGui::showDebugWindow(bool* p_open)
{

    if (idLoadScreenManager::getLoadScreenState() != loadScreenState::NotActive) {
        return;      
    }


    ImGuiDebugWin::ClearMessages();

    ImGuiDebugWin::AddMessage("DEBUG:");
    ImGuiDebugWin::AddMessage("_");

    std::string buttonsStr = "usercmd_t=>buttons: ";
    buttonsStr += K_Utils::intToHexString(idUsercmdGenLocalManager::DBG_Buttons);
    ImGuiDebugWin::AddMessage(buttonsStr);

    std::string lastKeyPressedStr = "last key pressed: ";
    std::string keyStr = idUsercmdGenLocalManager::debugGetLastA2InidKeyboardSmth_AE72A0Str();
    lastKeyPressedStr += keyStr;

    ImGuiDebugWin::AddMessage(idUsercmdGenLocalManager::debug_getFireKeysInfoStr());

    ImGuiDebugWin::AddMessage(lastKeyPressedStr);

    ImGuiDebugWin::AddMessage(Debug::getCurrentMovementModeStr());


    ImGuiDebugWin::AddMessage("hudGameFlags: ");
    ImGuiDebugWin::AddMessage(K_Utils::intToHexString(Debug::gethudStateFlagsInt()));


    ImGuiDebugWin::AddMessage("idFocusTrackerManager Last Crosshair Info State: ");
    ImGuiDebugWin::AddMessage(idFocusTrackerManager::getCrosshairInfoStr());
    ImGuiDebugWin::AddMessage(Tests::getmovementModeDgbStrForImgui());


    std::string dwInfoStr = "Is Dual Wielding: ";
    dwInfoStr += K_Utils::boolToStr(idPlayerManager::isDualWielding());
    ImGuiDebugWin::AddMessage(dwInfoStr);

    ImGuiDebugWin::AddMessage(idPlayerManager::getAnimSysEventsDgbStrForImgui());

    ImGuiDebugWin::AddMessage(cameraManager::getAnimCamAmountDbgStrForImgui());

    std::string leanModeStr = "is Leaning: ";
    if (idPlayerManager::isLeaning()) {
        leanModeStr += "true";
    }
    else {
        leanModeStr += "false";
    }    
    ImGuiDebugWin::AddMessage(leanModeStr);

    std::string postFiringStr = "Is Post firing: ";
    postFiringStr += std::to_string(cameraManager::Dbg_isPostFiring);
    ImGuiDebugWin::AddMessage(postFiringStr);


    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImVec2 window_pos = ImVec2(viewport->Pos.x, viewport->Pos.y);
    ImVec2 window_size = ImVec2(viewport->Size.x, viewport->Size.y);

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size);

    ImGui::SetNextWindowBgAlpha(0.0f);   

    if (ImGui::Begin("Debug Window", p_open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground))
    {
        for (const auto& msg : ImGuiDebugWin::getMessages()) {
            ImGui::TextUnformatted(msg.c_str());
        }
    }
    ImGui::End();
}
