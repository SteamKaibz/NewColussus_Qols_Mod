#include "DebugGui.h"


void DebugGui::showDebugWindow(bool* p_open)
{

    if (idLoadScreenManager::getLoadScreenState() != loadScreenState::NotActive) {
        return;      
    }


    ImGuiDebugWin::ClearMessages();

    ImGuiDebugWin::AddMessage("DEBUG:");
    ImGuiDebugWin::AddMessage("_");

    ImGuiDebugWin::AddMessage(Debug::getCurrentMovementModeStr());


    ImGuiDebugWin::AddMessage("hudGameFlags: ");
    ImGuiDebugWin::AddMessage(K_Utils::intToHexString(Debug::gethudStateFlagsInt()));


    ImGuiDebugWin::AddMessage("idFocusTrackerManager Last Crosshair Info State: ");
    ImGuiDebugWin::AddMessage(idFocusTrackerManager::getCrosshairInfoStr());
    ImGuiDebugWin::AddMessage(Tests::getmovementModeDgbStrForImgui());


    ImGuiDebugWin::AddMessage(hudManager::inGuiGetDualWieldInfo());       

    std::string preMoveEventStr = "PreMoveEvent: ";
    preMoveEventStr += std::to_string((int)idPlayerManager::getPreMoveEvent());
    ImGuiDebugWin::AddMessage(preMoveEventStr);

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
