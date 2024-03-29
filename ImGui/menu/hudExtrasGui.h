#pragma once

#include <Windows.h>
#include "../dependencies/imgui/imgui.h"
#include "menu.hpp"


#define IM_COL32_REDK       IM_COL32(255,0,0,115)  
#define IM_COL32_HUDCOLOR       IM_COL32(228,222,208,255)  

class hudExtrasGui
{
private:

	static ImVec4 gameHudColor;
	static ImVec4 redHudColor;

public:
	static void showHudExtrasWindow(bool* p_open = NULL);
};

