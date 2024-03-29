#pragma once


#include "../ImGui/dependencies/imgui/imgui.h"        




class ImGuiDebug {
private:
	static bool m_lastIsMouseWithinImGuiWindow;
public:


	static bool IsMouseWithinImGuiWindow()
	{
		if (ImGui::GetCurrentContext() == nullptr) {
			logInfo("GetCurrentContext is nullptr...");
			return false;
		}

		ImVec2 windowPos = ImGui::GetWindowPos();
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 mousePos = ImGui::GetMousePos();

		logInfo("windowPos: x: %.2f y: %.2f  windowSize: x: %.2f y: %.2f mousePos:  x: %.2f y: %.2f", windowPos.x, windowPos.y, windowSize.x, windowSize.y, mousePos.x, mousePos.y);
		if (mousePos.x >= windowPos.x && mousePos.x <= windowPos.x + windowSize.x &&
			mousePos.y >= windowPos.y && mousePos.y <= windowPos.y + windowSize.y)
		{
			logInfo("IsMouseWithinImGuiWindow: true");
			return true;       
		}
		logInfo("IsMouseWithinImGuiWindow: false");
		return false;       
	}
	
	

};
 bool ImGuiDebug::m_lastIsMouseWithinImGuiWindow = false;
